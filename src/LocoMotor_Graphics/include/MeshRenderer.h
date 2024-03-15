#pragma once

#include "Component.h"

namespace Ogre {
	class Entity;
	class MovableObject;
	class Mesh;
}

namespace LocoMotor {
	class GameObject;

	namespace Graphics {
		class GraphicsManager;
		class Node;

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

		void init(std::string name, std::string file, bool istatic);

		Ogre::Mesh* getMesh();
	protected:


		void setParameters(std::vector<std::pair<std::string, std::string>>& params);
		void start();
		void update(float dt);

	private:
		Ogre::Entity* _mesh;
		std::string _mat;
		std::string _name;
		std::string _src;
		bool _isStatic;

		GameObject* _gObj;

		Graphics::Node* _node;

		Ogre::MovableObject* getMovObj();
	};
	
}