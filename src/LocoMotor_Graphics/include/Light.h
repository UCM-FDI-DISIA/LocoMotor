#pragma once

#include <OgreLight.h>
#include "Component.h"
namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
	}
	class Light:public Component {
		friend class Graphics::GraphicsManager;
	public:
		
		/// @brief Sets the diffuse value of the light
		void setDiffuse(float x, float y, float z);
		/// @brief Sets the specular value of the light
		void setSpecular(float x, float y, float z);
		
	protected:
		Ogre::Light* _light;
		void init(Ogre::Light* l, Ogre::Light::LightTypes type);
		void start();
		void update(float dt);

	private:
		Light();
		~Light();
		//Ogre::MovableObject* getMovObj();
		Ogre::Light* getLight();

		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
	};
	
}