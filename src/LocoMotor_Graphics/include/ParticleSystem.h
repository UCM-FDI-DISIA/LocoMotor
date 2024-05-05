#pragma once
#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

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

	class MOTOR_API ParticleSystem : public Component {

		friend class GraphicsManager;

	public:

		ParticleSystem();
		~ParticleSystem();

		void play();
		void stop();

		void setParticle(const std::string& particleName);

	protected:

		bool setParameters(ComponentMap& params) override;
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

		bool playOnStart;

		bool emittingSelf; 

	};
}
#endif // !PARTICLE_SYSTEM