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
	std::map<std::string, std::string> permaLogs;
	int logCycle = 0;
	void printLogs();
	void printInfo();
	void printFps();
	void printPermaLogs();
	std::queue<std::string> logqueue;
	void reportFps(std::string, int);
	void addPermaLog(std::string);
	void setPermaLog(std::string, std::string);
	void deletePermaLog(std::string);

public:
	UNGConsole();
	virtual ~UNGConsole();
	void run();
	void log(std::string);
	void close();
};

#endif /* SRC_UNGCONSOLE_H_ */

