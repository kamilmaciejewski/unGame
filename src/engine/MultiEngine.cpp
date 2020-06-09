#include "MultiEngine.h"

//	Foo::Foo(int bar, string id) {
//		this->bar = bar;
//		this->id = id;
//	}
//
//	void Foo::doSmtn(string from) {
//		cout << "Foo: Do: " << id << " from " << from << ", bar: " << bar << endl;
//	}
//
//	Foo::~Foo() {
//		cout << "Foo: Destructor: " << id << ", bar: " << bar << endl;
//	}
//	bool Foo::isAlive() {
//		return bar > 0;
//	}
	MultiEngine::MultiEngine(){
		logger = LoggingHandler::getLogger("MULTIENG");
		logger->log("Start");
	}

	MultiEngine::~MultiEngine(){
		logger->log("Stop");
		delete logger;
		logger = nullptr;
	}
	vector<shared_ptr<Creature>>* MultiEngine::registerEngine(string id) {
		vector<shared_ptr<Creature>> *vect = new vector<shared_ptr<Creature>>();
		vect->reserve(vectSize);
		logger->log("Added v " + id);
		vectors.insert(make_pair("v" + id, vect));
		return vect;
	}
	bool MultiEngine::addFooReuse(vector<shared_ptr<Creature>> *vect, shared_ptr<Creature> foo) {
		for (vector<shared_ptr<Creature>>::iterator ptr = vect->begin();
				ptr < vect->end(); ptr++) {
			if ((*ptr) == nullptr) {
				logger->log("Found slot");
				(*ptr) = foo;
				return true;
			}
		}
		logger->log("Slot not found for");
		return false;
	}

	void MultiEngine::addFoo(int bar, int id) {
		NeuralParams params;
		shared_ptr<Creature> foo = make_shared<Creature>(nullptr, params);
		for (auto vect : vectors) {
			if (!addFooReuse(vect.second, foo)) {
				logger->log("Push  to: " + vect.first);
				vect.second->push_back(foo);

			}
		}
//		foo = nullptr;
	}
//main:
//bool isRunning1 = true;
//
//void runThread(vector<shared_ptr<Foo>> *vect, string engineId,
//		chrono::duration<double> freq_) {
//	vector<shared_ptr<Foo>>::iterator ptr;
//	string id = engineId;
//	chrono::duration<double> freq = freq_;
//	int counter = 0;
//	string lastId = "";
//	cout << "Thr " << id << "start\n";
//	while (isRunning1) {
//		this_thread::sleep_for(freq);
//		counter = 0;
//		lastId = "";
//		for (ptr = vect->begin(); ptr < vect->end(); ptr++) {
//			if ((*ptr) != nullptr) {
//				lastId = (*ptr)->id;
//				counter++;
//				(*ptr)->bar--;
//				(*ptr)->doSmtn(id);
//				if (!(*ptr)->isAlive()) {
//					cout << "Thr " << id << " delete ptr" << "\n";
//					cout << "Thr " << id << " before delete: "
//							<< (*ptr).use_count() << "\n";
//					(*ptr) = nullptr;
//					cout << "Thr " << id << " after delete: "
//							<< (*ptr).use_count() << "\n";
//					continue;
//				}
//
//			}
//		}
//		cout << "Thr " << id << " Cnt:" << counter << ", last ID: " << lastId
//				<< "\n";
//
//	}
//	cout << "Thr" << id << " stop" << "\n";
//}
//
//int main() {
//
//	MultiEngine multiEngine;
//	auto v1 = multiEngine.registerEngine("th1");
//	auto v2 = multiEngine.registerEngine("th2");
//	thread thread1(runThread, v1, "1", chrono::duration<double> { 1000ms });
//	thread thread2(runThread, v2, "2", chrono::duration<double> { 2000ms });
//
//	int count = 0;
//	while (count < 5) {
//		count++;
//		multiEngine.addFoo(10 + count, count);
//		sleep(5);
//	}
//	isRunning1 = false;
//	cout << "Stop threads:" << "\n";
//	thread1.join();
//	thread2.join();
//	cout << "Stop" << "\n";
//	return 0;
//}
