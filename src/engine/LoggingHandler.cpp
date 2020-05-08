#include "LoggingHandler.h"
UNGConsole *LoggingHandler::consoleHandler = nullptr;

UNGLogger* LoggingHandler::getLogger(std::string engineID) {

	if (consoleHandler == nullptr) {
		consoleHandler = new UNGConsole();
	}
	return new UNGLogger(engineID, consoleHandler);

}
UNGConsole* LoggingHandler::getConsole() {
	if (consoleHandler == nullptr) {
		consoleHandler = new UNGConsole();
	}
	return consoleHandler;
}
