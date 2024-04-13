#include "Light.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <Transform.h>
#include <iostream>

LocoMotor::Light::Light() {
	_light = nullptr;
	_node = nullptr;
	_nodeScale = LMVector3(1, 1, 1);
	_nodeRotation = LMQuaternion();
}

void LocoMotor::Light::start() {
	if (_gameObject->getComponent<Transform>() == nullptr) {
		std::cerr << "GameObject with name '" << _gameObject->getName() << "' has no Transform component\n";
		return;
	}
}

void LocoMotor::Light::update(float dt) {
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	_node->setPosition(_gameObject->getComponent<Transform>()->getPosition().getX(), _gameObject->getComponent<Transform>()->getPosition().getY(), _gameObject->getComponent<Transform>()->getPosition().getZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	if (_nodeRotation.getW() != _gameObject->getComponent<Transform>()->getRotation().getW()) {
		quat.w = _gameObject->getComponent<Transform>()->getRotation().getW();
		_nodeRotation.setW(_gameObject->getComponent<Transform>()->getRotation().getW());
	}
	if (_nodeRotation.getX() != _gameObject->getComponent<Transform>()->getRotation().getX()) {
		quat.x = _gameObject->getComponent<Transform>()->getRotation().getX();
		_nodeRotation.setX(_gameObject->getComponent<Transform>()->getRotation().getX());
	}
	if (_nodeRotation.getY() != _gameObject->getComponent<Transform>()->getRotation().getY()) {
		quat.y = _gameObject->getComponent<Transform>()->getRotation().getY();
		_nodeRotation.setY(_gameObject->getComponent<Transform>()->getRotation().getY());
	}
	if (_nodeRotation.getZ() != _gameObject->getComponent<Transform>()->getRotation().getZ()) {
		quat.z = _gameObject->getComponent<Transform>()->getRotation().getZ();
		_nodeRotation.setZ(_gameObject->getComponent<Transform>()->getRotation().getZ());
	}
	_node->rotate(quat, Ogre::Node::TS_LOCAL);

	if (_nodeScale.getX() != _gameObject->getComponent<Transform>()->getSize().getX()) {
		_node->scale(_gameObject->getComponent<Transform>()->getSize().getX(), 1, 1);
		_nodeScale.setX(_gameObject->getComponent<Transform>()->getSize().getX());
	}
	if (_nodeScale.getY() != _gameObject->getComponent<Transform>()->getSize().getY()) {
		_node->scale(1, _gameObject->getComponent<Transform>()->getSize().getY(), 1);
		_nodeScale.setY(_gameObject->getComponent<Transform>()->getSize().getY());
	}
	if (_nodeScale.getZ() != _gameObject->getComponent<Transform>()->getSize().getZ()) {
		_node->scale(1, 1, _gameObject->getComponent<Transform>()->getSize().getZ());
		_nodeScale.setZ(_gameObject->getComponent<Transform>()->getSize().getZ());
	}
}

LocoMotor::Light::~Light() {
	//Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->destroyLight(_light);
}

void LocoMotor::Light::setDiffuse(float r, float g, float b) {
	_light->setDiffuseColour(r, g, b);
}

void LocoMotor::Light::setSpecular(float r, float g, float b) {
	_light->setSpecularColour(r, g, b);
}

void LocoMotor::Light::setParameters(ComponentMap& params){
	_light = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createLight();
	_light->setType(Ogre::Light::LT_DIRECTIONAL);
	_node = Graphics::GraphicsManager::GetInstance()->createNode(_gameObject->getName());
	_node->attachObject(_light);
	setDiffuse(1, 1, 1);
	setSpecular(1, 1, 1);

	for (auto& param : params) {
		if (param.first == "Diffuse" || param.first == "diffuse") {
			try {
				auto col = LMVector3::stringToVector(param.second);
				setDiffuse(col.getX(), col.getY(), col.getZ());
			}
			catch (...) {
			}
		}
		else if (param.first == "Specular" || param.first == "specular") {
			try {
				auto col = LMVector3::stringToVector(param.second);
				setSpecular(col.getX(), col.getY(), col.getZ());
			}
			catch (...) {
			}
		}
	}
}