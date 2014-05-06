
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
	vector<vector<double> > possitions;
	vector<vector<bool> > satellites;
	vector<long int> times;
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
        while (getline(strstr,word, ',')) 
        {       	
        	if (j>3) { satellites[i][atoi(word.c_str())] = true; }
        	else if (j==0) { times[i] = atoi(word.c_str());}
        	else if (j==1) { possitions[i][0] = atof(word.c_str());}
        	else if (j==2) { possitions[i][1] = atof(word.c_str());}
        	else if (j==3) { possitions[i][2] = atof(word.c_str());}
        	//cout << word << '\n';
        	j++;
        }
       	i++;
    }
    cout << "Csv File read and vectors filled with values\n";
    ClientGpsData myClientGpsData(this->lines, times, possitions, satellites);
    cout << "created instance of ClientGpsData\n";
    return myClientGpsData;
}