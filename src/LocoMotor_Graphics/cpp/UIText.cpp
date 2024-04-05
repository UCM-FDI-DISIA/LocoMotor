#include "UIText.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"

#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

#include "OgreResourceManager.h"
#include "OgreResource.h"

using namespace LocoMotor;

unsigned int UIText::_numOfTexts = 0;

LocoMotor::UIText::UIText() : _gfxManager(nullptr), _container(nullptr), _overlayMngr(nullptr) {
	_numOfTexts++;
	_uType = "t";
	_uTxtName = "New Text";
}

LocoMotor::UIText::~UIText() {
	_overlayMngr->destroyOverlayElement(_container);
}

void LocoMotor::UIText::setText(std::string text) {
	_uTxtName = text;
	_txtElem->setCaption(_uTxtName);
}

void LocoMotor::UIText::setFont(std::string nFont) {

	auto a = Ogre::FontManager::getSingletonPtr();

	auto res = a->createOrRetrieve(nFont, "General");

	if (!res.second) {
		_txtElem->setFontName(nFont);
		if (_uType[0] == 'i') _txtElem->getFont()->setType(Ogre::FT_IMAGE);
		else _txtElem->getFont()->setType(Ogre::FT_TRUETYPE);
	}
}

void LocoMotor::UIText::setParameters(ComponentMap& params) {

	_gfxManager = Graphics::GraphicsManager::GetInstance();
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();

	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIText" + std::to_string(_numOfTexts)));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);
	_container->setPosition(_gfxManager->getWindowWidth() * _anchorX + _positionX, _gfxManager->getWindowHeight() * _anchorY + _positionY);

	_container->setDimensions(_sizeX, _sizeY);

	_txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
		  _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfTexts)));

	_txtElem->setMetricsMode(Ogre::GMM_PIXELS);
	_txtElem->setCaption(_uTxtName);
	_txtElem->setCharHeight(_sizeY);
	_txtElem->setPosition(0, 0);
	_txtElem->setDimensions(_sizeY, _sizeX);
	_txtElem->setColourBottom(Ogre::ColourValue::Black);
	_txtElem->setColourTop(Ogre::ColourValue::Black);
	_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);

	_container->addChild(_txtElem);

	_container->show();
	_txtElem->show();

	Graphics::OverlayManager::GetInstance()->getContainer()->addChild(_container);
}

void LocoMotor::UIText::update(float dT) {
	updatePosition();
}

void LocoMotor::UIText::setAnchorPoint(float x, float y) {
	_anchorX = x;
	_anchorY = y;
	updatePosition();
}

void LocoMotor::UIText::setPosition(float x, float y) {
	_positionX = x;
	_positionY = y;
	updatePosition();
}

void LocoMotor::UIText::setDimensions(float w, float h) {
	_sizeX = w;
	_sizeY = h;
	_container->setDimensions(_sizeX, _sizeY);
}

void LocoMotor::UIText::setPivot(float x, float y) {
	_pivotX = x;
	_pivotY = y;
	updatePosition();
}

void LocoMotor::UIText::setAlignment(TextAlignment a) {
	
	switch (a) {
		case TextAlignment::LEFT:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
			break;
		case TextAlignment::CENTER:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
			break;
		case TextAlignment::RIGHT:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
			break;
		default:
			break;
	}

}

void LocoMotor::UIText::show() {
	_container->show();
}

void LocoMotor::UIText::hide() {
	_container->hide();
}

void LocoMotor::UIText::initializeABorrar() {

	std::vector<std::pair<std::string, std::string>> a;
	setParameters(a);
}

void LocoMotor::UIText::updatePosition() {
	_container->setMetricsMode(Ogre::GMM_PIXELS);
	int wWidth = _gfxManager->getWindowWidth();
	int wHeight = _gfxManager->getWindowHeight();
	_container->setPosition(wWidth * _anchorX + _positionX - (_sizeX * _pivotX), wHeight * _anchorY + _positionY - (_sizeY * _pivotY));
}
