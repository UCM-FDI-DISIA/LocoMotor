#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreSceneManager.h>

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
	Graphics::GraphicsManager::GetInstance()->destroyNode(_node->GetName());
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
	// PROVISIONAL
	_node->Translate(0, 0, -150);
	_node->Scale(20, 20, 20);
	_node->Rotate(20, 240, 80);
}


void LocoMotor::MeshRenderer::update(float dt) {
	// PROVISIONAL
	_node->Rotate(0, 0.1 * dt, 0);
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
			_node->Attach(_mesh);
		}
	}
	
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
