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

			printFps();
			printPermaLogs();
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
		mvaddstr(15 + logEntry, 0,
				logs[(logEntry + logCycle) % logsSize].c_str());
	}
}
void UNGConsole::printFps() {
	int rowId = 0;
	for (auto const &x : fpsReports) {
		std::string row = x.first + " FPS: " + std::to_string(x.second);
		mvaddstr(5 + rowId, 0, row.c_str());
		rowId++;
	}
}

void UNGConsole::printPermaLogs() {
	int rowId = 0;
	for (auto const &x : permaLogs) {
		std::string row = x.first + ": " + x.second;
		mvaddstr(10 + rowId, 0, row.c_str());
		rowId++;
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
void UNGConsole::reportFps(std::string engineID, int fpsVal) {
	if (fpsReports.find(engineID) == fpsReports.end()) {
		fpsReports.insert(std::make_pair(engineID, 0));
	}
	fpsReports[engineID] = fpsVal;
}

void UNGConsole::setPermaLog(std::string logId, std::string logVal) {
	permaLogs[logId] = logVal;
}

void UNGConsole::deletePermaLog(std::string logId) {
	permaLogs.erase(logId);
}
