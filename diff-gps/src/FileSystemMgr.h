#ifndef FILESYSTEMMGR_H
#define FILESYSTEMMGR_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

class FileSystemMgr{
	private:
		string getPartialRinexUrl(string stationID, long long ut);

	public:
		FileSystemMgr();
		static string getRinexUrl(string stationID, long long ut); //string stationID, long ut
		static string getAltRinexUrl(string stationID, long long ut);
		static string getRinexDir();
		static string getRinexFileName(string stationID, long long ut, string fileType);
		static string getRinexPath(string stationID, long long ut);
};

#endif