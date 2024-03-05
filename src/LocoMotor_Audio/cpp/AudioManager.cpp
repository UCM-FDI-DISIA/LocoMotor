#include "AudioManager.h"
#include "AudioListener.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cassert>

using namespace LocoMotor;
using namespace LocoMotor::Audio;

AudioManager* AudioManager::_instance = nullptr;

bool AudioManager::Init()
{
	return Init(16);
}

bool AudioManager::Init(int numChannels)
{
	assert(_instance == nullptr);
	_instance = new AudioManager();

	if (!_instance->init(numChannels)) {
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

AudioManager* AudioManager::GetInstance()
{
	assert(_instance != nullptr);
	return _instance;
}

void AudioManager::Release()
{
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

unsigned short AudioManager::update(float deltaTime)
{
	return _sys->update();
}

unsigned short AudioManager::addSound(const char* fileName, bool ui)
{
	if (_soundLib[fileName] != nullptr) {
		if (ui)
			_soundLib[fileName]->setMode(FMOD_DEFAULT);
		else
			_soundLib[fileName]->setMode(FMOD_3D_WORLDRELATIVE);
		return 0;
	}

#ifndef _DEBUG
	if (ui)
		return _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		return _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err;
	if (ui)
		err = _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		err = _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);

	if (err != 0) {
		std::cerr << "AUDIO: File '" << fileName << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

unsigned short AudioManager::playSound(const char* id)
{
	FMOD::Channel* ch;
	unsigned short err = playSoundwChannel(id, &ch);
	ch->setPaused(false);
	return err;
}

unsigned short AudioManager::playSoundwChannel(const char* id, FMOD::Channel** channel)
{
#ifndef _DEBUG
	unsigned short err = _sys->playSound(_soundLib[id], _main, true, channel);

	return err;
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err = _sys->playSound(_soundLib[id], _main, true, channel);

	if (err != 0) {
		std::cerr << "AUDIO: Trying to play sound '" << id << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

std::list<AudioListener*>::iterator AudioManager::addListener(AudioListener* curr, size_t& index)
{
	index = _listeners.size();
	_listeners.push_back(curr);

	_sys->set3DNumListeners((int)_listeners.size());

	std::list<AudioListener*>::iterator it = _listeners.end();
	it--;
	return it;
}

unsigned short AudioManager::removeListener(std::list<AudioListener*>::iterator it, size_t indexToRemove)
{
	auto listenerIt = _listeners.erase(it);
	int nIndex = (int)indexToRemove;

	unsigned short err = 0;

	while (listenerIt != _listeners.end()) {
		err = (*listenerIt)->changeIndex(nIndex);

#ifdef _DEBUG
		if (err != 0) {
			std::cerr << "AUDIO: Trying to update listeners while removing number '" << indexToRemove << "' caused fmod exception: " << FMOD_ErrorString((FMOD_RESULT)err) << std::endl;
		}
#endif // _DEBUG
		listenerIt++;
		nIndex++;
	}
	_sys->set3DNumListeners((int)_listeners.size());
	return err;
}

FMOD::System* AudioManager::getSystem() const
{
	return _sys;
}

FMOD::Sound* AudioManager::getSound(const char* id)
{
	return _soundLib[id] ? _soundLib[id] : nullptr;
}

const char* AudioManager::getError(const unsigned short& errorCode)
{
	return FMOD_ErrorString((FMOD_RESULT)errorCode);
}

AudioManager::AudioManager()
{
	_sys = nullptr;
	_main = nullptr;
	_soundLib = std::unordered_map<std::string, FMOD::Sound*>();
	_listeners = std::list<AudioListener*>();
}

AudioManager::~AudioManager()
{
	for (auto& snd : _soundLib) {
		snd.second->release();
	}
	_main->release();

	_sys->close();
	_sys->release();
}

bool AudioManager::init(int numChannels)
{
	if (!(System_Create(&_sys) == FMOD_OK)) {
		return false;
	}

	if (!(_sys->init(numChannels, FMOD_INIT_NORMAL, 0) == FMOD_OK)) {
		_sys->release();
		return false;
	}

	if (!(_sys->createChannelGroup(0, &_main) == FMOD_OK)) {
		_sys->close();
		_sys->release();
		return false;
	}

	_sys->set3DSettings(1.f, 1.f, 1.f);

	return true;
}
