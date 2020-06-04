#ifndef UNGCONSOLE_H_
#define UNGCONSOLE_H_

#include <iostream>
#include <map>
#include <ncurses.h>
#include <string>
#include <vector>
#include <queue>

#include "SDL2/SDL.h"
#include "UNGGlobals.h"

struct UNGConsoleEntry{
	UNG_Globals::engine engineId;
	std::string message;
};

class UNGConsole {
	friend class UNGLogger;
	bool isRunning = true;
	int logCycle = 0;
	const int logsSize = 10;
	std::queue<std::string> logqueue;
	std::map<std::string, int> fpsReports;
	std::map<std::string, std::string> permaLogs;

	std::string logs [15];
	void printLogs();
	void printInfo();
	void printFps();
	void printPermaLogs();
	void reportFps(std::string, int);
	void addPermaLog(std::string);
	void setPermaLog(std::string, std::string);
	void deletePermaLog(std::string);

public:
	UNGConsole() = default;
	virtual ~UNGConsole();
	void run();
	void log(std::string);
	void close();
};

#endif /* UNGCONSOLE_H_ */

