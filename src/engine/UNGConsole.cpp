#include "UNGConsole.h"
#include "SDL2/SDL.h"

UNGConsole::UNGConsole() {

}

UNGConsole::~UNGConsole() {
	while (!logqueue.empty()) {
		logqueue.pop();
	}
}
void UNGConsole::run() {
	initscr();
	cbreak();
	noecho();
	clear();
	halfdelay(5);
	int counter = 0;

	while (isRunning) {
		char ch = getch();
		if (ch == ERR) {
			erase();
			mvaddstr(0, 0, "Waiting");
			std::string cntStr = std::to_string(counter);
			mvaddstr(1, 0, cntStr.c_str());
			counter++;

			while (!logqueue.empty()) {
				log(logqueue.front());
				logqueue.pop();
			}

			printLogs();
			refresh();
		} else {
			isRunning = false;
		}
	}
	endwin();
}
void UNGConsole::log(std::string log) {
	logs[logCycle] = log;
	logCycle = (logCycle + 1) % logsSize;
}
void UNGConsole::printLogs() {
	for (int logEntry = 0; logEntry < logsSize; logEntry++) {
		mvaddstr(10 + logEntry, 0,
				logs[(logEntry + logCycle) % logsSize].c_str());
	}
}

void UNGConsole::close() {
	while (!logqueue.empty()) {
		log(logqueue.front());
		logqueue.pop();
	}
	for (int logEntry = 0; logEntry < logsSize; logEntry++) {
		if (!logs[(logEntry + logCycle) % logsSize].empty())
			std::cout << logs[(logEntry + logCycle) % logsSize] << std::endl;
	}
	std::cout << "Console closed" << std::endl;
}
