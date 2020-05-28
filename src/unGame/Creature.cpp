#include <UNGCreature.h>

Creature::Creature(SDL_Surface *surfaceptr) {
	multiview = new std::vector<UNG_Vector*>();
	multiview->reserve(MAX_VIEW_ENTRIES);
	surface = surfaceptr;
}

Creature::~Creature() {
	cleanupView();
	delete multiview;
	multiview = nullptr;
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
					("rot:" + std::to_string(rotation_speed)).c_str(),
					UNG_Globals::GREEN);
			stringColor(renderer, pos.x, pos.y + 30, ("out:" + tmp).c_str(),
					UNG_Globals::GREEN);
			neuralNet.draw(renderer);
			for (auto vect : *multiview) {
				vect->draw(renderer);
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
		rotate(rotation_speed * *timeDelta);
		if (BOOST_LIKELY(settings->move)) {
			move(timeDelta);
		}
		drawable->rect_draw.x = pos.x - (drawable->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable->rect_draw.y = pos.y - (drawable->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
	}
}

void Creature::updateNeuralNet(Settings *settings) {
	neuralNet.process();
	if (isActive()) {
		neuralNet.handleInput(settings);
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

void Creature::move(const uint32_t *time_delta) {
	pos.x += sin(degToRad(drawable->rot_angle)) * speed * *time_delta;
	pos.y += cos(degToRad(drawable->rot_angle)) * speed * *time_delta;
	energy -= metabolism_factor * (speed * *time_delta);
}

void Creature::setSpeed(float &speed) {
	this->speed = speed;
}

void Creature::setRotationSpeed(float &speed) {
	this->rotation_speed = speed;
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
	return energy > 0;

}

void Creature::cleanupView() {
	neuralNet.clearInput();
	if (multiview->size() > 0) {

		for (auto vect : *multiview) {
			delete vect;
			vect = nullptr;
		}
		multiview->clear();
	}
}

bool Creature::lookAt(const Creature *otherCreature) {
	if (multiview->size() < MAX_VIEW_ENTRIES) {
		auto vect = lookAt(otherCreature->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			return true;
		}
	}
	return false;
}

bool Creature::lookAt(const Plant *plant) {
	if (multiview->size() < MAX_VIEW_ENTRIES) {
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
	if (dist != 0 && abs(dist) < VIEW_DIST) {
		float angle = radToDeg(atan2(point.x - pos.x, point.y - pos.y));
		if (abs(getDifference(vect->getAngleDeg(), angle)) < FOV) {
			return new UNG_Vector(&pos, angle, dist);
		}
	}
	return nullptr;
}

void Creature::mapViewOnNeuralNetwork(UNG_Vector *vectView) {
	neuralNet.kickInput(
			int(
			//TODO: should be relative vector passed here
					(getDifference(vectView->getAngleDeg(), vect->getAngleDeg())
							+ FOV) / (2 * FOV / neuralNet.inputSize)));
}

void Creature::mapNeuralNetworkOutput() {
	rotation_speed = 0;
	tmp = "";
	float speedFactor = 0.05;
	int angle = ((*neuralNet.output).size() / 2) * (-1);
	for (auto neuron : *neuralNet.output) {
		++angle;
		if (neuron->state) {
			rotation_speed -= angle  * speedFactor;
			tmp = tmp + neuron->id + ":"+ std::to_string(angle) + ";";
		}
	}
}

std::string Creature::getInfo() {
	return "energy: " + std::to_string(energy) + ", view: "
			+ std::to_string(multiview->size());
}
