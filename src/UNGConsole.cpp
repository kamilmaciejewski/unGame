#include "UNGConsole.h"

UNGConsole::~UNGConsole() {
	while (!logqueue.empty()) {
		logqueue.pop();
	}
}

void UNGConsole::run(int timeout, Settings *settings) {
	initscr();
	cbreak();
	noecho();
	clear();
	halfdelay(10);
	int counter = 0;

	while (isRunning && (counter++ < timeout || timeout == 0)) {
		char ch = getch();
		if (ch == ERR) {
			erase();
			mvaddstr(0, 0,
					("Running for " + std::to_string((int )(counter / 3600))
							+ "h:" + std::to_string((int )((counter / 60) % 60))
							+ "m:" + std::to_string(counter % 60) + "s").c_str());

			while (!logqueue.empty()) {
				log(logqueue.front());
				logqueue.pop();
			}

			printFps();
			printPermaLogs();
			printLogs();
			printInfo();
			refresh();
		} else if (ch == 27) {
			isRunning = false;
		} else if (ch == 45) {
			settings->timeScale -= 0.1;
		} else if (ch == 43) {
			settings->timeScale += 0.1;
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
		mvaddstr(20 + logEntry, 0,
				logs[(logEntry + logCycle) % logsSize].c_str());
	}
}

void UNGConsole::printInfo() {
	int rowid = 40;
	mvaddstr(rowid++, 0, "Usage in Console window:");
	mvaddstr(rowid++, 0, "ESC: exit");
	mvaddstr(rowid++, 0, "+/-: time scale");
	rowid++;
	mvaddstr(rowid++, 0, "Usage in GUI window:");
	mvaddstr(rowid++, 0, "V: draw vectors toggle,  T: draw textures toggle");
	mvaddstr(rowid++, 0, "R: rotate toggle,        M: move toggle");
	mvaddstr(rowid++, 0,
			"L: look toggle,          C: add creature/plant toggle");
	mvaddstr(rowid++, 0, "ESC: close GUI window");
	mvaddstr(rowid++, 0, "LMB: mark active object, RMB: add creature/plant");
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
