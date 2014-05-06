#ifndef CLIENTGPSDATA_H
#define CLIENTGPSDATA_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

class ClientGpsData {

  private:
    // TODO: fix these; we need consts for declaring length of member arrays,
    // and we have them in our initial design, but what do they need to be?
    //
    // "N" replaces "0..n" from the diagram
    // "M" replaces "0..m"
    // "AXES" replaces "3", I'm pretty sure this was because it's for
    //   3-dimensional coordinates
    int N;
    static const int M = 86;
    static const int AXES = 3;

    vector<long long> theTime;
    vector<vector<long double> > initialCart; //[N][AXES];
    vector<vector<long double> > correctedCart; //[N][AXES];
    vector<vector<long double> > initialGeo; //[N][AXES];
    vector<vector<long double> > correctedGeo; //[N][AXES];
    vector<vector<bool> > satellites; //[N][M];
    vector<int8_t> flags; //[N];
    string inUnits;
    string outUnits;
    string nearestStationID;
    vector<long double> stationCoords; //[AXES];
    double stationDist;

  public:
    ClientGpsData(int,vector<long long>,vector<vector<long double> >,vector<vector<bool> >);
    
    ClientGpsData(int);

    vector<long long> getTheTime();
    void setTheTime(const vector<long long>&);

    vector<int8_t> getFlags();
    void setFlags(const vector<int8_t>&);

    vector<vector<long double> > getInitialCart();
    void setInitialCart(const vector<vector<long double> >&);

    vector<vector<long double> > getCorrectedCart();
    void setCorrectedCart(const vector<vector<long double> >&);

    vector<vector<long double> > getInitialGeo();
    void setInitialGeo(const vector<vector<long double> >&);

    vector<vector<long double> > getCorrectedGeo();
    void setCorrectedGeo(const vector<vector<long double> >&);

    string getInUnits();
    void setInUnits(const string&);

    string getOutUnits();
    void setOutUnits(const string&);

    string getNearestStationID();
    void setNearestStationID(const string&);

    vector<long double> getStationCoords();
    void setStationCoords(const vector<long double>&);

    long double getStationDist();
    void setStationDist(const long double&);

    vector<vector<bool> > getSatellites();
    void setSatellites( const vector<vector<bool> >&);
};

#endif
