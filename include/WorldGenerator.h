/*
 * WorldGenerator.h
 *
 *  Created on: 19 mar 2018
 *      Author: ekammac
 */

#ifndef UNGAME_WORLDGENERATOR_H_
#define UNGAME_WORLDGENERATOR_H_

#include "world.h"
class WorldGenerator {
public:
	enum TestConfigurations{
		conf1Creature = 0,
		conf99Creatures = 1,
		conf1000Creatures = 2,
	};

	WorldGenerator();
	virtual ~WorldGenerator();
	World* generateWorld(TestConfigurations );
};

#endif /* UNGAME_WORLDGENERATOR_H_ */
