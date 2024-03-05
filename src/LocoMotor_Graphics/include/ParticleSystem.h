#pragma once

#include "Component.h"
#include "LMVector.h"
#include <string>
#include <unordered_map>

//#include <OgreParticleSystem.h>

namespace Ogre {
	class ParticleSystem;
	class ParticleEmitter;
	class Node;
	class RenderScene;
}

namespace LocoMotor{

	class Scene;
	class GameObject;

	class ParticleSystem : public Component {

		friend class GraphicsManager;

	protected:

		void init()/* override*/;
		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void onEnable() override;
		void start() override;
		void update(float dT) override;
		void onDisable() override;


	private:

		// Nodo de ogre
		Ogre::Node* _node;

		// Referencia a la escena de render
		//OgreWrapper::RenderScene* _renderScn;
		//OgreWrapper::ParticleHelper* _particleHelper;

		std::string _filename;
		std::string _name;

		// Emitidores de particulas de Ogre
		std::unordered_map <std::string, Ogre::ParticleEmitter*> _emitters;

		// Sistema de particulas de Ogre
		Ogre::ParticleSystem* _particleSystem;

		/// @brief Gets an emmiter with a name
		Ogre::ParticleEmitter* GetEmitter(std::string name);

		//Ogre::Vector3* LmVectorToOgreVector(const LMVector3 lmVector);

	public:

		ParticleSystem();
		~ParticleSystem();

		/// @brief Adds an emmiter with a name in a position
		void AddEmitter(std::string name, const LMVector3 position);

		/// @brief Removes an emmiter with a name
		void RemoveEmitter(std::string name);

		/// @brief Moves an emmiter with a name to a position
		void MoveEmitter(std::string name, const LMVector3 position);

		/// @brief Rotates an emmiter with a name to a rotation
		void RotateEmitter(std::string name, const LMVector3 position);

		/// @brief Sets the emitter with a name, emmiting boolean
		void SetEmitting(std::string name, bool emitting);
	};
}