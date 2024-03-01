#include "Camera.h"
#include <OgreCamera.h>
#include <OgreViewport.h>

//#include <OgreSceneNode.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreVector3.h>


LocoMotor::Graphics::Camera::Camera() {
}

LocoMotor::Graphics::Camera::~Camera() {
}



void LocoMotor::Graphics::Camera::SetTarget(GameObject* target, LMVector3 offset)
{
	_target = target;
	_offset = offset;
}

void LocoMotor::Graphics::Camera::SetFOV(float newFov)
{
	_mCamera->setFOVy(Ogre::Radian(newFov * 3.14f / 180));
}

void LocoMotor::Graphics::Camera::SetViewportRatio(int viewportIndex, int modeIndex)
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

void LocoMotor::Graphics::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	_mCamera->setNearClipDistance(nearPlane);
	_mCamera->setFarClipDistance(farPlane);
}


void LocoMotor::Graphics::Camera::updateViewport() {
	_vp->update();
}

void LocoMotor::Graphics::Camera::start() {}

void LocoMotor::Graphics::Camera::setParameters(std::vector<std::pair<std::string, std::string>>& params) {

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


// Funcionalidad componentes

void LocoMotor::Graphics::Camera::init()
{
	_mCamera = nullptr;
	//_scene = nullptr;
	//_renderScn = nullptr;
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
}
void LocoMotor::Graphics::Camera::onEnable()
{
}
void LocoMotor::Graphics::Camera::update(float dT)
{
}
void LocoMotor::Graphics::Camera::onDisable()
{
}