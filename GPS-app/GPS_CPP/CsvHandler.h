#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <limits>
#include "ClientGpsData.h"

using namespace std;

class CsvHandler {
private:
	ClientGpsData readCsv();
	void numLines();
	string infile;
	int lines;
public:
	CsvHandler(string);
	CsvHandler();
	string doubleToText(const double &);
	ClientGpsData getClientData();
	ClientGpsData getClientData(string);
	void setFileName(string);
	string runOutput();
	void writeCsv(ClientGpsData);
};

#endif