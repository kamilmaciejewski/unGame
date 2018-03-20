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
		conf1Creature = 1,
		conf99RandomCreatures = 99,
		conf1000RandomCreatures = 1000,
	};

	WorldGenerator();
	virtual ~WorldGenerator();
	World* generateWorld(TestConfigurations);
	Creature * generateCreature(TestConfigurations &);
};

#endif /* UNGAME_WORLDGENERATOR_H_ */
