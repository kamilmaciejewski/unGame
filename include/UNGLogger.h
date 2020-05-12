#ifndef UNG_UNGLogger_H_
#define UNG_UNGLogger_H_

#include <string>
#include "UNGConsole.h"
#include "Globals.h"
//class UNGPermaLog{
//	public:
//};
class UNGLogger {
public:
	UNGLogger(std::string, UNGConsole*);
	~UNGLogger();

	void reportFps(int);
	void log(std::string);
	void setPermaLog(std::string, std::string);
	void deletePermaLog(std::string);
private:
	std::string engineID;
	UNGConsole *consoleHandler;
};

#endif /* UNG_UNGLogger_H_ */
