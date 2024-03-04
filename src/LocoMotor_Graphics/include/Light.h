#pragma once

#include <OgreLight.h>
#include "Component.h"
namespace LocoMotor {
	class Light:public Component {
	public:
		Light();
		~Light();
		//Ogre::MovableObject* getMovObj();
		Ogre::Light* getLight();
		/// @brief Sets the diffuse value of the light
		void setDiffuse(float x, float y, float z);
		/// @brief Sets the specular value of the light
		void setSpecular(float x, float y, float z);
		void init(Ogre::Light* l, Ogre::Light::LightTypes type);
		void start();
		void update(float dt);
		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
	protected:
		Ogre::Light* _light;
	};
	
}