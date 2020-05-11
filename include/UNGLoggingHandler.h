#ifndef SRC_ENGINE_LOGGINGHANDLER_H_
#define SRC_ENGINE_LOGGINGHANDLER_H_

#include "UNGLogger.h"

class LoggingHandler {
public:
	static UNGLogger* getLogger(std::string);
	static UNGConsole* getConsole();
private:
	static UNGConsole* consoleHandler;
};

#endif /* SRC_ENGINE_LOGGINGHANDLER_H_ */
