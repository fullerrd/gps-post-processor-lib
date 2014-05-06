#include "GpsPostProcessor.h"

using namespace std;

GpsPostProcessor& GpsPostProcessor::getInstance() {
  static GpsPostProcessor instanceGPSPP;
  instanceGPSPP.myCsvHandler = CsvHandler();
  instanceGPSPP.fsMgr = FileSystemMgr();
  instanceGPSPP.bsMgr = BaseStationMgr();
  instanceGPSPP.rnxMgr = RinexMgr();
  return instanceGPSPP;
}

void GpsPostProcessor::runPostProcessor(string filename) {

	ClientGpsData myClientData = myCsvHandler.getClientData(filename);
  vector<vector<long double> > clientGeo = myClientData.getInitialGeo();
  vector<vector<long double> > clientEcef = clientGeo;
  int size = clientGeo.size();
  for (int i=0;i<size;i++) {
    clientEcef[i] = UnitConverter::geoToCart(clientGeo[i][0],clientGeo[i][1],clientGeo[i][2]);
  }
  myClientData.setInitialCart(clientEcef);
  bsMgr.getNearestRinex(myClientData);
  rnxMgr.possitionSolution(myClientData);
  // cout << fsMgr.getRinexUrl(myClientData.getStationId(),myClientData.get);
	// vector<long>  times = myClientData.getTheTime();
	// cout << times[0] << "\n" << times[1] << "\n"<< times[2] << "\n";
}

int main(int argc, char* argv[]) {

  GpsPostProcessor& gpp = GpsPostProcessor::getInstance();
  cout << "created instance of GpsPostProcessor\n";
  gpp.runPostProcessor("./client-data/loc_log__2014_62_1812.csv");

  // unitconverter test code (best practice would be to have real unit tests with
  // known values)
  long double lat = 1.0;
  long double lon = 1.0;
  long double alt = 1.0;
  long double x = 1.0;
  long double y = 1.0;
  long double z = 1.0;

  vector<long double> cartesian;
  cartesian = UnitConverter::geoToCart(lat, lon, alt);
  printf("\n\nUnitConverter test geoToCart\n  in: %Lf, %Lf, %Lf\n", lat, lon, alt);
  printf("  out: %Lf, %Lf, %Lf\n", cartesian[0], cartesian[1], cartesian[2]);

  vector<long double> geocentric;
  geocentric = UnitConverter::cartToGeo(x, y, z);
  printf("UnitConverter test cartToGeo\n  in: %Lf, %Lf, %Lf\n", x, y, z);
  printf("  out: %Lf, %Lf, %Lf\n\n", geocentric[0], geocentric[1], geocentric[2]);

  
  // in seconds
  long one_year = 60 * 60 * 24 * 365;
  long one_day = 60 * 60 * 24;
  
  // 3 years, 2 days; getYear should be 1973, getDayOfYear should be 32
  long u_time = (3 * one_year) + (32 * one_day) + 100;

  string year = UnitConverter::getYear(u_time);
  string dayOfYear = UnitConverter::getDayOfYear(u_time);

  // should output 3
  printf("\n\nUnitConverter test getYear\n  in: %ld\n  out: ", u_time);
  cout << year << endl;

  // should output 2
  printf("\n\nUnitConverter test getDayOfYear\n  in: %ld\n  out: ", u_time);
  cout << dayOfYear << endl;

  return 0;
}
