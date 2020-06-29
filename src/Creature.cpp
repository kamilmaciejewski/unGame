#include <UNGCreature.h>
#include <UNGLoggingHandler.h>

#include <sstream> //for std::stringstream temp
#include <string>  //for std::string temp

Creature::Creature(SDL_Surface *surfaceptr, NeuralParams params, uint64_t id) {
	this->id = id;
	parentId = id;
	ancessorId = id;
	neuralNet = new UNGNeuralNetwork(params);
	multiview = new std::vector<UNG_Vector*>();
	multiview->reserve(genotype.maxViewEntries);
	surface = surfaceptr;
}

Creature::Creature(const Creature &creature, uint64_t id){
	this->id = id;
	parentId = creature.id;
	ancessorId = creature.ancessorId;
	neuralNet = new UNGNeuralNetwork(*creature.neuralNet);
	multiview = new std::vector<UNG_Vector*>();
	genotype = creature.genotype;
	multiview->reserve(genotype.maxViewEntries);
	surface = creature.surface;
	energy = creature.energy;
	pos = creature.pos;
	drawable->rot_angle = creature.drawable->rot_angle;
	generations = creature.generations + 1;
}

Creature::~Creature() {
//	auto logger = LoggingHandler::getLogger("CR");
//	const void *address = static_cast<const void*>(this);
//	std::stringstream ss;
//	ss << address;
//	std::string name = ss.str();
//	if (logger != nullptr) {
//		logger->log("Creature destr " + name + "en: " + to_string(energy));
//	}
//	std::cout<<"Destr " << name <<"\n";
	cleanupView();
	delete multiview;
	multiview = nullptr;
	delete neuralNet;
	neuralNet = nullptr;
}

void Creature::draw(SDL_Renderer *renderer, Settings *settings) {
	if (!isAlive()) {
		return;
	}
	if (BOOST_UNLIKELY(drawable->texture == nullptr)) {
		drawable->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(drawable->texture, nullptr, nullptr,
				&drawable->rect_draw.w, &drawable->rect_draw.h);
	}
	if (BOOST_LIKELY(settings->draw_textures)) {
		SDL_SetTextureAlphaMod(drawable->texture, energy);
		if (BOOST_UNLIKELY(activeState)) {
			stringColor(renderer, pos.x, pos.y + 20,
					("en:" + std::to_string(energy)).c_str(),
					UNG_Globals::GREEN);
			stringColor(renderer, pos.x, pos.y + 30,
					("gen:" + std::to_string(generations)).c_str(),
					UNG_Globals::GREEN);
			stringColor(renderer, pos.x, pos.y + 40,
					("feed:" + std::to_string(feed_factor)).c_str(),
					UNG_Globals::GREEN);
			stringColor(renderer, pos.x, pos.y + 50,
					("id:" + std::to_string(id) + "(" + std::to_string(parentId)
							+ ";" + std::to_string(ancessorId) + ")").c_str(),
					UNG_Globals::GREEN);
//			stringColor(renderer, pos.x, pos.y + 60,
//								("mview size:" + std::to_string(multiview->size())).c_str(),
//								UNG_Globals::GREEN);
			neuralNet->draw(renderer);
			int tmpOffset = 70;
			for (auto mvect : *multiview) {
				mvect->draw(renderer);
				auto relativeAngle = getAngleDifference(mvect->getAngleDeg(),
						vect->getAngleDeg());
				stringColor(renderer, mvect->pos->x, mvect->pos->y + tmpOffset,
						(std::to_string(mvect->getAngleDeg()) + "("
								+ std::to_string(relativeAngle) + ";"

								+ std::to_string(relativeAngle
												/ neuralNet->params.sightFov)
								+ ")").c_str(), UNG_Globals::GREEN);
				tmpOffset += 10;
//				neuralNet->kickInput(relativeAngle, 0);
			}
			SDL_RenderDrawRect(renderer, &drawable->rect_draw);
		}

		SDL_RenderCopyEx(renderer, drawable->texture, nullptr,
				&drawable->rect_draw, -drawable->rot_angle, nullptr,
				SDL_FLIP_NONE);
	}
//	if (BOOST_LIKELY(settings->draw_vectors)) {
//		drawable->vect.draw(renderer); //draw direction vector
}

void Creature::update(const uint32_t *timeDelta, Settings *settings) {
	if (!isAlive()) {
		return;
	}
	if (BOOST_LIKELY(settings->rotate)) {
		rotate(rotation_speed * *timeDelta * settings->timeScale);
		rotation_speed = 0;
		if (BOOST_LIKELY(settings->move)) {
			move((*timeDelta * settings->timeScale));
		}
		drawable->rect_draw.x = pos.x - (drawable->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable->rect_draw.y = pos.y - (drawable->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
		energy -= metabolism_factor * (neuralNet->params.speed * *timeDelta * settings->timeScale);
		energy -= neural_factor * neuralNet->energyCost;
		feed_factor = feed_factor - 0.00004;
	}
}

void Creature::updateNeuralNet(Settings *settings) {
	neuralNet->process();
	if (isActive()) {
		neuralNet->handleMouseInput(settings);
	}
	mapNeuralNetworkOutput();
}

void Creature::rotate(const float &rotationAngle) {
	drawable->rot_angle += rotationAngle;
	if (BOOST_UNLIKELY(std::abs(drawable->rot_angle) > f360)) {
		drawable->rot_angle = fmod(drawable->rot_angle, f360);
	}
	vect->setAngleDeg(drawable->rot_angle);
}

void Creature::move(const uint32_t &time_delta) {

	pos.x += sin(degToRad(drawable->rot_angle)) * tmpSpeed * time_delta;
	pos.y += cos(degToRad(drawable->rot_angle)) * tmpSpeed * time_delta;
	tmpSpeed = neuralNet->params.speed;
}

void Creature::setActive() {
	if (!activeState) {
		SDL_SetTextureAlphaMod(drawable->texture, 255);
		activeState = true;
	}
}

void Creature::setInactive() {
	if (activeState) {
		SDL_SetTextureAlphaMod(drawable->texture, energy);
		activeState = false;
	}
}

bool Creature::isActive() {
	return activeState;
}

bool Creature::isAlive() {
	return energy > 1;

}

void Creature::cleanupView() {
	neuralNet->clearInput();
	if (multiview->size() > 0) {

		for (auto vect : *multiview) {
			delete vect;
			vect = nullptr;
		}
		multiview->clear();
	}
}
//void Creature::updateView() {
//	neuralNet->updateInput();
//}


bool Creature::lookAt(const Creature *otherCreature) {
	if (multiview->size() < genotype.maxViewEntries) {
		auto vect = lookAt(otherCreature->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			return true;
		}
	}
	return false;
}

bool Creature::lookAt(const Plant *plant) {
	if (multiview->size() < genotype.maxViewEntries) {
		auto vect = lookAt(plant->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			//TODO: should be relative vector for neural network as plant might get out of view FOV in the mean time
			mapViewOnNeuralNetwork(vect);
			return true;
		}
	}
	return false;
}

UNG_Vector* Creature::lookAt(const SDL_FPoint point) {
	float dist = distance(pos, point);
	if (dist != 0 && abs(dist) < neuralNet->params.viewDist) {
		float angle = radToDeg(atan2(point.x - pos.x, point.y - pos.y));
		if (abs(getAngleDifference(vect->getAngleDeg(), angle))
				< neuralNet->params.sightFov) {
			return new UNG_Vector(&pos, angle, dist);
		}
	}
	return nullptr;
}

void Creature::mapViewOnNeuralNetwork(UNG_Vector *vectView) {
	auto relativeAngle = getAngleDifference(vectView->getAngleDeg(), vect->getAngleDeg());
	neuralNet->kickInput(relativeAngle, vectView->value);
//	neuralNet->kickInput(
//			int(
//			//TODO: should be relative vector passed here
//					(getAngleDifference(vectView->getAngleDeg(), vect->getAngleDeg())
//							+ neuralNet->params.sightFov)
//							/ (2 * neuralNet->params.sightFov
//									/ neuralNet->params.inputSize)));
}

void Creature::mapNeuralNetworkOutput() {

	int angle = ((*neuralNet->output).size() / 2) * (-1);
	for (auto neuron : *neuralNet->output) {
		++angle;
		if (neuron->state) {
			rotation_speed -= (angle ^ 3) * neuralNet->params.rotationFactor;
			tmpSpeed -= (abs(angle) ^ 2) * neuralNet->params.speedFactor;
//			tmp = tmp + neuron->id + ":"+ std::to_string(angle) + ";";
		}
	}
	if (neuralNet->foodFound){
		tmpSpeed = tmpSpeed*neuralNet->params.feedDetectspeedFactor;
		neuralNet->foodFound = false;
	}
}

std::string Creature::getInfo() {
	return "energy: " + std::to_string(energy) + ", view: "
			+ std::to_string(multiview->size());
}
