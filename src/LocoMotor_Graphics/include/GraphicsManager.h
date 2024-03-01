#ifndef _GRAPHICS_MANAGER_H
#define _GRAPHICS_MANAGER_H

#include <map>
#include <OgreMaterialManager.h>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class SceneNode;
	class OverlaySystem;
	namespace RTShader {
		class ShaderGenerator;
	}
}

struct SDL_Window;
namespace LocoMotor {
	namespace Graphics {

		class Camera;

		struct NativeWindowPair {
			Ogre::RenderWindow* render = nullptr;
			SDL_Window* native = nullptr;
		};
		class GraphicsManager {
		public:
			/// @brief Initializes the OgreManager singleton with a name for the new window
			/// @param name Name for the window.
			/// @return whether the initialize went well or not.
			///	If the name is already taken, the scene with that name will be returned instead.
			std::string initialize(std::string name);


			/// @brief Creates a scene, if you try to create a scene with an already used name, the method will return that scene instead.
			/// @param name Name for the new scene.
			/// @return The newly created scene.
			///	If the name is already taken, the scene with that name will be returned instead.
			void createScene(std::string name);


			/// @brief Renders a frame.
			void render();

			/// @brief 
			/// Returns RenderWindow
			/// @return Render window of Ogre
			Ogre::RenderWindow* getRenderWindow();

			/// @brief
			/// Sets the active scene for the manager
			/// @param name The name of the scene to become active
			void setActiveScene(std::string name);
			/// @brief Returns the render window height
			int getWindowHeight();
			/// @brief Returns the render window width
			int getWindowWidth();

			GraphicsManager* getInstance();

			void setActiveCamera(Camera* cam);

			Camera* getMainCamera();

			Camera* createCamera(std::string name);

			void deactivateScene(std::string name);
		protected:
			Ogre::Root* _root;
			NativeWindowPair _mWindow;

			std::map<std::string , Ogre::SceneManager*> _scenes;

			Ogre::MaterialManager::Listener* _mMaterialMgrListener = nullptr;

			Ogre::SceneManager* _activeScene;

			Ogre::RTShader::ShaderGenerator* _mShaderGenerator;

			Ogre::OverlaySystem* _ovrSys;

			Camera* _mainCamera;

			/// @brief Creates a new OgreManager.
			/// @param name The name for the window
			GraphicsManager();
			~GraphicsManager();

			/// @brief Loads the resouces and initializes the RTShaderSytem
			void loadResources();

			/// @brief Initializes the window
			/// @param name The Window title
			/// @return
			NativeWindowPair initWindow(std::string name);

			/// @brief
			/// Shuts down Ogre and releases all the memory related to it
			void shutdown();

		};
	}
}

#endif
