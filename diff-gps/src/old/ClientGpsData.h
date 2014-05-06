#ifndef CLIENTGPSDATA_H
#define CLIENTGPSDATA_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

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

    vector<long> theTime;
    vector<vector<double> > initialCart; //[N][AXES];
    vector<vector<double> > correctedCart; //[N][AXES];
    vector<vector<double> > initialGeo; //[N][AXES];
    vector<vector<double> > correctedGeo; //[N][AXES];
    vector<vector<bool> > satellites; //[N][M];
    vector<int8_t> flags; //[N];
    string inUnits;
    string outUnits;
    string nearestStationID;
    vector<double> stationCoords; //[AXES];
    double stationDist;

  public:
    ClientGpsData(int);

    ClientGpsData(int,vector<long>,vector<vector<double> >,vector<vector<bool> >);

    vector<long> getTheTime();
    void setTheTime(const vector<long>&);

    vector<int8_t> getFlags();
    void setFlags(const vector<int8_t>&);

    vector<vector<double> > getInitialCart();
    void setInitialCart(const vector<vector<double> >&);

    vector<vector<double> > getCorrectedCart();
    void setCorrectedCart(const vector<vector<double> >&);

    vector<vector<double> > getInitialGeo();
    void setInitialGeo(const vector<vector<double> >&);

    vector<vector<double> > getCorrectedGeo();
    void setCorrectedGeo(const vector<vector<double> >&);

    string getInUnits();
    void setInUnits(const string&);

    string getOutUnits();
    void setOutUnits(const string&);

    string getNearestStationID();
    void setNearestStationID(const string&);

    vector<double> getStationCoords();
    void setStationCoords(const vector<double>&);

    double getStationDist();
    void setStationDist(const double&);

    vector<vector<bool> > getSatellites();
    void setSatellites( const vector<vector<bool> >&);
};

#endif
