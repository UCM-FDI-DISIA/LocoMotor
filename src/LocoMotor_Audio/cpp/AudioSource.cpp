#include "AudioSource.h"
#include "AudioManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <random>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor;
using namespace FMOD;

AudioSource::AudioSource() : _man(nullptr) {
	_chMap = std::unordered_map<const char*, ChannelData>();
	_volumeMult = 1.f;
	_posRemember = nullptr;
	_mode = 0;
	_playOnStart = "";
}

AudioSource::~AudioSource() {
	delete _posRemember;
	for (auto& ch : _chMap) {
		ch.second.channel->setFrequency(1.f);
		ch.second.channel->setVolume(1.f);
		ch.second.channel->stop();
	}
}

unsigned short AudioSource::addSound(const char* fileName) {
	return _man->addSound(fileName);
}

unsigned short AudioSource::playSound(const char* fileName, int loops, unsigned int loopBegin, unsigned int loopEnd) {
	FMOD::Sound* snd = _man->getSound(fileName);
	if (snd == nullptr) {
	#ifdef _DEBUG
		std::cerr << "Sound '" << fileName << "' is not added to the manager, adding it now\n";
	#endif // _DEBUG
		addSound(fileName);
		snd = _man->getSound(fileName);
	}

	unsigned int len;
	snd->getLength(&len, FMOD_TIMEUNIT_MS);

	if (loopBegin >= len)
		loops = 0;
	else if (loopEnd > len)
		loopEnd = len;

	if (!loops)
		snd->setMode(_mode);
	else {
		snd->setMode(_mode | FMOD_LOOP_NORMAL);
		FMOD_RESULT err = snd->setLoopPoints(std::min(loopBegin, loopEnd), FMOD_TIMEUNIT_MS, std::max(loopBegin, loopEnd), FMOD_TIMEUNIT_MS);
	#ifdef _DEBUG
		if (err != FMOD_OK) {
			std::cerr << "Source error: Trying to play a loop: " << _man->getError(err) << std::endl;
		}
	#endif
		snd->setLoopCount(std::max(-1, loops));
	}
	Channel* channel;
	unsigned short fail = _man->playSoundwChannel(fileName, &channel);

	FMOD_VECTOR vel = FMOD_VECTOR(); vel.x = 0; vel.y = 0; vel.z = 0;
	if (_mode != FMOD_2D) {
		if (fail != FMOD_OK)
			channel->set3DAttributes(_posRemember, &vel);
		else
			fail = channel->set3DAttributes(_posRemember, &vel);
	}
	_chMap[fileName].channel = channel;
	float aux;
	_chMap[fileName].channel->getFrequency(&aux);
	_chMap[fileName].ogFrec = aux;
	_chMap[fileName].channel->setVolume(_volumeMult);

	channel->setPaused(false);
	return fail;
}

unsigned short AudioSource::playOneShot(const char* fileName, const FMOD_VECTOR& position, const float volume) {
	float randPtch = 0.8f + (float) (rand()) / ((float) (RAND_MAX / (1.1f - 0.8f)));
	return playOneShot(fileName, position, volume, randPtch);
}

unsigned short AudioSource::playOneShot(const char* fileName, const FMOD_VECTOR& position, const float volume, const float pitch) {
	FMOD::Sound* snd = _man->getSound(fileName);
	if (snd == nullptr) {
	#ifdef _DEBUG
		std::cerr << "Sound " << fileName << " is not added to the manager, adding it now";
	#endif // _DEBUG
		addSound(fileName);
		snd = _man->getSound(fileName);
	}
	snd->setMode(_mode);

	Channel* channel;
	unsigned short fail = _man->playSoundwChannel(fileName, &channel);

	FMOD_VECTOR vel = FMOD_VECTOR(); vel.x = 0; vel.y = 0; vel.z = 0;
	if (fail != FMOD_OK)
		channel->set3DAttributes(&position, &vel);
	else
		fail = channel->set3DAttributes(&position, &vel);
	float aux;
	channel->getFrequency(&aux);
	channel->setFrequency(aux * pitch);
	channel->setVolume(volume);

	channel->setPaused(false);
	return fail;
}

unsigned short AudioSource::pauseSound(const char* fileName, bool pause) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound " << fileName << " is not currently playing on this AudioSource, from PauseSound()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setPaused(pause);
}

unsigned short AudioSource::pause(bool pause) {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		FMOD_RESULT aux = chan.second.channel->setPaused(pause);
		if (aux > res) {
			res = aux;
		}
	}
	return res;
}

unsigned short AudioSource::stopSound(const char* fileName) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound '" << fileName << "' is not currently playing on this AudioSource, from Stop()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	_chMap[fileName].channel->setFrequency(_chMap[fileName].ogFrec);
	_chMap[fileName].channel->setVolume(1.f);
	return _chMap[fileName].channel->stop();
}

unsigned short AudioSource::stop() {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		chan.second.channel->setFrequency(chan.second.ogFrec);
		chan.second.channel->setVolume(1.f);
		FMOD_RESULT aux = chan.second.channel->stop();
		if (aux > res) {
			res = aux;
		}
	}
	return res;
}

unsigned short AudioSource::setSoundVolume(const char* fileName, const float volume) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound '" << fileName << "' is not currently playing on this AudioSource, from SetVolume()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setVolume(volume);
}

unsigned short AudioSource::setVolume(const float volume) {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		FMOD_RESULT aux = chan.second.channel->setVolume(volume);
		if (aux > res) {
			res = aux;
		}
	}
	_volumeMult = volume;
	return res;
}

unsigned short AudioSource::setSoundFreq(const char* fileName, const float freqMult) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound " << fileName << " is not currently playing on this AudioSource, from SetSoundFreq()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setFrequency(std::max(0.f, _chMap[fileName].ogFrec * freqMult));
}

unsigned short AudioSource::setFrequency(const float freqMult) {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		FMOD_RESULT aux = chan.second.channel->setFrequency(std::max(0.f, chan.second.ogFrec * freqMult));
		if (aux > res) {
			res = aux;
		}
	}
	return res;
}

void AudioSource::setPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel) {

	auto it = _chMap.begin();

	while (it != _chMap.end()) {
		bool is;
		it->second.channel->isPlaying(&is);
		if (is) {
			if (_mode == FMOD_2D) {
				it++;
				continue;
			}
			it->second.channel->set3DAttributes(&newPos, &newVel);
			it++;
		}
		else {
			it->second.channel->setFrequency(it->second.ogFrec);
			it->second.channel->setVolume(1.f);
			it->second.channel->stop();
			it->second.channel = nullptr;
			it = _chMap.erase(it);
		}
	}

	_posRemember->x = newPos.x;
	_posRemember->y = newPos.y;
	_posRemember->z = newPos.z;
}

void AudioSource::setPositionAndVelocity(const FMOD_VECTOR& newPos, float delta) {
	FMOD_VECTOR vel = FMOD_VECTOR();
	vel.x = (newPos.x - _posRemember->x) / delta;
	vel.y = (newPos.y - _posRemember->y) / delta;
	vel.z = (newPos.z - _posRemember->z) / delta;

	setPositionAndVelocity(newPos, vel);
}

void AudioSource::setMode3D() {
	_mode = FMOD_3D | FMOD_3D_WORLDRELATIVE;
}

void AudioSource::setMode2D() {
	_mode = FMOD_2D;
}

void LocoMotor::AudioSource::setParameters(std::vector<std::pair<std::string, std::string>>& params) {
	_man = Audio::AudioManager::GetInstance();
	_chMap = std::unordered_map<const char*, ChannelData>();
	_volumeMult = 1.f;
	_posRemember = new FMOD_VECTOR();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
	_mode = FMOD_3D | FMOD_3D_WORLDRELATIVE;
	for (auto& parameter : params) {
		if (parameter.first == "PlayOnAwake") {
			std::cout << parameter.second.c_str() << std::endl;
			_playOnStart = parameter.second;
		}
		else if (parameter.first == "Volume") {
			try {
				_volumeMult = std::stof(parameter.second);
			}
			catch (...) {

			}
		}
	}
}

void LocoMotor::AudioSource::start() {
	if (_playOnStart != "") {
		addSound(_playOnStart.c_str());
		playSound(_playOnStart.c_str());
	}
}

void LocoMotor::AudioSource::update(float dT) {
	FMOD_VECTOR newPosition = FMOD_VECTOR();
	// Inicializar con la posicion del transform...

	setPositionAndVelocity(newPosition, dT);
}
