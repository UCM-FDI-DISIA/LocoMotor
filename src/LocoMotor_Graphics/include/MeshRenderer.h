#pragma once

#include "Component.h"

namespace Ogre {
	class Entity;
	class MovableObject;
}

namespace LocoMotor {
	class GameObject;

	namespace Graphics {
		class GraphicsManager;
	}

	class MeshRenderer :public LocoMotor::Component {
		friend class Graphics::GraphicsManager;
	public:

		MeshRenderer();
		~MeshRenderer();
		
		void setMaterial(std::string mat);

		void setMesh(std::string mesh);
		
		/// @brief Sets the Mesh renderer visible/invisible
	    void setVisible(bool visible);

	protected:


		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
		void init(std::string name, std::string file, bool istatic);
		void start();
		void update(float dt);

	private:
		Ogre::Entity* _mesh;
		std::string _mat;
		std::string _name;
		std::string _src;
		bool _isStatic;

		GameObject* _gObj;

		Ogre::MovableObject* getMovObj();
	};
	
}