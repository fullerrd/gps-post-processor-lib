#include "ClientGpsData.h"
#include <stdlib.h>

using namespace std;

ClientGpsData::ClientGpsData(int length ) {
	this->N = length;
}

ClientGpsData::ClientGpsData(int length, vector<long> theTime, vector<vector<double> > initialCoords, vector<vector<bool> > satellites) {
	this->N = length;
	cout << "set length\n";
	this->theTime = theTime;
	cout << "set time\n";
	this->satellites = satellites;
	cout << "set satellites\n";
	cout << initialCoords.size() << "\n";
	if (initialCoords[0][0] <  91.0) {
		this->initialGeo = initialCoords;
		this->inUnits = "Geo";
	}
	else {
		this->initialCart = initialCoords;
		this->inUnits = "Cart";
	}
	cout << "set init coords\n";
}

vector<long> ClientGpsData::getTheTime() {
	return this->theTime;
}
void ClientGpsData::setTheTime(const vector<long>& theTime){
	this->theTime = theTime;
}

vector<int8_t> ClientGpsData::getFlags() {
	return this->flags;
}
void ClientGpsData::setFlags(const vector<int8_t>& flags) {
	this->flags = flags;
}

vector<vector<double> > ClientGpsData::getInitialCart() {
	return this->initialCart;
}
void ClientGpsData::setInitialCart(const vector<vector<double> >& initialCart) {
	this->initialCart = initialCart;
}

vector<vector<double> > ClientGpsData::getCorrectedCart() {
	return this->correctedCart;
}
void ClientGpsData::setCorrectedCart(const vector<vector<double> >& correctedCart) {
	this->correctedCart = correctedCart;
}

vector<vector<double> > ClientGpsData::getInitialGeo() {
	return this->initialGeo;
}
void ClientGpsData::setInitialGeo(const vector<vector<double> >& initialGeo) {
	this-> initialGeo = initialGeo;
}

vector<vector<double> > ClientGpsData::getCorrectedGeo() {
	return this->correctedGeo;
}
void ClientGpsData::setCorrectedGeo(const vector<vector<double> >& correctedGeo) {
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

vector<double> ClientGpsData::getStationCoords() {
	return this->stationCoords;
}
void ClientGpsData::setStationCoords(const vector<double>& stationCoords){
	this->stationCoords = stationCoords;
}

double ClientGpsData::getStationDist() {
	return this->stationDist;
}
void ClientGpsData::setStationDist(const double& stationDist) {
	this->stationDist = stationDist;
}

vector<vector<bool> > ClientGpsData::getSatellites() {
	return this->satellites;
}
void ClientGpsData::setSatellites( const vector<vector<bool> >& satellites){
	this->satellites = satellites;
}
