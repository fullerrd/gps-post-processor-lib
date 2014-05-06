#ifndef UNIT_CONVERTER
#define UNIT_CONVERTER

#include <sstream>
#include <vector>
#include "Position.hpp"
#include "WGS84Ellipsoid.hpp"
#include "CommonTime.hpp"
#include "UnixTime.hpp"

using namespace std;

// facade class for some of GPSTk's coordinate and time conversion functionality
class UnitConverter {
private:
	//gpstk::UnixTime ut();
public:
	UnitConverter();
	static vector<long double> geoToCart(long double, long double, long double); // Geodetic WGS84 Ellipsoid (degrees/meters) to ECEF Cartesian (meters)
	static vector<long double> cartToGeo(long double, long double, long double); // ECEF Cartesian (meters) to Geodetic WGS84 Ellipsoid (degrees/meters)
	static string getYear(long long unixTime);
	static string getDayOfYear(long long unixTime);
	static gpstk::CommonTime getCommonTime(long long unixTime);
	static long long getUnixTime(gpstk::CommonTime commonTime);

};

#endif
