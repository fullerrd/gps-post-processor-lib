#ifndef DOWNLOADMGR_H
#define DOWNLOADMGR_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "FileSystemMgr.h"

using namespace std;

class DownloadMgr{
public:
	void downloadRinex(string, long long , string);
};
#endif