#include "Light.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Node.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>

LocoMotor::Light::Light() {
	_light = nullptr;
	_node = nullptr;
}

void LocoMotor::Light::init(std::string name, int type) {
	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return;

	_name = name;
	_light = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createLight();
	_light->setType(Ogre::Light::LT_DIRECTIONAL);
	_node = Graphics::GraphicsManager::GetInstance()->createNode(_gameObject->getName());
	_node->Attach(_light);
	setDiffuse(1, 1, 1);
	_node->SetDirection(-1, -1, -1);

}
void LocoMotor::Light::start() {

}

void LocoMotor::Light::update(float dt) {
	//to do: hacer que la luz pueda moverse con el transform
}

LocoMotor::Light::~Light() {
	Graphics::GraphicsManager::GetInstance()->destroyNode(_node->GetName());
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