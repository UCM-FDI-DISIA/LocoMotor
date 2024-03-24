#pragma once

#include "Component.h"
#include "LMVector.h"
#include <unordered_map>

namespace Ogre {
	class Entity;
	class MovableObject;
	class Mesh;
	class SceneNode;
	class AnimationState;
}

namespace LocoMotor {

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

		void init(std::string name, std::string file, bool istatic);


		void playAnimation(std::string animationName, bool loop);
		void updateAnimation(double time);

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
		LMVector3 _nodeScale;
		LMQuaternion _nodeRotation;

		Ogre::SceneNode* _node;

		Ogre::MovableObject* getMovObj();


		// Prueba animaciones
		std::unordered_map<std::string, Ogre::AnimationState*> allAnimations;

		// The animation that is currently being played
		Ogre::AnimationState* currentAnimation;

		int numAnimationsActive;
	};
	
}