#ifndef BaseStation_H
#define BaseStation_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class BaseStation {

  private:
  	vector<long double> trueEcefCoord;
  	string stationId;
  public:
  	BaseStation();
  	BaseStation(vector<long double>,string);
  	string getStationId();
  	vector<long double> getTrueEcefCoord();
  	void setTrueEcefCoord(vector<long double>);
  	void setStationId(string);
};
#endif