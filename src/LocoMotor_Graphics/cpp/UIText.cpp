#include "UIText.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"
#include "LMVector.h"

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

	if (nFont == "") return;

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

	std::string text = "New Text";
	std::string font = "";
	Ogre::TextAreaOverlayElement::Alignment alignment = Ogre::TextAreaOverlayElement::Alignment::Left;
	LMVector3 colTop = LMVector3();
	LMVector3 colBot = LMVector3();

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
		else if (param.first == "Text" || param.first == "text") {
			text = param.second;
		}
		else if (param.first == "Font" || param.first == "font") {
			font = param.second;
		}
		else if (param.first == "Alignment" || param.first == "alignment") {
			if (param.second[0] == 'C' || param.second[0] == 'c') {
				alignment = Ogre::TextAreaOverlayElement::Alignment::Center;
			}
			else if (param.second[0] == 'R' || param.second[0] == 'r') {
				alignment = Ogre::TextAreaOverlayElement::Alignment::Right;
			}
		}
		else if (param.first == "ColorTop" || param.first == "colorTop") {
			colTop = LMVector3::StringToVector(param.second);
		}
		else if (param.first == "ColorBot" || param.first == "colorBot") {
			colBot = LMVector3::StringToVector(param.second);
		}
	}

	_container->setDimensions(_sizeX, _sizeY);

	updatePosition();

	_txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
		  _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfTexts)));
	_txtElem->setMetricsMode(Ogre::GMM_PIXELS);

	setFont(font);
	setText(text);
	_txtElem->setCharHeight(_sizeY);
	_txtElem->setColourTop(Ogre::ColourValue(colTop.GetX(), colTop.GetY(), colTop.GetZ(), 1.f));
	_txtElem->setColourBottom(Ogre::ColourValue(colBot.GetX(), colBot.GetY(), colBot.GetZ(), 1.f));
	_txtElem->setAlignment(alignment);


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
