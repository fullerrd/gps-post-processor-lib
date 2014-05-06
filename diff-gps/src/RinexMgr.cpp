#include "RinexMgr.h"
#include <stdlib.h>

using namespace std;
using namespace gpstk;



RinexMgr::RinexMgr () {

}

void RinexMgr::possitionSolution(ClientGpsData& myClientGpsData){

	//File names to be replaced with calls to FileSystemMgr
	string obsFile = "./RINEX/dsrc0630.14o";
	string lastNavFile = "./RINEX/brdc0800.14n";
	string currentNavFile = "./RINEX/brdc0630.14n";
	string nextNavFile = "./RINEX/brdc0800.14n";

	GPSEphemerisStore bcestore;
	PRSolution2 PRSolver;
	ZeroTropModel noTropModel;
	GGTropModel ggTropModel;
	TropModel *tropModelPtr=&noTropModel;
	const double gamma = (L1_FREQ_GPS/L2_FREQ_GPS)*(L1_FREQ_GPS/L2_FREQ_GPS);
	try
	{
		// Read nav file and store unique list of ephemerides
    	Rinex3NavStream rnffs(currentNavFile.c_str());    // Open ephemerides data file
      Rinex3NavData rne;
      Rinex3NavHeader hdr;

      // Let's read the header (may be skipped)
     	rnffs >> hdr;

      // Storing the ephemeris in "bcstore"
      while (rnffs >> rne) bcestore.addEphemeris(rne);

      // Setting the criteria for looking up ephemeris
      bcestore.SearchNear();


      Rinex3ObsStream roffs(obsFile.c_str());    // Open observations data file

      // In order to throw exceptions, it is necessary to set the failbit
      roffs.exceptions(ios::failbit);

      Rinex3ObsHeader roh;
      Rinex3ObsData rod;

         // Let's read the header
      roffs >> roh;

      int indexC1;
      try
      {
         indexC1 = roh.getObsIndex( "C1" );
      }
      catch(...)
      {
         cerr << "The observation file doesn't have C1 pseudoranges." << endl;
         exit(1);
      }
      int iteration = 0;
      //double minX=, minY, minZ, maxX, maxY, maxZ;
      //Process Lines of the observation file
      while( roffs >> rod )
      {
      	if( rod.epochFlag == 0 || rod.epochFlag == 1 )  // Begin usable data
         {

            vector<SatID> prnVec;
            vector<double> rangeVec;

               // Define the "it" iterator to visit the observations PRN map. 
               // Rinex3ObsData::DataMap is a map from RinexSatID to
               // vector<RinexDatum>:
               //      std::map<RinexSatID, vector<RinexDatum> >
            Rinex3ObsData::DataMap::const_iterator it;

               // This part gets the PRN numbers and ionosphere-corrected
               // pseudoranges for the current epoch. They are correspondly fed
               // into "prnVec" and "rangeVec"; "obs" is a public attribute of
               // Rinex3ObsData to get the map of observations

            for( it = rod.obs.begin(); it!= rod.obs.end(); it++ )
            {
            	double C1( 0.0 );
               try
               {
                  C1 = rod.getObs( (*it).first, indexC1 ).data;
               }
               catch(...)
               {
                     // Ignore this satellite if P1 is not found
                  continue;
               }
            	// Now, we include the current PRN number in the first part
                  // of "it" iterator into the vector holding the satellites.
                  // All satellites in view at this epoch that have P1 or P1+P2
                  // observations will be included.
               prnVec.push_back( (*it).first );

                  // The same is done for the vector of doubles holding the
                  // corrected ranges
               rangeVec.push_back( C1 - 0.0 );

                     // WARNING: Please note that so far no further correction
                     // is done on data: Relativistic effects, tropospheric
                     // correction, instrumental delays, etc.

            }
            Matrix<double> SVP;
            std::ostream *pDebug=NULL;
            PRSolver.PrepareAutonomousSolution( rod.time, prnVec, rangeVec, bcestore, SVP, pDebug);
         	  //cout << "Size of prnVec: " << prnVec.size();
            vector<bool> UseSat, UseSave;
            vector<int> GoodIndexes;
            bool hasGlonass = false;
            bool hasOther = false;
            int N, i;
            /*
            if(Debug && pDebugStream) {
              *pDebugStream << "In RAIMCompute after PAS(): Satellites:";
                for(j=0; j<prnVec.size(); j++) {
                  RinexSatID rs(::abs(prnVec[j].id), prnVec[j].system);
                  *pDebugStream << " " << (prnVec[j].id < 0 ? "-":"") << rs;
                }
                *pDebugStream << endl;
                *pDebugStream << " SVP matrix(" << SVP.rows() << "," << SVP.cols() << ")" << endl;
                *pDebugStream << fixed << setw(16) << setprecision(3) << SVP << endl;
            }
            */
            long long ut = UnitConverter::getUnixTime(rod.time);
            vector<vector<long double> > clientEcef = myClientGpsData.getInitialCart();
            vector<vector<bool> > clientSats = myClientGpsData.getSatellites();
            vector<long long> clientTimes = myClientGpsData.getTheTime();
            vector<int8_t>  clientFlags = myClientGpsData.getFlags();
            //cout << UnitConverter::getDayOfYear((clientTimes[iteration]/1000)) << "\n";

            //cout << ut << "   !=    " << (clientTimes[0]) << "\n";
            //cout << (abs((clientTimes[0]/1000) - ut)) << "\n";
            






            for (N=0,i=0; i<prnVec.size(); i++)
            {
              if (prnVec[i].id > 0)
              {
                N++;
                UseSat.push_back(true);
                GoodIndexes.push_back(i);
              }
              else
              {
                UseSat.push_back(false);
              }
            }
            UseSave = UseSat;

            //if (N < prnVec.size()) return -3;


            int x = prnVec[0].id;
            //Prepare constance and output vectors for AutonomousPRSolution
            vector<bool> use;
         	  bool algebraic = false;
            int n_iterate = 30;
            double converge = 3.e-8;
            Vector<double> Sol;
            Matrix<double> Cov;
            Vector<double> Resid(prnVec.size());
            Vector<double> Slope(rangeVec.size());
            //cout << "The size of UseSat is: " << UseSat.size() << "\n";
            //cout << prnVec[0].id << prnVec[1].id << prnVec[2].id << prnVec[3].id << prnVec[4].id << prnVec[5].id<< "\n";
         	  PRSolver.AutonomousPRSolution(rod.time,
                                      UseSat,
                                      SVP,
                                      tropModelPtr,
                                      algebraic,
                                      n_iterate,
                                      converge,
                                      Sol,
                                      Cov,
                                      Resid,
                                      Slope,
                                      pDebug);
            //double dist;
            /*if (iteration < 675 && iteration < 679) {
            
            cout << "------------------------------------------------\n";
            cout << "For iteration #: "<< iteration << "\n";
            cout << "UT == " << ut << "\n";
            if (Sol.size() == 4) { 
              cout << "x == ";
              printf("%lf \n", Sol[0]);
              cout << "y == ";
              printf("%lf \n", Sol[1]);
              cout << "z == ";
              printf("%lf \n", Sol[2]);
              cout << "common time == ";
              printf("%lf \n", Sol[3]);
              */
              vector<long double>pos = myClientGpsData.getStationCoords();
              vector<double> pos1(3);
              pos1[0] = (double) pos[0];
              pos1[1] = (double) pos[1];
              pos1[2] = (double) pos[2];
              Vector<double>pos2 = Sol;
              double dist = sqrt(((pos1[0]-pos2[0])*(pos1[0]-pos2[0])) + ((pos1[1]-pos2[1])*(pos1[1]-pos2[1])) + ((pos1[2]-pos2[2])*(pos1[2]-pos2[2])));
              //cout << "Distance from known station postion: "<< dist << "\n";
            //}
            //}
            for(int S = 0; S < clientSats.size(); S++) { 
              if (clientFlags[S] != 1 && abs((clientTimes[S]/1000) - ut) < 60 ) { 
                cout << "Client posstion fix at " << (clientTimes[S]/1000)<< "-UT corrected by " << dist << " meters.\n";
                clientFlags[S] = 1;

              }
            }

            
            iteration++;
         }
      }
   }
   catch(Exception& e)
   {
      cerr << e << endl;
   }
   catch (...)
   {
      cerr << "Caught an unexpected exception." << endl;
   }



}