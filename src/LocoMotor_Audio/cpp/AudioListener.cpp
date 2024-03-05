#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor;

void LocoMotor::AudioListener::setParameters(std::vector<std::pair<std::string, std::string>>& params) {
	_man = Audio::AudioManager::GetInstance();
	_fSys = _man->getSystem();
}

void AudioListener::onEnable() {
	_thisIT = _man->addListener(this, _fIndex);
}

void LocoMotor::AudioListener::start() {}

void AudioListener::update(float dT) {
	FMOD_VECTOR lastPosition;
	_fSys->get3DListenerAttributes(_fIndex, &lastPosition, NULL, NULL, NULL);

	//Pasar de datos del transform a los atributos necesarios

	//_fSys->set3DListenerAttributes(_fIndex, transformPosition, velcidadCalculada, transformForward, transformUp);

}

void AudioListener::onDisable() {
	_man->removeListener(_thisIT, _fIndex);
}

AudioListener::AudioListener() : _fIndex(0), _man(nullptr), _fSys(nullptr), _thisIT() {
}

AudioListener::~AudioListener() {
}

unsigned short AudioListener::setTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up) {

#ifdef _DEBUG
	unsigned short err = _man->getSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cerr << "Listener error: " << _man->getError(err) << std::endl;
	}
	return err;
#else
	return _man->getSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
#endif // _DEBUG
}

unsigned short AudioListener::changeIndex(int index) {
	FMOD_VECTOR newPos; FMOD_VECTOR newVel; FMOD_VECTOR forward; FMOD_VECTOR up;

	unsigned short err = _man->getSystem()->get3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);

	if (err == 0)
		err = _man->getSystem()->set3DListenerAttributes(index, &newPos, &newVel, &forward, &up);

	_fIndex = (size_t)index;

	return err;
}
