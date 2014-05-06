#ifndef RINEXMGR_H
#define RINEXMGR_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "ClientGpsData.h"
#include "UnitConverter.h"

// Classes for handling observations RINEX files (data)
#include "Rinex3ObsHeader.hpp"
#include "Rinex3ObsData.hpp"
#include "Rinex3ObsStream.hpp"

// Classes for handling satellite navigation parameters RINEX
   // files (ephemerides)
#include "Rinex3NavHeader.hpp"
#include "Rinex3NavData.hpp"
#include "Rinex3NavStream.hpp"

// Class for storing "broadcast-type" ephemerides
#include "GPSEphemerisStore.hpp"

// Class for handling RAIM
#include "PRSolution2.hpp"

   // Class defining GPS system constants
#include "GNSSconstants.hpp"


using namespace std;

class RinexMgr{
	private:
		
	public:
		RinexMgr();
		void possitionSolution(ClientGpsData&);

};
#endif
