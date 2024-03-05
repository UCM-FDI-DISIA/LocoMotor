#pragma once

#include "Component.h"

namespace Ogre {
	class Entity;
	class MovableObject;
}

namespace LocoMotor {
	class GameObject;
	class MeshRenderer :public LocoMotor::Component {
	public:
		//MeshRenderer(Ogre::Entity* rend);
		MeshRenderer();
		~MeshRenderer();
		
		Ogre::MovableObject* getMovObj();
		void setMaterial(std::string mat);
		void init(std::string name, std::string file,bool istatic);
		void start();
		void update(float dt);
		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
		/// @brief Sets the Mesh renderer visible/invisible
	    void setVisible(bool visible);

	private:
		Ogre::Entity* _mesh;
		std::string _mat;
		std::string _name;
		std::string _src;
		bool _isStatic;

		GameObject* _gObj;
		//RenderScene*


	};
	
}