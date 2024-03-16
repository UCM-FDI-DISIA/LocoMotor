#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreSceneManager.h>

#include "GameObject.h"
#include "Transform.h"

LocoMotor::MeshRenderer::MeshRenderer() {
	_name = "";
	_src = "";
	_mat = "";
	_mesh = nullptr;
	_isStatic = false;
	_node = nullptr;
	_nodeScale = LMVector3(1, 1, 1);
	_nodeRotation = LMQuaternion();
}

LocoMotor::MeshRenderer::~MeshRenderer()
{
	Graphics::GraphicsManager::GetInstance()->destroyNode(_node->getName());
}

void LocoMotor::MeshRenderer::setParameters(std::vector<std::pair<std::string, std::string>>& params)
{
}

void LocoMotor::MeshRenderer::init(std::string name, std::string file,bool istatic) {
	_name = name;
	_src = file;
	_isStatic = istatic;
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());
}

void LocoMotor::MeshRenderer::start() {

}


void LocoMotor::MeshRenderer::update(float dt) {
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

void LocoMotor::MeshRenderer::setVisible(bool visible) {
	if (_mesh != nullptr) {
		_mesh->setVisible(visible);
	}
}
void LocoMotor::MeshRenderer::setMaterial(std::string mat) {
	if (_mesh != nullptr) {
		_mesh->setMaterialName(mat);
	}
}

void LocoMotor::MeshRenderer::setMesh(std::string mesh) {
	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return;
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh)) {
		_mesh = LocoMotor::Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createEntity(mesh);
		if (_mesh != nullptr) {
			_node->attachObject(_mesh);
		}
	}
	
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
