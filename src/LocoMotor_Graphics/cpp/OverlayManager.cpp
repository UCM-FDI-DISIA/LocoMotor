#include "OverlayManager.h"

#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"

#include <cassert>

using namespace LocoMotor;

unsigned int Graphics::OverlayManager::_numOfCanvas = 0;
Graphics::OverlayManager* Graphics::OverlayManager::_instance = nullptr;

Graphics::OverlayManager::OverlayManager() : _canvas(nullptr), _container(nullptr), _ovrsys(nullptr) {}

Graphics::OverlayManager::~OverlayManager() {
	delete _canvas;
	_canvas = nullptr;
	delete _container;
	_container = nullptr;
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

Ogre::OverlayContainer* LocoMotor::Graphics::OverlayManager::getContainer() {
	return _container;
}

Ogre::OverlaySystem* LocoMotor::Graphics::OverlayManager::getSystem() {
	return _ovrsys;
}

bool Graphics::OverlayManager::init() {

	_ovrsys = new Ogre::OverlaySystem();

	Ogre::OverlayManager* _aux = Ogre::OverlayManager::getSingletonPtr();

	if (_aux == nullptr) {
		delete _ovrsys;
		_ovrsys = nullptr;
		return false;
	}

	_canvas = _aux->create("MainOverlay" + _numOfCanvas);
	_container = static_cast<Ogre::OverlayContainer*>(_aux->createOverlayElement("Panel", "Main" + _numOfCanvas));
	_container->setPosition(0.0f, 0.0f);
	_container->setDimensions(1.0f, 1.0f);

	_canvas->add2D(_container);
	//_canvas->show();
	return true;
}
