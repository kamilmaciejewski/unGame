#ifndef SRC_UNGCONSOLE_H_
#define SRC_UNGCONSOLE_H_

#include <ncurses.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

class UNGConsole {
	bool isRunning = true;
	const int logsSize = 10;
	std::string logs [10];
	int logCycle = 0;
	void printLogs();
public:
	UNGConsole();
	virtual ~UNGConsole();
	void run();
	void log(std::string);
	std::queue<std::string> logqueue;
	void close();

};

#endif /* SRC_UNGCONSOLE_H_ */
