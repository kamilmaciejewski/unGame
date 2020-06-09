#ifndef MULTIENGINE_H_
#define MULTIENGINE_H_

#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <atomic>
#include <map>

#include "UNGLoggingHandler.h"
#include "UNGCreature.h"

using namespace std;
//class Foo {
//public:
//	atomic_int bar { 5 };
//	string id;
//
//	Foo(int bar, string id);
//
//	void doSmtn(string from);
//
//	~Foo();
//	bool isAlive();
//};

class MultiEngine {
public:
	map<string, vector<shared_ptr<Creature>>*> vectors;

	MultiEngine();
	virtual ~MultiEngine();

	vector<shared_ptr<Creature>>* registerEngine(string id);
	bool addFooReuse(vector<shared_ptr<Creature>> *vect, shared_ptr<Creature> foo);
	void addFoo(int bar, int id);
	private:
	const uint8_t vectSize = 100;
	UNGLogger* logger;
};
#endif /* MULTIENGINE_H_ */
