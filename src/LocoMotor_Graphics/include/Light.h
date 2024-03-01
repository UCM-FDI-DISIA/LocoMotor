#pragma once

#include <OgreLight.h>
#include "Component.h"
namespace LocoMotor {
	class Light:public Component {
	public:
		Light();
		~Light();
		Ogre::MovableObject* GetMovObj();
		void setDiffuse(float x, float y, float z);
		void setSpecular(float x, float y, float z);
		void init(Ogre::Light* l, Ogre::Light::LightTypes type);
		void start();
		void update(float dt);
	protected:
		Ogre::Light* _light;
	};
	
}