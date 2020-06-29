#include <UNGLoggingHandler.h>

UNGConsole *LoggingHandler::consoleHandler = nullptr;
map<string, UNGLogger*> *LoggingHandler::loggers = nullptr;

UNGLogger* LoggingHandler::getLogger(std::string engineID) {

	if (consoleHandler == nullptr) {
		consoleHandler = new UNGConsole();
	}
	if (loggers == nullptr) {
		loggers = new map<string, UNGLogger*>();
	}
	if (!(*loggers).contains(engineID)) {
		(*loggers)[engineID] = new UNGLogger(engineID, consoleHandler);
	}
	return (*loggers)[engineID];

}
UNGConsole* LoggingHandler::getConsole() {
	if (consoleHandler == nullptr) {
		consoleHandler = new UNGConsole();
	}
	return consoleHandler;
}
void LoggingHandler::cleanup() {
	if (loggers == nullptr) {
		return;
	}
	for (auto logger : *loggers) {
		delete logger.second;
		logger.second = nullptr;
	}
	delete loggers;
	loggers = nullptr;
}
