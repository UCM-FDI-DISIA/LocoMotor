#include "OverlayManager.h"

#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"

#include <cassert>

#include <iostream>

using namespace LocoMotor;

unsigned int Graphics::OverlayManager::_numOfCanvas = 0;
Graphics::OverlayManager* Graphics::OverlayManager::_instance = nullptr;

Graphics::OverlayManager::OverlayManager() : _ovrsys(nullptr) {}

Graphics::OverlayManager::~OverlayManager() {

	delete _ovrsys;
	_ovrsys = nullptr;
}

bool Graphics::OverlayManager::Init() {
	assert(_instance == nullptr);

	_instance = new OverlayManager();

	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	_numOfCanvas++;

	return true;
}

Graphics::OverlayManager* Graphics::OverlayManager::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void Graphics::OverlayManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

bool LocoMotor::Graphics::OverlayManager::IsInitialized() {
	return _instance != nullptr;
}

void LocoMotor::Graphics::OverlayManager::stringToAnchors(const std::string& s, float& x, float& y)
{
	unsigned char currAxis = 0;
	std::string num = "";
	for (const char c : s) {
		if (c != ' ') {
			num += c;
		}
		else {
			float value = 0.f;
			try {
				value = std::stof(num);
			}
			catch (...) {
				value = 0.f;
				std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
			}
			if (currAxis == 0) {
				x = value;
			}
			else if (currAxis == 1) {
				y = value;
			}
			currAxis++;
			num = "";
			if (currAxis == 2) {
				break;
			}
		}
	}
	float value = 0.0f;
	try {
		value = std::stof(num);
	}
	catch (...) {
		value = 0.0f;
		std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
	}
	if (currAxis == 1)
		y = value;
}

void LocoMotor::Graphics::OverlayManager::stringToPosition(const std::string& s, int& x, int& y)
{
	unsigned char currAxis = 0;
	std::string num = "";
	for (const char c : s) {
		if (c != ' ') {
			num += c;
		}
		else {
			int value = 0;
			try {
				value = std::stoi(num);
			}
			catch (...) {
				value = 0;
				std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading an int from UI position/size" << "\033[0m" << std::endl;
			}
			if (currAxis == 0) {
				x = value;
			}
			else if (currAxis == 1) {
				y = value;
			}
			currAxis++;
			num = "";
			if (currAxis == 2) {
				break;
			}
		}
	}
	int value = 0;
	try {
		value = std::stoi(num);
	}
	catch (...) {
		value = 0;
		std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading an int from UI position/size" << "\033[0m" << std::endl;
	}
	if (currAxis == 1)
		y = value;
}

Ogre::OverlayManager* LocoMotor::Graphics::OverlayManager::getOgreOverlayManager() {
	return _ogrOverlayManager;
}

Ogre::OverlaySystem* LocoMotor::Graphics::OverlayManager::getOgreSystem() {
	return _ovrsys;
}

bool Graphics::OverlayManager::init() {

	_ovrsys = new Ogre::OverlaySystem();

	_ogrOverlayManager = Ogre::OverlayManager::getSingletonPtr();

	if (_ogrOverlayManager == nullptr) {
		delete _ovrsys;
		_ovrsys = nullptr;
		return false;
	}

	return true;
}
