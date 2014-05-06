LIBS=-lgpstk
I_PATH=-Igpstk/src/

all:
	g++ -c src/ClientGpsData.cpp -o build/ClientGpsData.o $(LIBS) $(I_PATH)
	g++ -c src/CsvHandler.cpp -o build/CsvHandler.o $(LIBS) $(I_PATH)
	g++ -c src/FileSystemMgr.cpp -o build/FileSystemMgr.o $(LIBS) $(I_PATH)
	g++ -c src/BaseStation.cpp -o build/BaseStation.o $(LIBS) $(I_PATH)
	g++ -c src/BaseStationMgr.cpp -o build/BaseStationMgr.o $(LIBS) $(I_PATH)
	g++ -c src/UnitConverter.cpp -o build/UnitConverter.o $(LIBS) $(I_PATH)
	g++ -c src/RinexMgr.cpp -o build/RinexMgr.o $(LIBS) $(I_PATH)
	g++ -c src/DownloadMgr.cpp -o build/DownloadMgr.o $(LIBS) $(I_PATH)
	g++ src/GpsPostProcessor.cpp src/ClientGpsData.cpp src/CsvHandler.cpp src/UnitConverter.cpp src/FileSystemMgr.cpp src/BaseStation.cpp src/BaseStationMgr.cpp src/RinexMgr.cpp -o build/GpsPostProcessor $(LIBS) $(I_PATH)
clean:
	rm build/*
