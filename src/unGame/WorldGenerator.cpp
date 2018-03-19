/*
 * WorldGenerator.cpp
 *
 *  Created on: 19 mar 2018
 *      Author: ekammac
 */

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {

}

WorldGenerator::~WorldGenerator() {
}

World* WorldGenerator::generateWorld(TestConfigurations testConfiguration){
	World * tmpWorld =  new World();

	switch(testConfiguration) {
	case conf1Creature:
		break;
	case conf99Creatures:
		break;
	case conf1000Creatures:
		break;
	}

	return tmpWorld;
}

