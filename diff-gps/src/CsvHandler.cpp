
#include "CsvHandler.h"

using namespace std;

CsvHandler::CsvHandler(){}

CsvHandler::CsvHandler(string filename)
{
	this->infile = filename;	
}

void CsvHandler::setFileName(string filename) {
	this->infile = filename;
}

ClientGpsData CsvHandler::getClientData() {
	cout << "Getting client data.... \n";
	numLines();
	cout << "Calculated numLines \n";
	ClientGpsData myClientGpsData = readCsv();
	return myClientGpsData;
}
ClientGpsData CsvHandler::getClientData(string filename) {
	cout << "Getting client data.... \n";
	this->infile = filename;
	cout << "Calculated numLines \n";
	numLines();
	cout << "Reading CSV and creating myClientGpsData\n";
	ClientGpsData myClientGpsData = readCsv();
	cout << "Returning myClientGpsData\n";
	return myClientGpsData;
}
void CsvHandler::numLines()
{
	int number_of_lines = 0;
	string line;
	ifstream infile(this->infile.c_str());
	while (std::getline(infile, line)) {
		//cout << line;
		++number_of_lines;
	}
	this->lines = number_of_lines;
}
ClientGpsData CsvHandler::readCsv(){
	cout << "In readCsv\n";
	cout << "The Csv has this many lines: " << this->lines << "\n";
	vector<vector<long double> > possitions;
	vector<vector<bool> > satellites;
	vector<long long int> times;
	possitions.resize(this->lines);
	satellites.resize(this->lines);
	times.resize(this->lines);

	for (int i = 0; i < this->lines; ++i) 
	{
		possitions[i].resize(3);
		satellites[i].resize(86);
		for (int j=0; j< 86; ++j) satellites[i][j] = false;
	}
	cout << "initialized value vectors\n";

    ifstream infile(this->infile.c_str());
    //ifstream infile("loc_log__2014_62_1812.csv");
    string line = "";
    int i = 0;
    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";
        int j = 0;
        //long long int w = 0;
        //long double x = 0.0;
        //long double y = 0.0;
        //long double z = 0.0;
        sscanf(line.c_str(), "%lli,%Lf,%Lf,%Lf\n",&times[i], &possitions[i][0], &possitions[i][1], &possitions[i][2]);
        while (getline(strstr,word, ',')) 
        {       	
        	if (j>3) { satellites[i][atoi(word.c_str())] = true; }
        	//cout << word << '\n';
        	j++;
        }
       	i++;
    }
    cout << "Csv File read and vectors filled with values\n";
    ClientGpsData myClientGpsData = ClientGpsData(this->lines, times, possitions, satellites);
    cout << "created instance of ClientGpsData\n";
    //vector<vector<long double> > possitions = myClientGpsData.getP;
    cout << "size of possitons ==";
    cout << possitions.size() << "\n";
    return myClientGpsData;
}
void CsvHandler::writeCsv(ClientGpsData myClientGpsData){
	cout << "Writing new CSV file \n";
	vector<long long> times = myClientGpsData.getTheTime();
	vector<vector<long double> > possitions = myClientGpsData.getInitialGeo();
	vector<vector<bool> > satellites = myClientGpsData.getSatellites();

	double f = 0.0;
	cout << "Initialized client data structures\n";

	ofstream outfile;
  	outfile.open ( "corrected.csv");
  	cout <<"Attempting to write csv file \n";
	for (int i = 0; i<this->lines; i++) {
		//outfile << to_string(times[i]) << ","; *********** to_string causing issues
		for (int j=0; j< 3; j++) {
			//outfile << to_string((possitions[i][j]))  << ","; *********** to_string causing issues
		}
		for (int j=0; j<86; j++) {
			if (satellites[i][j]) {
				outfile << j << ",";
			}
		}
		outfile << "\n";
	}
	cout <<"Closing file and returning \n";
  	outfile.close();
  }
template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
