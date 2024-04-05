#include "EventEmitter.h"
#include "AudioManager.h"
#include "Transform.h"
#include "LMVector.h"
#include "GameObject.h"

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor;

EventEmitter::EventEmitter() : _currentEvent(nullptr), _studioSys(nullptr), playOnStart(false) {}

EventEmitter::~EventEmitter() {
	if (_currentEvent != nullptr)
		_currentEvent->release();
}

void LocoMotor::EventEmitter::setEvent(const char* eventID) 
{

	if (_studioSys == nullptr) {
		return;
	}

	FMOD::Studio::EventDescription* desc;

#ifndef _DEBUG

	_studioSys->getEvent(eventID, &desc);

#else

	FMOD_RESULT err;
	err = _studioSys->getEvent(eventID, &desc);

	if (err != FMOD_OK) {
		std::cerr << "AUDIO: Event with ID '" << eventID << "' could not be loaded: \n\t" << FMOD_ErrorString(err) << std::endl;
	}

#endif // !_DEBUG

	desc->createInstance(&_currentEvent);
}

void EventEmitter::play() {
	_currentEvent->start();
}

void EventEmitter::setVolume(float vol) {
	_currentEvent->setVolume(vol);
}

void EventEmitter::setPitch(float pitch) {
	_currentEvent->setPitch(pitch);
}

void EventEmitter::setParameter(const char* paramName, float value) {
	_currentEvent->setParameterByName(paramName, value);
}

float EventEmitter::getParameter(const char* paramName) {
	float val;
	_currentEvent->getParameterByName(paramName, &val);
	return val;
}

void EventEmitter::stop() {
	_currentEvent->stop(FMOD_STUDIO_STOP_IMMEDIATE);
}

void LocoMotor::EventEmitter::setParameters(ComponentMap& params) {
	_studioSys = Audio::AudioManager::GetInstance()->getStudioSystem();
	if (_studioSys == nullptr) {
	#ifdef _DEBUG
		std::cerr << "Attempted to create an EventEmitter component without studio initialized, removing component" << std::endl;
	#endif
		return;
	}

	for (auto& parameter : params) {
		if (parameter.first == "EventID") {
			setEvent(parameter.second.c_str());
		}
		else if (parameter.first == "Volume") {
			try {
				if (_currentEvent)
					_currentEvent->setVolume(std::stof(parameter.second));
			}
			catch (...) {

			}
		}
		else if (parameter.first == "Start" || parameter.first == "Play") {
			playOnStart = true;
		}
	}
}

void LocoMotor::EventEmitter::start() {
	if (_studioSys == nullptr) {
		_gameObject->removeComponents("EventEmitter");
		return;
	}
	if (playOnStart)
		play();
}

void LocoMotor::EventEmitter::update(float dT) {
	if (_currentEvent == nullptr)
		return;
	FMOD_3D_ATTRIBUTES at;
	_currentEvent->get3DAttributes(&at);

	LMVector3 newPos = _gameObject->getComponent<Transform>()->GetPosition();

	at.velocity.x = (newPos.GetX() - at.position.x) / dT;
	at.velocity.y = (newPos.GetY() - at.position.y) / dT;
	at.velocity.z = (newPos.GetZ() - at.position.z) / dT;

	at.position.x = newPos.GetX();
	at.position.y = newPos.GetY();
	at.position.z = newPos.GetZ();

	LMVector3 forward = _gameObject->getComponent<Transform>()->GetRotation().Forward();

	at.forward.x = forward.GetX();
	at.forward.y = forward.GetY();
	at.forward.z = forward.GetZ();

	LMVector3 up = _gameObject->getComponent<Transform>()->GetRotation().Up();

	at.up.x = up.GetX();
	at.up.y = up.GetY();
	at.up.z = up.GetZ();

	_currentEvent->set3DAttributes(&at);
}

