#include "ParticleSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "GraphicsManager.h"

#include <OgreParticleEmitter.h>
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

uint32_t LocoMotor::ParticleSystem::numOfParticleSystems = 0;

LocoMotor::ParticleSystem::ParticleSystem() {
	_node = nullptr;
	_particleSystem = nullptr;
	numOfParticleSystems++;
	plsyOnStart = false;
}

LocoMotor::ParticleSystem::~ParticleSystem() {
	Graphics::GraphicsManager::GetInstance()->destroyNode(_node->getName());
	numOfParticleSystems--;
}

void LocoMotor::ParticleSystem::play()
{
	unsigned short numEmitters = _particleSystem->getNumEmitters();
	for (unsigned short i = 0; i < numEmitters; i++) {
		_particleSystem->getEmitter(i)->setEnabled(true);
	}
	_particleSystem->setEmitting(true);
}

void LocoMotor::ParticleSystem::stop()
{
	_particleSystem->setEmitting(false);
}

void LocoMotor::ParticleSystem::onEnable() {}

void LocoMotor::ParticleSystem::start()
{
	if (plsyOnStart)
		_particleSystem->setEmitting(true);
}

void LocoMotor::ParticleSystem::update(float dT) {
	if (_gameObject->getComponent<Transform>() == nullptr) return;

	Transform* tr = _gameObject->getComponent<Transform>();

	_node->setPosition(tr->GetPosition().GetX(), tr->GetPosition().GetY(), tr->GetPosition().GetZ());

	_node->setOrientation(tr->GetRotation().GetW(), tr->GetRotation().GetX(), tr->GetRotation().GetY(), tr->GetRotation().GetZ());

	_node->setScale(tr->GetSize().GetX(), tr->GetSize().GetY(), tr->GetSize().GetZ());
}

void LocoMotor::ParticleSystem::onDisable() {}

void LocoMotor::ParticleSystem::setParameters(ComponentMap& params) {

	_node = Graphics::GraphicsManager::GetInstance()->createNode(_gameObject->getName() + "nopeteTemporal");

	std::string particleName = "";

	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "Particle" || params[i].first == "particle") {
			particleName = params[i].second;
		}
		else if (params[i].first == "PlayOnStart" || params[i].first == "playOnStart") {
			plsyOnStart = true;
		}
	}

	_particleSystem = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createParticleSystem(_node->getName(), particleName);

	if (_particleSystem == nullptr) return;

	_node->attachObject(_particleSystem);

	_particleSystem->setEmitting(false);

}
