#ifndef UNGLogger_H_
#define UNGLogger_H_

#include <string>

#include "UNGConsole.h"
#include "UNGGlobals.h"

class UNGLogger {
public:
	UNGLogger(std::string, UNGConsole*);
	~UNGLogger() = default;

	void reportFps(int);
	void log(std::string);
	void setPermaLog(std::string, std::string);
	void deletePermaLog(std::string);

private:
	std::string engineID;
	UNGConsole *consoleHandler;
};

#endif /* UNGLogger_H_ */
