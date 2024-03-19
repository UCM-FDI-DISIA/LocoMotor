#pragma once
#ifndef UI_TEXT
#define UI_TEXT

#include <string>
#include "Component.h"

namespace Ogre {
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
	class TextAreaOverlayElement;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;

	}

	enum class TextAlignment {
		LEFT,
		CENTER,
		RIGHT
	};

	class UIText : public Component {

	public:
		UIText();
		virtual ~UIText();

		void setText(std::string text);

		void setFont(std::string nFont);

		/// @brief Sets the anchor point of the element
		void setAnchorPoint(float x, float y);

		/// @brief Sets the position of the entity on the UI
		void setPosition(float x, float y);

		/// @brief Sets the size of the entity on the UI
		void setDimensions(float w, float h);

		/// @brief Sets the pivot of the textbox
		void setPivot(float x, float y);

		void setAlignment(TextAlignment a);

		/// @brief Shows/turns visible the entity on the UI
		void show();

		/// @brief Hides/turns invisible the entity on the UI
		void hide();

		void initializeABorrar();

	protected:

		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void start() override {};
		void update(float dT) override;

	private:

		void updatePosition();

		Graphics::GraphicsManager* _gfxManager;

		Ogre::OverlayContainer* _container;
		Ogre::OverlayManager* _overlayMngr;

		static unsigned int _numOfTexts;

		Ogre::TextAreaOverlayElement* _txtElem;
		std::string _uFont;
		std::string _uType;
		std::string _uTxtName;

		float _anchorX = 0.5f, _anchorY = 0.5f;
		float _pivotX = 0.5f, _pivotY = 0.5f;
		int _positionX = 0, _positionY = 0;
		int _sizeX = 100, _sizeY = 50;
	};

}

#endif
