#include "ClientGpsData.h"
#include <stdlib.h>

using namespace std;



ClientGpsData::ClientGpsData(int length, vector<long long> theTime, vector<vector<long double> > initialCoords, vector<vector<bool> > satellites) {
	this->N = length;
	cout << "set length\n";
	this->theTime = theTime;
	cout << "set time\n";
	this->satellites = satellites;
	vector<int8_t> flg_vec;
	//this->flags = flg_vec;
	this->flags.resize(length);
	cout << "set satellites\n";
	cout << initialCoords.size() << "\n";
	cout << length << "\n";
	cout << theTime.size() << "\n";
	cout << satellites.size() << "\n";
	if (initialCoords[0][0] <  91.0) {
		this->initialGeo = initialCoords;
		this->correctedGeo = initialCoords;
		this->inUnits = "Geo";
	}
	else {
		this->initialCart = initialCoords;
		this->correctedCart = initialCoords;
		this->inUnits = "Cart";
	}
	cout << "set init coords\n";
}
ClientGpsData::ClientGpsData(int length ) {
	this->N = length;
}
vector<long long> ClientGpsData::getTheTime() {
	return this->theTime;
}
void ClientGpsData::setTheTime(const vector<long long>& theTime){
	this->theTime = theTime;
}

vector<int8_t> ClientGpsData::getFlags() {
	return this->flags;
}
void ClientGpsData::setFlags(const vector<int8_t>& flags) {
	this->flags = flags;
}

vector<vector<long double> > ClientGpsData::getInitialCart() {
	return this->initialCart;
}
void ClientGpsData::setInitialCart(const vector<vector<long double> >& initialCart) {
	this->initialCart = initialCart;
}

vector<vector<long double> > ClientGpsData::getCorrectedCart() {
	return this->correctedCart;
}
void ClientGpsData::setCorrectedCart(const vector<vector<long double> >& correctedCart) {
	this->correctedCart = correctedCart;
}

vector<vector<long double> > ClientGpsData::getInitialGeo() {
	return this->initialGeo;
}
void ClientGpsData::setInitialGeo(const vector<vector<long double> >& initialGeo) {
	this-> initialGeo = initialGeo;
}

vector<vector<long double> > ClientGpsData::getCorrectedGeo() {
	return this->correctedGeo;
}
void ClientGpsData::setCorrectedGeo(const vector<vector<long double> >& correctedGeo) {
	this->correctedGeo = correctedGeo;
}

string ClientGpsData::getInUnits() {
	return this->inUnits;
}
void ClientGpsData::setInUnits(const string& inUnits) {
	this->inUnits = inUnits;
}

string ClientGpsData::getOutUnits() {
	return this->outUnits;
}
void ClientGpsData::setOutUnits(const string& outUnits) {
	this->outUnits = outUnits;
}

string ClientGpsData::getNearestStationID() {
	return this->nearestStationID;
}
void ClientGpsData::setNearestStationID(const string& nearestStationID) {
	this->nearestStationID = nearestStationID;
}

vector<long double> ClientGpsData::getStationCoords() {
	return this->stationCoords;
}
void ClientGpsData::setStationCoords(const vector<long double>& stationCoords){
	this->stationCoords = stationCoords;
}

long double ClientGpsData::getStationDist() {
	return this->stationDist;
}
void ClientGpsData::setStationDist(const long double& stationDist) {
	this->stationDist = stationDist;
}

vector<vector<bool> > ClientGpsData::getSatellites() {
	return this->satellites;
}
void ClientGpsData::setSatellites( const vector<vector<bool> >& satellites){
	this->satellites = satellites;
}
