#pragma once

#include "Component.h"
#include "LMVector.h"
#include <string>
#include <unordered_map>

//#include <OgreParticleSystem.h>

namespace Ogre {
	class ParticleSystem;
	class SceneNode;
}

namespace LocoMotor{

	class Scene;
	class GameObject;

	class ParticleSystem : public Component {

		friend class GraphicsManager;

	public:

		ParticleSystem();
		~ParticleSystem();

	protected:

		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void onEnable() override;
		void start() override;
		void update(float dT) override;
		void onDisable() override;


	private:

		// Nodo de ogre
		Ogre::SceneNode* _node;

		// Sistema de particulas de Ogre
		Ogre::ParticleSystem* _particleSystem;

		static uint32_t numOfParticleSystems;

		bool plsyOnStart;

	};
}