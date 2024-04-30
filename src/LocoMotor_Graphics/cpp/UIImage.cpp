#include "UIImage.h"
#include "GameObject.h"
#include "LMVector.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"
#include <iostream>

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"

using namespace LocoMotor;

LocoMotor::UIImage::UIImage() : _gfxManager(nullptr), _container(nullptr), _overlayMngr(nullptr) {
}

LocoMotor::UIImage::~UIImage() {
	_overlayMngr->destroyOverlayElement(_container);
	_container = nullptr;
	Ogre::OverlayManager::getSingletonPtr()->destroy(_overlay->getName());
	_overlay = nullptr;
}

void LocoMotor::UIImage::setImage(const std::string& nImage) {
	if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(nImage))
		_container->setMaterialName(nImage);
	else {
		_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());
	#ifdef _DEBUG
		std::cerr << "\033[1;31m" << "Material '" << nImage << "' wasn't found in any known .material script. UIImage at gameObject: " << _gameObject->getName() << "\033[0m" << std::endl;
	#endif
	}
}

void LocoMotor::UIImage::setParameters(ComponentMap& params) {


	_gfxManager = Graphics::GraphicsManager::GetInstance();
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();

	_overlay = _overlayMngr->create("overlay_" + _gameObject->getName() + "_img");

	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImage" + _gameObject->getName()));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);

	std::string imageName = "";
	int sortingLayer = 0;
	float rotation = 0.f;

	for (auto& param : params) {
		if (param.first == "Anchor" || param.first == "anchor") {
			Graphics::OverlayManager::stringToAnchors(param.second, _anchorX, _anchorY);
		}
		else if (param.first == "Pivot" || param.first == "pivot") {
			Graphics::OverlayManager::stringToAnchors(param.second, _pivotX, _pivotY);
		}
		else if (param.first == "Position" || param.first == "position") {
			Graphics::OverlayManager::stringToPosition(param.second, _positionX, _positionY);
		}
		else if (param.first == "Size" || param.first == "size") {
			Graphics::OverlayManager::stringToPosition(param.second, _sizeX, _sizeY);
		}
		else if (param.first == "SortingLayer" || param.first == "sortingLayer") {
			try {
				sortingLayer = std::stoi(param.second);
			}
			catch (...) {
				sortingLayer = 0;
			}
		}
		else if (param.first == "Rotation" || param.first == "rotation") {
			try {
				rotation = std::stof(param.second);
			}
			catch (...) {
				rotation = 0.f;
			}
		}
		else if (param.first == "Image" || param.first == "image") {
			imageName = param.second;
		}
	}

	_container->setDimensions(Ogre::Real(_sizeX), Ogre::Real(_sizeY));

	updatePosition();

	setImage(imageName);

	setSortingLayer(sortingLayer);
	setRotation(rotation);

	_overlay->add2D(_container);

	_overlay->show();
}

void LocoMotor::UIImage::update(float dT) {
	updatePosition();
}

void LocoMotor::UIImage::setAnchorPoint(float x, float y) {
	_anchorX = x;
	_anchorY = y;
	updatePosition();
}

void LocoMotor::UIImage::setPosition(int x, int y) {
	_positionX = x;
	_positionY = y;
	updatePosition();
}

void LocoMotor::UIImage::setDimensions(int w, int h) {
	_sizeX = w;
	_sizeY = h;
	_container->setDimensions(Ogre::Real(_sizeX), Ogre::Real(_sizeY));
}

void LocoMotor::UIImage::setPivot(float w, float h) {
	_pivotX = w;
	_pivotY = h;
	updatePosition();
}

void LocoMotor::UIImage::setSortingLayer(int layer) {
	if (layer < 0) layer = 0;
	else if (layer > 650) layer = 650;
	_overlay->setZOrder(Ogre::ushort(layer));
}

void LocoMotor::UIImage::setRotation(float radians) {
	_overlay->setRotate(Ogre::Radian(radians));
}

void LocoMotor::UIImage::show() {
	_container->show();
}

void LocoMotor::UIImage::hide() {
	_container->hide();
}

void LocoMotor::UIImage::initializeABorrar() {
	std::vector<std::pair<std::string, std::string>> a;
	setParameters(a);
}

int LocoMotor::UIImage::getWidth() {
	return _sizeX;
}

int LocoMotor::UIImage::getHeight() {
	return _sizeY;
}

void LocoMotor::UIImage::updatePosition() {
	_container->setMetricsMode(Ogre::GMM_PIXELS);
	int wWidth = _gfxManager->getWindowWidth();
	int wHeight = _gfxManager->getWindowHeight();
	_container->setPosition(wWidth * _anchorX + _positionX - (_sizeX * _pivotX), wHeight * _anchorY + _positionY - (_sizeY * _pivotY));
}
