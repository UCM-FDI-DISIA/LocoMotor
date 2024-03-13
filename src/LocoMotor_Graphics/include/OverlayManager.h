#pragma once
#ifndef OVERLAY_MANAGER
#define OVERLAY_MANAGER

namespace Ogre {
	class SceneManager;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
	class OverlayContainer;
}

namespace LocoMotor {

	namespace Graphics {

		struct AnchorPoint {
			float x = 0;
			float y = 0;
		};

		struct UIPosition {
			short x = 0;
			short y = 0;
		};

		class RenderScene;
		class UIElement;

		class OverlayManager {
		public:
			OverlayManager();
			~OverlayManager();

			/// @brief Inits the canvas to the sceneManager
			/// @return whether it went well or not (abort)
			static bool Init();

			/// @brief Get a reference to the singleton instance
			/// @return bru h
			static OverlayManager* GetInstance();

			/// @brief Destroys the canvas
			static void Release();

			Ogre::OverlayContainer* getContainer();
			Ogre::OverlaySystem* getSystem();

		private:

			bool init();

			Ogre::OverlaySystem* _ovrsys;

			Ogre::Overlay* _canvas;
			Ogre::OverlayContainer* _container;

			static OverlayManager* _instance;

			static unsigned int _numOfCanvas;

		};
	}

}

#endif