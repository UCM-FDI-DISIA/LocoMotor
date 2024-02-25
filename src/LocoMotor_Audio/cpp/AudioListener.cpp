#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor::Audio;

AudioListener::AudioListener() : _man(AudioManager::GetInstance()) {
	_thisIT = _man->addListener(this, _fIndex);
}

AudioListener::~AudioListener() {
	_man->removeListener(_thisIT, _fIndex);
}

unsigned short AudioListener::setTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up) {

#ifdef _DEBUG
	unsigned short err = _man->getSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cerr << "Listener error: " << _man->getError(err) << std::endl;
	}
	return err;
#else
	return _man->GetSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
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
