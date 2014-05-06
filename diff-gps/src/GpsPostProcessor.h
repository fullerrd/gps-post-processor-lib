#ifndef GPSPOSTPROCESSOR_H
#define GPSPOSTPROCESSOR_H

#include "CsvHandler.h"
#include "ClientGpsData.h"
#include "UnitConverter.h"
#include "FileSystemMgr.h"
#include "BaseStationMgr.h"
#include "RinexMgr.h"
#include <vector>
#include <stdint.h>

class GpsPostProcessor {

  private:
    GpsPostProcessor() {};
    GpsPostProcessor(GpsPostProcessor const&);
    GpsPostProcessor& operator=(GpsPostProcessor const&);
    CsvHandler myCsvHandler;

    BaseStationMgr bsMgr;
    // CsvHandler *        csvHandler;
    // DownloadMgr *       dlMgr;
    
    RinexMgr rnxMgr;

  public:
    FileSystemMgr     fsMgr;

    static GpsPostProcessor& getInstance();
    void runPostProcessor(string);
    // void submitCsv(ifstream csvData);
};

#endif
