#ifndef UNG_UNGLogger_H_
#define UNG_UNGLogger_H_

#include <string>
#include "UNGConsole.h"
#include "Globals.h"

class UNGLogger {
public:
	~UNGLogger();
	void reportFps(int);
	void log(std::string);
	UNGLogger(std::string, UNGConsole*);
private:
	std::string engineID;
	UNGConsole *consoleHandler;
};

#endif /* UNG_UNGLogger_H_ */