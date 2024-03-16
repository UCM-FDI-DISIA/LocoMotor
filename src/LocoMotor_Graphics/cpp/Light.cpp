#include "Light.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <Transform.h>

LocoMotor::Light::Light() {
	_light = nullptr;
	_node = nullptr;
	_nodeScale = LMVector3(1, 1, 1);
	_nodeRotation = LMQuaternion();
}

void LocoMotor::Light::init(std::string name, int type) {
	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return;

	_name = name;
	_light = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createLight();
	_light->setType(Ogre::Light::LT_DIRECTIONAL);
	_node = Graphics::GraphicsManager::GetInstance()->createNode(_gameObject->getName());
	_node->attachObject(_light);
	setDiffuse(1, 1, 1);
	_node->setDirection(-1, -1, -1);

}
void LocoMotor::Light::start() {

}

void LocoMotor::Light::update(float dt) {
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	_node->setPosition(_gameObject->getComponent<Transform>()->GetPosition().GetX(), _gameObject->getComponent<Transform>()->GetPosition().GetY(), _gameObject->getComponent<Transform>()->GetPosition().GetZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	if (_nodeRotation.GetW() != _gameObject->getComponent<Transform>()->GetRotation().GetW()) {
		quat.w = _gameObject->getComponent<Transform>()->GetRotation().GetW();
		_nodeRotation.SetW(_gameObject->getComponent<Transform>()->GetRotation().GetW());
	}
	if (_nodeRotation.GetX() != _gameObject->getComponent<Transform>()->GetRotation().GetX()) {
		quat.x = _gameObject->getComponent<Transform>()->GetRotation().GetX();
		_nodeRotation.SetX(_gameObject->getComponent<Transform>()->GetRotation().GetX());
	}
	if (_nodeRotation.GetY() != _gameObject->getComponent<Transform>()->GetRotation().GetY()) {
		quat.y = _gameObject->getComponent<Transform>()->GetRotation().GetY();
		_nodeRotation.SetY(_gameObject->getComponent<Transform>()->GetRotation().GetY());
	}
	if (_nodeRotation.GetZ() != _gameObject->getComponent<Transform>()->GetRotation().GetZ()) {
		quat.z = _gameObject->getComponent<Transform>()->GetRotation().GetZ();
		_nodeRotation.SetZ(_gameObject->getComponent<Transform>()->GetRotation().GetZ());
	}
	_node->rotate(quat, Ogre::Node::TS_LOCAL);

	if (_nodeScale.GetX() != _gameObject->getComponent<Transform>()->GetSize().GetX()) {
		_node->scale(_gameObject->getComponent<Transform>()->GetSize().GetX(), 1, 1);
		_nodeScale.SetX(_gameObject->getComponent<Transform>()->GetSize().GetX());
	}
	if (_nodeScale.GetY() != _gameObject->getComponent<Transform>()->GetSize().GetY()) {
		_node->scale(1, _gameObject->getComponent<Transform>()->GetSize().GetY(), 1);
		_nodeScale.SetY(_gameObject->getComponent<Transform>()->GetSize().GetY());
	}
	if (_nodeScale.GetZ() != _gameObject->getComponent<Transform>()->GetSize().GetZ()) {
		_node->scale(1, 1, _gameObject->getComponent<Transform>()->GetSize().GetZ());
		_nodeScale.SetZ(_gameObject->getComponent<Transform>()->GetSize().GetZ());
	}
}

LocoMotor::Light::~Light() {
	Graphics::GraphicsManager::GetInstance()->destroyNode(_node->getName());
	//Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->destroyLight(_light);
}

//Ogre::MovableObject* LocoMotor::Light::getMovObj() {
//	return _light;
//}
Ogre::Light* LocoMotor::Light::getLight() {
	return _light;
}

void LocoMotor::Light::setDiffuse(float r, float g, float b) {
	_light->setDiffuseColour(r, g, b);
}

void LocoMotor::Light::setSpecular(float r, float g, float b) {
	_light->setSpecularColour(r, g, b);
}

void LocoMotor::Light::setParameters(std::vector<std::pair<std::string, std::string>>& params){

}