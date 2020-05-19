#include "unGame.h"

using namespace boost::program_options;

int main(int argc, const char *argv[])
try {
	settings = new Settings();
	if(!handleOptions(argc, argv)){
		return 0;
	}

	auto console = LoggingHandler::getConsole();
	auto logger = LoggingHandler::getLogger("MAIN");

	logger->log("Start world generator");
	worldGenerator = new WorldGenerator();
	logger->log("Generate world");

//	world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
//	world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf1KRandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf10KRandomCreatures);

	logger->log("World set settings");
	world->setSettings(settings);
	logger->log("Starting");
	ungEngine.run(world);
	sdlEngine.run(world, settings);
	neuralEngine.run(world);
	console->run();
	sdlEngine.stop();
	ungEngine.close();
	neuralEngine.close();
	logger->log("Removing world...");
	delete (world);
	logger->log("Removing world generator");
	delete (worldGenerator);
	logger->log("Removing settings handler");
	delete (settings);
	logger->log("Closed");
	console->close();
	delete console;
	return 0;

}
catch (const error &ex) {
	std::cerr << ex.what() << '\n';
}

//using namespace boost::program_options;
bool handleOptions(int argc, const char *argv[]) {
	options_description desc { "Options" };
	desc.add_options()("help,h", "Help screen")("mode",
			value<std::string>()->default_value("gui"), "Mode");

	variables_map params;
	store(parse_command_line(argc, argv, desc), params);
	notify(params);

	if (params.count("help")) {
		std::cout << desc << '\n';
		return false;
	} else if (params.count("mode")) {
		std::string mode = params["mode"].as<std::string>();
		if (mode != "gui" && mode != "console") {
			std::cout << "Mode can be 'gui' or 'console'" << std::endl;
			return false;
		}
	}
	std::string mode = params["mode"].as<std::string>();

	if (mode == "gui") {
		settings->mode = Settings::MODE::GUI;
	} else if (mode == "console") {
		settings->mode = Settings::MODE::CONSOLE;
	}

	return true;
}
