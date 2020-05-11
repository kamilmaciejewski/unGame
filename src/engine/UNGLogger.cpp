#include "UNGLogger.h"

UNGLogger::UNGLogger(std::string engineID_, UNGConsole *console) {
	engineID = engineID_ + " engine";
	consoleHandler = console;
//	console->registerLogger(engineID_);
}

UNGLogger::~UNGLogger() {
}
//void UNGLogger::registerEngine(UNG_Globals::engine engineID){
//	fpsReports.insert(std::make_pair(engineID, 0));
//}
void UNGLogger::reportFps(int fpsVal) {
	consoleHandler->reportFps(engineID, fpsVal);
}

void UNGLogger::log(std::string message) {
	consoleHandler->logqueue.push(engineID + ": " + message);
}

void UNGLogger::addPermaLog(std::string logId) {
	consoleHandler->addPermaLog(engineID+ ": " + logId);
}
void UNGLogger::setPermaLog(std::string logId, std::string logVal) {
	consoleHandler->setPermaLog(engineID+ ": " + logId, logVal);
}
void UNGLogger::deletePermaLog(std::string logId) {
	consoleHandler->deletePermaLog(engineID+ ": " + logId);
}
