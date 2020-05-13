#ifndef UNGLOGGINGHANDLER_H_
#define UNGLOGGINGHANDLER_H_

#include "UNGLogger.h"

class LoggingHandler {
public:
	static UNGLogger* getLogger(std::string);
	static UNGConsole* getConsole();
private:
	static UNGConsole* consoleHandler;
};

#endif /* UNGLOGGINGHANDLER_H_ */
