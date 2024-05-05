#pragma once
#ifndef UI_IMAGE
#define UI_IMAGE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

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

	class MOTOR_API UIImage : public Component {

	public:
		UIImage();
		virtual ~UIImage();

		void setImage(const std::string& nImage);

		/// @brief Sets the anchor point of the element
		void setAnchorPoint(float x, float y);

		/// @brief Sets the position of the entity on the UI
		void setPosition(int x, int y);

		/// @brief Sets the size of the entity on the UI
		void setDimensions(int w, int h);

		/// @brief Sets the pivot of the image
		void setPivot(float x, float y);

		/// @brief Sets the new sorting layer of the element, the higher the number the more priotity it will have
		/// @param layer: A number, only values between 0 and 650 are sorted between them
		void setSortingLayer(int layer);

		/// @brief Sets the rotation of this element, with the pivot located in the center of the screen in radians
		void setRotation(float radians);

		/// @brief Shows/turns visible the entity on the UI
		void show();

		/// @brief Hides/turns invisible the entity on the UI
		void hide();

		int getWidth();
		int getHeight();

	protected:

		bool setParameters(ComponentMap& params) override;
		void start() override {};
		void update(float dT) override;

	private:

		void updatePosition();

		Graphics::GraphicsManager* _gfxManager;

		Ogre::Overlay* _overlay;
		Ogre::OverlayContainer* _container;
		Ogre::OverlayManager* _overlayMngr;

		float _anchorX = 0.5f, _anchorY = 0.5f;
		float _pivotX = 0.5f, _pivotY = 0.5f;
		int _positionX = 0, _positionY = 0;
		int _sizeX = 50, _sizeY = 50;
	};

}

#endif
