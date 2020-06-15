#ifndef UNGLOGGINGHANDLER_H_
#define UNGLOGGINGHANDLER_H_

#include "UNGLogger.h"
#include "map"
using namespace std;
class LoggingHandler {
public:
	static UNGLogger* getLogger(std::string);
	static UNGConsole* getConsole();
	static void cleanup(); //TODO: use shared pointers
private:
	static UNGConsole* consoleHandler;
	static map<string, UNGLogger*> *loggers;

};

#endif /* UNGLOGGINGHANDLER_H_ */
