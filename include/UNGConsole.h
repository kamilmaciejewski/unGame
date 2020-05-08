#ifndef SRC_UNGCONSOLE_H_
#define SRC_UNGCONSOLE_H_

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
	int logCycle = 0;
	void printLogs();
	std::queue<std::string> logqueue;
public:
	UNGConsole();
	virtual ~UNGConsole();
	void run();
	void log(std::string);
	void close();
};

#endif /* SRC_UNGCONSOLE_H_ */
