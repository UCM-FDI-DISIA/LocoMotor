#include "AudioManager.h"
#include "AudioListener.h"
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_errors.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cassert>

using namespace LocoMotor;
using namespace LocoMotor::Audio;

AudioManager* AudioManager::_instance = nullptr;

bool AudioManager::Init(bool useStudio)
{
	return Init(16, useStudio);
}

bool AudioManager::Init(int numChannels, bool useStudio)
{
	assert(_instance == nullptr);
	_instance = new AudioManager();

	if (!_instance->init(numChannels, useStudio)) {
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

unsigned short AudioManager::update()
{
	return _studioSys? _studioSys->update() : _sys->update();
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

void LocoMotor::Audio::AudioManager::loadFMODBuild(const char* fmodPath) {

	if (_studioSys == nullptr) {
	#ifdef _DEBUG
		std::cerr << "Studio not initialized, pass a 'true' to the Init to initialize with Studio" << std::endl;
	#endif
		return;
	}

	FMOD::Studio::Bank* bank;
	std::string masterStringPath = fmodPath;
	masterStringPath += "/Master.strings.bank";

	//Si ya está cargado...
	if (_studioSys->getBank(masterStringPath.c_str(), &bank) == FMOD_OK)
		return;

	FMOD_RESULT res = _studioSys->loadBankFile(masterStringPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

	if (res != FMOD_OK) {
	#ifdef _DEBUG
		std::cerr << "Couldn´t find '" << masterStringPath << "'" << std::endl;
	#endif
		return;
	}

	int numOfStrings;

	bank->getStringCount(&numOfStrings);
	char path[100];

#ifdef _DEBUG
	std::cout << "Loading all banks included in Master.strings.bank" << std::endl;
#endif

	for (int i = 0; i < numOfStrings; i++) {
		FMOD_GUID info;
		int ret;
		bank->getStringInfo(i, &info, path, 100, &ret);

		std::string retrieved = path;
		retrieved.shrink_to_fit();

		if (retrieved.rfind("bank:", 0) == 0) {
			FMOD::Studio::Bank* toLoad;
		#ifdef _DEBUG
			std::cout << "Loading bank at: " << retrieved.substr(5).append(".bank").insert(0, fmodPath) << std::endl;
		#endif
			_studioSys->loadBankFile(retrieved.substr(5).append(".bank").insert(0, fmodPath).c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &toLoad);
		}
	}
}

FMOD::System* AudioManager::getSystem() const
{
	return _sys;
}

FMOD::Studio::System* LocoMotor::Audio::AudioManager::getStudioSystem() const {
	return _studioSys;
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

bool AudioManager::init(int numChannels, bool useStudio)
{
	if (useStudio) {
		if (!(FMOD::Studio::System::create(&_studioSys) == FMOD_OK)) {
			return false;
		}

		if (!(_studioSys->initialize(numChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0) == FMOD_OK)) {
			_studioSys->release();
			return false;
		}

		_studioSys->getCoreSystem(&_sys);
	}
	else {
		if (!(System_Create(&_sys) == FMOD_OK)) {
			return false;
		}

		if (!(_sys->init(numChannels, FMOD_INIT_NORMAL, 0) == FMOD_OK)) {
			_sys->release();
			return false;
		}
	}

	if (!(_sys->createChannelGroup(0, &_main) == FMOD_OK)) {
		_sys->close();
		_sys->release();
		return false;
	}

	_sys->set3DSettings(1.f, 1.f, 1.f);

	return true;
}
