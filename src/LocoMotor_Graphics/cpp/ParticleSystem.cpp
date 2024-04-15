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
	playOnStart = false;
	emittingSelf = true;
}

LocoMotor::ParticleSystem::~ParticleSystem() {
	numOfParticleSystems--;
}

void LocoMotor::ParticleSystem::play()
{
	emittingSelf = true;
	if (!isEnabled()) return;
	unsigned short numEmitters = _particleSystem->getNumEmitters();
	for (unsigned short i = 0; i < numEmitters; i++) {
		_particleSystem->getEmitter(i)->setEnabled(true);
	}
	_particleSystem->setEmitting(true);
}

void LocoMotor::ParticleSystem::stop()
{
	emittingSelf = false;
	_particleSystem->setEmitting(false);
}

void LocoMotor::ParticleSystem::onEnable() {
	if (_particleSystem != nullptr && isEnabled())
		_particleSystem->setEmitting(emittingSelf);
}

void LocoMotor::ParticleSystem::start()
{
	if (playOnStart) {
		emittingSelf = true;
		_particleSystem->setEmitting(true);
	}
}

void LocoMotor::ParticleSystem::update(float dT) {
	if (_gameObject->getComponent<Transform>() == nullptr) return;

	Transform* tr = _gameObject->getComponent<Transform>();

	_node->setPosition(tr->getPosition().getX(), tr->getPosition().getY(), tr->getPosition().getZ());

	_node->setOrientation(tr->getRotation().getW(), tr->getRotation().getX(), tr->getRotation().getY(), tr->getRotation().getZ());

	_node->setScale(tr->getSize().getX(), tr->getSize().getY(), tr->getSize().getZ());
}

void LocoMotor::ParticleSystem::onDisable() {
	if (_particleSystem != nullptr && !isEnabled())
		_particleSystem->setEmitting(false);
}

void LocoMotor::ParticleSystem::setParameters(ComponentMap& params) {

	_node = Graphics::GraphicsManager::GetInstance()->createNode(_gameObject->getName());

	std::string particleName = "";

	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "Particle" || params[i].first == "particle") {
			particleName = params[i].second;
		}
		else if (params[i].first == "PlayOnStart" || params[i].first == "playOnStart") {
			playOnStart = true;
		}
	}

	_particleSystem = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createParticleSystem(_node->getName(), particleName);

	if (_particleSystem == nullptr) return;

	_node->attachObject(_particleSystem);

	_particleSystem->setEmitting(false);

}
