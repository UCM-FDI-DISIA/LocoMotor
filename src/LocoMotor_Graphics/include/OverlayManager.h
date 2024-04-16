#pragma once
#ifndef OVERLAY_MANAGER
#define OVERLAY_MANAGER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace Ogre {
	class SceneManager;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
	class OverlayContainer;
}

namespace LocoMotor {

	namespace Graphics {

		class MOTOR_API OverlayManager {
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

			/// @brief Returns true if there is an instance of the singleton active
			static bool IsInitialized();

			static void stringToAnchors(const std::string& s, float& x, float& y);
			static void stringToPosition(const std::string& s, int& x, int& y);

			Ogre::OverlayManager* getOgreOverlayManager();
			Ogre::OverlaySystem* getOgreSystem();

		private:

			bool init();

			Ogre::OverlaySystem* _ovrsys;

			Ogre::OverlayManager* _ogrOverlayManager;

			static OverlayManager* _instance;

			static unsigned int _numOfCanvas;

		};
	}

}

#endif