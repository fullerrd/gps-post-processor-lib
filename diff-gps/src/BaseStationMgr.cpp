#include "BaseStationMgr.h"

using namespace std;

BaseStationMgr::BaseStationMgr() {
	fileName = "./config/cors.log";
	countLines();
	initializeStationList();
}

void BaseStationMgr::countLines(){
	int number_of_lines = 0;
	string line;
	ifstream infile(this->fileName.c_str());
	while (getline(infile, line)) {
		++number_of_lines;
	}
	this->numStations = number_of_lines;
}

long double BaseStationMgr::calDist(vector<long double> pos1,vector<long double> pos2) {
	return sqrt(((pos1[0]-pos2[0])*(pos1[0]-pos2[0])) + ((pos1[1]-pos2[1])*(pos1[1]-pos2[1])) + ((pos1[2]-pos2[2])*(pos1[2]-pos2[2])));
}

BaseStation BaseStationMgr::nearestStation(vector<long double> clientEcef) {
	int size = baseStations.size();
	int closestStationElem = 0;
	long double minDist = calDist(baseStations[closestStationElem].getTrueEcefCoord(),clientEcef);
	for (int i =1 ; i<size; i++) {
		long double dist =calDist(baseStations[i].getTrueEcefCoord(),clientEcef);
		if (minDist>dist) {
			minDist = dist;
			cout<< minDist << " " << baseStations[i].getStationId() << "\n";
			closestStationElem = i;
		}
	}
	return baseStations[closestStationElem];
}

void BaseStationMgr::initializeStationList() {
	cout << "In initializeStationList() \n";
	//this->baseStations.resize(numStations);
	ifstream infile(this->fileName.c_str());
    //ifstream infile("loc_log__2014_62_1812.csv");
    string line = "";
    vector<long double> possitions;
    possitions.resize(3);
    string stationName = "stat";
    double someDouble = 0.0;
    vector<double> someMoreDoubles;
    someMoreDoubles.resize(3);
    //char someString;
    int i = 0;
    cout << "Reading Station configuration file\n";
    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";
        int j = 0;
        //cout << line << "\n";
        sscanf(line.c_str(), "%c%c%c%c %lf %Lf %Lf %Lf %lf %lf %lf\n",&stationName[0],&stationName[1],&stationName[2],&stationName[3],&someDouble,&possitions[0], &possitions[1], &possitions[2], &someMoreDoubles[0],&someMoreDoubles[1],&someMoreDoubles[2]);
        //string temp = (stationName[0] + stationName[1] + stationName[2] + stationName[3]);
        baseStations.push_back(BaseStation(possitions,stationName));
       	i++;
    }
    cout << "Size of vector<BaseStation> == " << baseStations.size() << "\n";
}

void BaseStationMgr::getNearestRinex(ClientGpsData& myClientGpsData) {
	vector<vector<long double> > clientEcef = myClientGpsData.getInitialCart();
	BaseStation station = nearestStation(clientEcef[0]);
	myClientGpsData.setNearestStationID(station.getStationId());
	myClientGpsData.setStationDist(calDist(station.getTrueEcefCoord(),clientEcef[0]));
	myClientGpsData.setStationCoords(station.getTrueEcefCoord());
	return;
}