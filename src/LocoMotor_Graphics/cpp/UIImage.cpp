#include "UIImage.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"

#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"

using namespace LocoMotor;

unsigned int UIImage::_numOfImages = 0;

LocoMotor::UIImage::UIImage() : _gfxManager(nullptr), _container(nullptr), _overlayMngr(nullptr) {
	_numOfImages++;
}

LocoMotor::UIImage::~UIImage() {
	_overlayMngr->destroyOverlayElement(_container);
}

void LocoMotor::UIImage::setImage(std::string nImage) {
	if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(nImage))
		_container->setMaterialName(nImage);
}

void LocoMotor::UIImage::setParameters(std::vector<std::pair<std::string, std::string>>& params) {

	_gfxManager = Graphics::GraphicsManager::GetInstance();

	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImage" + std::to_string(_numOfImages)));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);
	_container->setPosition(_gfxManager->getWindowWidth() * _anchorX + _positionX, _gfxManager->getWindowHeight() * _anchorY + _positionY);

	_container->setDimensions(_sizeX, _sizeY);

	_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());

	Graphics::OverlayManager::GetInstance()->getContainer()->addChild(_container);
}

void LocoMotor::UIImage::update(float dT) {
	updatePosition();
}

void LocoMotor::UIImage::setAnchorPoint(float x, float y) {
	_anchorX = x;
	_anchorY = y;
	updatePosition();
}

void LocoMotor::UIImage::setPosition(float x, float y) {
	_positionX = x;
	_positionY = y;
	updatePosition();
}

void LocoMotor::UIImage::setDimensions(float w, float h) {
	_sizeX = w;
	_sizeY = h;
	_container->setDimensions(_sizeX, _sizeY);
}

void LocoMotor::UIImage::show() {
	_container->show();
}

void LocoMotor::UIImage::hide() {
	_container->hide();
}

void LocoMotor::UIImage::initializeABorrar() {

	_gfxManager = Graphics::GraphicsManager::GetInstance();
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();

	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImage" + std::to_string(_numOfImages)));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);
	_container->setPosition(_gfxManager->getWindowWidth() * _anchorX + _positionX, _gfxManager->getWindowHeight() * _anchorY + _positionY);

	_container->setDimensions(_sizeX, _sizeY);

	_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());

	Graphics::OverlayManager::GetInstance()->getContainer()->addChild(_container);
}

void LocoMotor::UIImage::updatePosition() {
	_container->setMetricsMode(Ogre::GMM_PIXELS);
	int wWidth = _gfxManager->getWindowWidth();
	int wHeight = _gfxManager->getWindowHeight();
	_container->setPosition(wWidth * _anchorX + _positionX - (_sizeX * _pivotX), wHeight * _anchorY + _positionY - (_sizeY * _pivotY));
}
