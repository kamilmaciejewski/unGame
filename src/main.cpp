#include "main.h"

using namespace boost::program_options;

bool isRunning1 = true;

void runThread(vector<shared_ptr<Creature>> *vect, string engineId,
		chrono::duration<double> freq_) {
	vector<shared_ptr<Creature>>::iterator ptr;
	string id = engineId;
	chrono::duration<double> freq = freq_;
	int counter = 0;
	string lastId = "";
	cout << "Thr " << id << "start\n";
	while (isRunning1) {
//		this_thread::sleep_for(freq);
		counter = 0;
		lastId = "";
		for (ptr = vect->begin(); ptr < vect->end(); ptr++) {
			if ((*ptr) != nullptr) {
				counter++;
				(*ptr)->energy--;
				if (!(*ptr)->isAlive()) {
					cout << "Thr " << id << " delete ptr" << "\n";
					cout << "Thr " << id << " before delete: "
							<< (*ptr).use_count() << "\n";
					(*ptr) = nullptr;
					cout << "Thr " << id << " after delete: "
							<< (*ptr).use_count() << "\n";
					continue;
				}

			}
		}
//		cout << "Thr " << id << " Cnt:" << counter << ", last ID: " << lastId
//				<< "\n";

	}
	cout << "Thr" << id << " stop" << "\n";
}

int consoleTimeout = 0;
int main(int argc, const char *argv[])
try {
	settings = new Settings();
	if (!handleOptions(argc, argv)) {
		return 0;
	}

	auto console = LoggingHandler::getConsole();
//	auto logger = LoggingHandler::getLogger("MAIN");

	UNGame unGame(settings);
	unGame.run();
	console->run(consoleTimeout,settings);
	unGame.stop();

//	logger->log("Start");
//	MultiEngine multiEngine;
//
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
//	logger->log("Stop threads");
//	thread1.join();
//	thread2.join();
//	logger->log("Stop");

//	worldGenerator = new WorldGenerator();
//	logger->log("Generate world");

//	world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
//  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
//	world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf1KRandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf10KRandomCreatures);

//	logger->log("World set settings");
//	world->setSettings(settings);
//	logger->log("Starting");
//	ungEngine.run(world);
//	sdlEngine.run(world, settings);
//	neuralEngine.run(world);
//	console->run();
//	sdlEngine.stop();
//	ungEngine.close();
//	neuralEngine.close();
//	logger->log("Removing world...");
//	delete (world);
//	logger->log("Removing world generator");
//	delete worldGenerator;
//	logger->log("Removing settings handler");
	delete settings;
	settings = nullptr;
//	logger->log("Closed");
	console->close();
	delete console;
	sleep(1); //wait for loggers in destructors
	LoggingHandler::cleanup();
	return 0;
}
catch (const error &ex) {
	std::cerr << ex.what() << '\n';
}

bool handleOptions(int argc, const char *argv[]) {
	options_description desc { "Options" };
	desc.add_options()("help,h", "Help screen")("mode",
			value<std::string>()->default_value("gui"), "Mode")("timeout",
			value<int>(), "Timeout");

	variables_map params;
	store(parse_command_line(argc, argv, desc), params);
	notify(params);

	if (params.count("help")) {
		std::cout << desc << '\n';
		return false;
	}

	if (params.count("mode")) {
		std::string mode = params["mode"].as<std::string>();
		if (mode != "gui" && mode != "console") {
			std::cout << "Mode can be 'gui' or 'console'" << std::endl;
			return false;
		}
	}
	if (params.count("timeout")) {
		if (params["timeout"].as<int>() < 0) {
			std::cout << "Timeout needs to be a positive value" << std::endl;
			return false;
		}
		consoleTimeout = params["timeout"].as<int>();
	}

	std::string mode = params["mode"].as<std::string>();

	if (mode == "gui") {
		settings->mode = Settings::MODE::GUI;
	} else if (mode == "console") {
		settings->mode = Settings::MODE::CONSOLE;
	}


	return true;
}
