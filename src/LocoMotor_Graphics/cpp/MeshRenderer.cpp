#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreSceneManager.h>

#include <iostream>
#include "GameObject.h"
#include "Node.h"

LocoMotor::MeshRenderer::MeshRenderer() {
	_gObj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_mesh = nullptr;
	_isStatic = false;
	_node = nullptr;
}

LocoMotor::MeshRenderer::~MeshRenderer()
{
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

}

void LocoMotor::MeshRenderer::setVisible(bool visible) {
	if (_mesh != nullptr) {
		_mesh->setVisible(visible);
	}
}
void LocoMotor::MeshRenderer::setMaterial(std::string mat) {
	if (_mesh != nullptr) {
		_mesh->setMaterialName(mat);
		//std::cout << _mesh->getParentNode()->getPosition().x << _mesh->getParentNode()->getPosition().y << _mesh->getParentNode()->getPosition().z << std::endl;
		//_node->Translate(0, 0, -100);
		_node->Scale(10, 10, 10);
		_node->Rotate(0, 45, 45);
		std::cout << _node->GetPosition_X()<<" " << _node->GetPosition_Y() <<" "<< _node->GetPosition_Z() << std::endl;
	}
}

void LocoMotor::MeshRenderer::setMesh(std::string mesh) {
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh)) {
		_mesh = LocoMotor::Graphics::GraphicsManager::GetInstance()->createRenderer(mesh);
		if (_mesh != nullptr) {
			_node->Attach(_mesh);
		}
	}
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
