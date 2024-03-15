#pragma once
#ifndef UI_IMAGE
#define UI_IMAGE

#include <string>
#include "Component.h"

namespace Ogre {
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
	}

	class UIImage : public Component {

	public:
		UIImage();
		virtual ~UIImage();

		void setImage(std::string nImage);

		/// @brief Sets the anchor point of the element
		void setAnchorPoint(float x, float y);

		/// @brief Sets the position of the entity on the UI
		void setPosition(float x, float y);

		/// @brief Sets the size of the entity on the UI
		void setDimensions(float w, float h);

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

		static unsigned int _numOfImages;

		float _anchorX = 0.5f, _anchorY = 0.5f;
		float _pivotX = 0.5f, _pivotY = 0.5f;
		int _positionX = 0, _positionY = 0;
		int _sizeX = 100, _sizeY = 50;
	};

}

#endif
