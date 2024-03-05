#include "RigidBody.h"
#include <iostream>
#include "PhysicsManager.h"

LocoMotor::RigidBody::RigidBody() {}

LocoMotor::RigidBody::~RigidBody() {}

void LocoMotor::RigidBody::setParameters(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "mass") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_mass = num;
		}
		else if (params[i].first == "damping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_damping = num;
		}
		else if (params[i].first == "angDamping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_angDamping = num;
		}
		else if (params[i].first == "gravity") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_gravity = num;
		}
		else if (params[i].first == "usedAsRaycast") {
			_raycast = true;
		}
		else if (params[i].first == "isTrigger") {
			_beATrigger = true;
		}
	}
}

void LocoMotor::RigidBody::awake() {
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LMVector3(1, 1, 1);
	info.origin = LMVector3(0, 0, 0);//gameObject->GetTransform()->GetPosition();
	info.sphereSize = 1;
	info.capsuleHeight = 1.0f;
	info.capsuleRadius = 0.5f;
	//if (_mass == 0) {
	//	MeshRenderer* mR = gameObject->GetComponent<MeshRenderer>();
	//	if (mR == nullptr)return;
	//	OgreWrapper::Renderer3D* mesh = gameObject->GetComponent<MeshRenderer>()->GetRenderer();
	//	if (mesh != nullptr) {
	//		_ms = new MeshStrider(mesh->GetMesh());
	//		_body = PhysicsManager::GetInstance()->CreateRigidBody(info, _ms);
	//		_body->setUserPointer(gameObject);
	//		if (_raycast) UseItAsRaycast();
	//		if (_beATrigger) BeATrigger();
	//		return;
	//	}
	//}
	_body = CreateRigidBody(info);
	_body->setUserPointer(_gameObject);
	//if (_raycast) UseItAsRaycast();
	//if (_beATrigger) BeATrigger();
}

void LocoMotor::RigidBody::start() {}

void LocoMotor::RigidBody::update(float dt) {}

btRigidBody* LocoMotor::RigidBody::CreateRigidBody(RigidBodyInfo info) {
	btCollisionShape* shape = nullptr;
	if (false){//ms != nullptr) {
		//shape = new btBvhTriangleMeshShape(ms, true, true);
	}
	else {
		if (info.capsuleHeight > 0.0)
			shape = new btCapsuleShapeZ(info.capsuleRadius, info.capsuleHeight);
		else if (info.sphereSize <= 0.0)
			shape = new btBoxShape(btVector3(info.boxSize.GetX(), info.boxSize.GetY(), info.boxSize.GetZ()));
		else if (info.sphereSize)
			shape = new btSphereShape(info.sphereSize);
	}
	if (shape == nullptr)return nullptr;
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(info.origin.GetX(), info.origin.GetY(), info.origin.GetZ()));

	btScalar mass(info.mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* rigidbody = new btRigidBody(rbInfo);

	//add the body to the dynamics world;
	LocoMotor::Physics::PhysicsManager::GetInstance()->getDynamicWorld()->addRigidBody(rigidbody);
	rigidbody->setDamping(0.7f, 0.7f);

	if (isDynamic) {
		rigidbody->setCcdMotionThreshold(0.000000001f);//0.0000001f
		rigidbody->setCcdSweptSphereRadius(0.5f);
	}
	return rigidbody;
}

LocoMotor::RigidBodyInfo::RigidBodyInfo() {

}
