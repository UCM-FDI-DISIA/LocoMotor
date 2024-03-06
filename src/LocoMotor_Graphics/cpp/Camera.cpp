#include "Camera.h"
#include <OgreCamera.h>
#include <OgreViewport.h>
#include "GraphicsManager.h"
#include "OgreSceneManager.h"
#include "Node.h"
#include "GameObject.h"
#include <OgreRenderWindow.h>

//#include <OgreSceneNode.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreVector3.h>


LocoMotor::Camera::Camera() : _mCamera(nullptr), _target(nullptr), _vp(nullptr) {
	_offset = LMVector3(0, 0, 0);
}

LocoMotor::Camera::~Camera() {
}



void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset)
{
	_target = target;
	_offset = offset;
}

void LocoMotor::Camera::SetFOV(float newFov)
{
	_mCamera->setFOVy(Ogre::Radian(newFov * 3.14f / 180));
}

void LocoMotor::Camera::SetViewportRatio(int viewportIndex, int modeIndex)
{
	if (modeIndex == 0) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 1) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 2) {
		_vp->setDimensions(0.0f, 0.5f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
}

void LocoMotor::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	_mCamera->setNearClipDistance(nearPlane);
	_mCamera->setFarClipDistance(farPlane);
}


void LocoMotor::Camera::updateViewport() {
	_vp->update();
}

void LocoMotor::Camera::start() {}

void LocoMotor::Camera::setParameters(std::vector<std::pair<std::string, std::string>>& params) {

	for (auto& param : params) {
		if (param.first == "CameraMode") {
			try {
				int modeIndex = std::stoi(param.second);
				SetViewportRatio(1, modeIndex); //ViewportIndex = 1 TEMPORAL
			}
			catch (...) {
			}
		}
		else if (param.first == "FOV" || param.first == "fov") {
			try {
				float fov = std::stof(param.second);
				SetFOV(fov);
			}
			catch (...) {
			}
		}
		else if (param.first == "target") {
			//_target = param.second;
		}
		else if (param.first == "main") {
			//gameObject->GetScene()->SetCamObj(gameObject);
		}
	}
}

void LocoMotor::Camera::render() {
	_vp->update();
}

// Funcionalidad componentes

void LocoMotor::Camera::init()
{
	_man = Graphics::GraphicsManager::GetInstance();
	_node = _man->createNode(_gameObject->getName());
	_mCamera = _man->getSceneManager()->createCamera(_gameObject->getName());
	_node->Attach(_mCamera);
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
	_vp = LocoMotor::Graphics::GraphicsManager::GetInstance()->getRenderWindow()->addViewport(_mCamera, 0);
	_vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
}
void LocoMotor::Camera::onEnable()
{
}
void LocoMotor::Camera::update(float dT)
{
}
void LocoMotor::Camera::onDisable()
{
}
