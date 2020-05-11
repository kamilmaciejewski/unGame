#ifndef SRC_UNGCONSOLE_H_
#define SRC_UNGCONSOLE_H_

#include <map>
#include <ncurses.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include "Globals.h"

struct UNGConsoleEntry{
	UNG_Globals::engine engineId;
	std::string message;
};

class UNGConsole {
	friend class UNGLogger;
	bool isRunning = true;
	const int logsSize = 10;
	std::string logs [10];
	std::map<std::string, int> fpsReports;
	int logCycle = 0;
	void printLogs();
	void printFps();
	std::queue<std::string> logqueue;
//	void registerLogger(std::string);
	void reportFps(std::string, int);
public:
	UNGConsole();
	virtual ~UNGConsole();
	void run();
	void log(std::string);
	void close();
};

#endif /* SRC_UNGCONSOLE_H_ */

