//#include "UNGLogger.h"
//UNGLogger* UNGLogger::instance = nullptr;
//
//UNGLogger* UNGLogger::getInstance() {
//	if (instance == nullptr) {
//		instance = new UNGLogger();
//	}
//return instance;
//}
//
//UNGLogger::UNGLogger() {
//}
//
//UNGLogger::~UNGLogger() {
//}
//void UNGLogger::registerEngine(UNG_Globals::engine engineID){
//	fpsReports.insert(std::make_pair(engineID, 0));
//}
//void UNGLogger::reportFPS(UNG_Globals::engine engineID, int fpsVal){
//	fpsReports[engineID]= fpsVal;
//}
//void UNGLogger::attachConsole(UNGConsole* consolePtr){
//	consoleHandler = consolePtr;
//}
