#pragma once

#include "Component.h"
namespace Ogre {
	class Light;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
		class Node;
	}
	class Light:public Component {
		friend class Graphics::GraphicsManager;
	public:
		
		Light();
		~Light();
		void init(std::string name, int type);
		/// @brief Sets the diffuse value of the light
		void setDiffuse(float x, float y, float z);
		/// @brief Sets the specular value of the light
		void setSpecular(float x, float y, float z);
		
	protected:
		Ogre::Light* _light;
		
		void start();
		void update(float dt);

	private:
		
		//Ogre::MovableObject* getMovObj();
		Ogre::Light* getLight();
		std::string _name;
		Graphics::Node* _node;

		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
	};
	
}