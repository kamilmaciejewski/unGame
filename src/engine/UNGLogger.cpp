#include "UNGLogger.h"

UNGLogger::UNGLogger(std::string engineID_, UNGConsole *console) {
	engineID = engineID_;
	consoleHandler = console;
}

UNGLogger::~UNGLogger() {
}
//void UNGLogger::registerEngine(UNG_Globals::engine engineID){
//	fpsReports.insert(std::make_pair(engineID, 0));
//}
void UNGLogger::reportFPS(int fpsVal) {
//	fpsReports[engineID]= fpsVal;
}

void UNGLogger::log(std::string message) {
	consoleHandler->logqueue.push(engineID + ": " + message);
}
