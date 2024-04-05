#include "AudioSource.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "Transform.h"

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
	_mode = 0;
	_playOnStart = "";
}

AudioSource::~AudioSource() {
	for (auto& ch : _chMap) {
		ch.second.channel->setFrequency(1.f);
		ch.second.channel->setVolume(1.f);
		ch.second.channel->stop();
	}
}

void AudioSource::addSound(const char* fileName) {
	_man->addSound(fileName);
}

void AudioSource::playSound(const char* fileName, int loops, unsigned int loopBegin, unsigned int loopEnd) {
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

		auto it = _chMap.begin();

		if (it == _chMap.end()) {

			//Si no hay ningun canal de audio en uso ya, seteamos la posicion del transform directamente y velocidad 0
			FMOD_VECTOR newPosition = FMOD_VECTOR();
			auto& lmPos = _gameObject->getComponent<Transform>()->GetPosition();
			newPosition.x = lmPos.GetX();
			newPosition.y = lmPos.GetY();
			newPosition.z = lmPos.GetZ();

			channel->set3DAttributes(&newPosition, &vel);
		}
		else {

			//Si hay algun canal, le ponemos los mismos atributos que el primer canal de audio, para que se comporten igual éste frame
			FMOD_VECTOR lastPosition = FMOD_VECTOR();
			FMOD_VECTOR lastVel = FMOD_VECTOR();
			it->second.channel->get3DAttributes(&lastPosition, &lastVel);

			channel->set3DAttributes(&lastPosition, &lastVel);
		}
	}
	_chMap[fileName].channel = channel;
	float aux;
	_chMap[fileName].channel->getFrequency(&aux);
	_chMap[fileName].ogFrec = aux;
	_chMap[fileName].channel->setVolume(_volumeMult);

	channel->setPaused(false);
}

void AudioSource::playOneShot(const char* fileName, const LMVector3& position, const float volume) {
	float randPtch = 0.95f + (float) (rand()) / ((float) (RAND_MAX / (1.05f - 0.95f)));
	return playOneShot(fileName, position, volume, randPtch);
}

void AudioSource::playOneShot(const char* fileName, const LMVector3& position, const float volume, const float pitch) {
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

	FMOD_VECTOR newPosition = FMOD_VECTOR();
	newPosition.x = position.GetX();
	newPosition.y = position.GetY();
	newPosition.z = position.GetZ();
	FMOD_VECTOR vel = FMOD_VECTOR(); vel.x = 0; vel.y = 0; vel.z = 0;
	if (fail != FMOD_OK)
		channel->set3DAttributes(&newPosition, &vel);
	else
		fail = channel->set3DAttributes(&newPosition, &vel);
	float aux;
	channel->getFrequency(&aux);
	channel->setFrequency(aux * pitch);
	channel->setVolume(volume);

	channel->setPaused(false);
}

void AudioSource::pauseSound(const char* fileName, bool pause) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound " << fileName << " is not currently playing on this AudioSource, from PauseSound()";
	#endif // _DEBUG
		return;
	}
	_chMap[fileName].channel->setPaused(pause);
}

void AudioSource::pause(bool pause) {
	for (auto& chan : _chMap) {
		chan.second.channel->setPaused(pause);
	}
}

void AudioSource::stopSound(const char* fileName) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound '" << fileName << "' is not currently playing on this AudioSource, from Stop()";
	#endif // _DEBUG
		return;
	}
	_chMap[fileName].channel->setFrequency(_chMap[fileName].ogFrec);
	_chMap[fileName].channel->setVolume(1.f);
	_chMap[fileName].channel->stop();
}

void AudioSource::stop() {
	for (auto& chan : _chMap) {
		chan.second.channel->setFrequency(chan.second.ogFrec);
		chan.second.channel->setVolume(1.f);
		chan.second.channel->stop();
	}
}

void AudioSource::setSoundVolume(const char* fileName, const float volume) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound '" << fileName << "' is not currently playing on this AudioSource, from SetVolume()";
	#endif // _DEBUG
	}
	_chMap[fileName].channel->setVolume(volume);
}

void AudioSource::setVolume(const float volume) {
	for (auto& chan : _chMap) {
		chan.second.channel->setVolume(volume);
	}
	_volumeMult = volume;
}

void AudioSource::setSoundFreq(const char* fileName, const float freqMult) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cerr << "Sound " << fileName << " is not currently playing on this AudioSource, from SetSoundFreq()";
	#endif // _DEBUG
	}
	_chMap[fileName].channel->setFrequency(std::max(0.f, _chMap[fileName].ogFrec * freqMult));
}

void AudioSource::setFrequency(const float freqMult) {
	for (auto& chan : _chMap) {
		chan.second.channel->setFrequency(std::max(0.f, chan.second.ogFrec * freqMult));
	}
}

void AudioSource::setMode3D() {
	_mode = FMOD_3D | FMOD_3D_WORLDRELATIVE;
}

void AudioSource::setMode2D() {
	_mode = FMOD_2D;
}

void LocoMotor::AudioSource::setParameters(ComponentMap& params) {
	_man = Audio::AudioManager::GetInstance();
	_chMap = std::unordered_map<const char*, ChannelData>();
	_volumeMult = 1.f;
	_mode = FMOD_3D | FMOD_3D_WORLDRELATIVE;
	for (auto& parameter : params) {
		if (parameter.first == "PlayOnAwake") {
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

	auto it = _chMap.begin();

	if (it == _chMap.end()) {
		return;
	}

	FMOD_VECTOR newPosition = FMOD_VECTOR();
	auto& lmPos = _gameObject->getComponent<Transform>()->GetPosition();
	newPosition.x = lmPos.GetX();
	newPosition.y = lmPos.GetY();
	newPosition.z = lmPos.GetZ();

	FMOD_VECTOR lastPosition = FMOD_VECTOR();
	it->second.channel->get3DAttributes(&lastPosition, NULL);

	FMOD_VECTOR newVel = FMOD_VECTOR();
	newVel.x = (newPosition.x - lastPosition.x) / dT;
	newVel.y = (newPosition.y - lastPosition.y) / dT;
	newVel.z = (newPosition.z - lastPosition.z) / dT;

	while (it != _chMap.end()) {
		bool is;
		it->second.channel->isPlaying(&is);
		if (is) {
			it->second.channel->set3DAttributes(&newPosition, &newVel);
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
}
