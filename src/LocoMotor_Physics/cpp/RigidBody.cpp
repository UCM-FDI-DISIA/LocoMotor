#include "RigidBody.h"
#include <iostream>
#include "PhysicsManager.h"
#include "btBulletDynamicsCommon.h"
#include "BulletVectorConverter.h"

#include "GameObject.h"
#include "Transform.h"

using namespace LocoMotor;
using namespace Physics;

LocoMotor::RigidBody::RigidBody() {}

LocoMotor::RigidBody::~RigidBody() {
	if (_body == nullptr)return;
	Physics::PhysicsManager::GetInstance()->getDynamicWorld()->removeRigidBody(_body);
	if (_body && _body->getMotionState()) {
		delete _body->getMotionState();
	}
	delete _body->getCollisionShape();
	delete _body;
}

void LocoMotor::RigidBody::setParameters(ComponentMap& params) {
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
			info.mass = num;
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
		else if (params[i].first == "size" || params[i].first == "scale") {
			 info.boxSize= LMVector3::stringToVector(params[i].second);
		}
		else if (params[i].first == "pos" || params[i].first == "center" || params[i].first == "origin") {
			info.origin = LMVector3::stringToVector(params[i].second);
		}
		else if (params[i].first == "sphereSize") {
			info.sphereSize = std::stof(params[i].second);
		}
		else if (params[i].first == "capsuleHeight") {
			info.capsuleHeight = std::stof(params[i].second);
		}
		else if (params[i].first == "capsuleRadius") {
			info.capsuleRadius = std::stof(params[i].second);
		}
	}
}

void LocoMotor::RigidBody::awake() {
	if (info.boxSize == LMVector3()) {
		info.boxSize = _gameObject->getComponent<Transform>()->getSize();
	}
	if (info.origin == LMVector3()) {
		info.origin = _gameObject->getComponent<Transform>()->getPosition();
	}
	info.sphereSize = 0;
	info.capsuleHeight = 0.0f;
	info.capsuleRadius = 0.0f;
	_body = CreateRigidBody(info);
	_body->setUserPointer(_gameObject);
	//if (_raycast) UseItAsRaycast();
	//if (_beATrigger) BeATrigger();
}

void LocoMotor::RigidBody::start() {}

void LocoMotor::RigidBody::update(float dt) {
	SetPosition(_gameObject->getComponent<Transform>()->getPosition());
	SetRotation(_gameObject->getComponent<Transform>()->getRotation());
}

void LocoMotor::RigidBody::fixedUpdate() {
	_gameObject->getComponent<Transform>()->setPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	_gameObject->getComponent<Transform>()->setRotation(BulletToLm(_body->getWorldTransform().getRotation()));
	//std::cout << "X: " << _body->getWorldTransform().getOrigin().x() << "Y: " << _body->getWorldTransform().getOrigin().y() << "Z: " << _body->getWorldTransform().getOrigin().z() << std::endl;

}

btRigidBody* LocoMotor::RigidBody::CreateRigidBody(RigidBodyInfo info) {
	btCollisionShape* shape = nullptr;
	if (info.capsuleHeight > 0.0)
		shape = new btCapsuleShapeZ(info.capsuleRadius, info.capsuleHeight);
	else if (info.sphereSize <= 0.0)
		shape = new btBoxShape(LmToBullet(info.boxSize));
	else if (info.sphereSize)
		shape = new btSphereShape(info.sphereSize);
	if (shape == nullptr)return nullptr;
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(LmToBullet(info.origin));

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
		rigidbody->setCcdMotionThreshold(0.0001f);//0.0000001f
		rigidbody->setCcdSweptSphereRadius(0.5f);
	}
	return rigidbody;
}

LocoMotor::RigidBodyInfo::RigidBodyInfo() {
	type = 0;
	boxSize = LMVector3();
	sphereSize = 0.f;
	capsuleRadius = 0.f;
	capsuleHeight = 0.f;
	origin = LMVector3();
	mass = 0.f;
}
void LocoMotor::RigidBody::AddForce(LMVector3 force) {
	_body->applyCentralForce(LmToBullet(force));
}
void LocoMotor::RigidBody::SetRotation(LMQuaternion rot) {
	_body->getWorldTransform().setRotation(LmToBullet(rot));
}


void LocoMotor::RigidBody::SetPosition(LMVector3 pos) {
	_body->getWorldTransform().setOrigin(LmToBullet(pos));
}


void LocoMotor::RigidBody::UseGravity(LMVector3 gravity) {

	_body->setGravity(LmToBullet(gravity));
}


void LocoMotor::RigidBody::FreezePosition(LMVector3 freezeAxis) {
	_body->setLinearFactor(LmToBullet(freezeAxis));
}


void LocoMotor::RigidBody::FreezeRotation(LMVector3 freezeAxis) {
	_body->setAngularFactor(LmToBullet(freezeAxis));
}


bool LocoMotor::RigidBody::CheckCollision(GameObject* other) {
	if (other != nullptr) {
		return _body->checkCollideWith(other->getComponent<RigidBody>()->GetBody());
	}
	return false;
}
btRigidBody* LocoMotor::RigidBody::GetBody() {
	return _body;
}

void LocoMotor::RigidBody::BeATrigger() {
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}
void LocoMotor::RigidBody::SetCollisionGroup(int group) {
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;
}


int LocoMotor::RigidBody::GetCollisionGroup() {
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterGroup;
}


void LocoMotor::RigidBody::SetCollisionMask(int mask) {
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterMask = 1 << mask;
}


int LocoMotor::RigidBody::GetCollisionMask() {
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterMask;
}


LMVector3 LocoMotor::RigidBody::GetLinearVelocity() {
	return BulletToLm(_body->getLinearVelocity());
}
void LocoMotor::RigidBody::SetLinearVelocity(LMVector3 newLinearVelocity) {
	_body->setLinearVelocity(LmToBullet(newLinearVelocity));
}


LMVector3 LocoMotor::RigidBody::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}


LMVector3 LocoMotor::RigidBody::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}


LMVector3 LocoMotor::RigidBody::GetAngularVelocity() {
	return BulletToLm(_body->getAngularVelocity());
}


void LocoMotor::RigidBody::SetAngularVelocity(LMVector3 newAngularVelocity) {
	_body->setAngularVelocity(LmToBullet(newAngularVelocity));
}


void LocoMotor::RigidBody::ApplyTorqueImpulse(LMVector3 impulse) {
	_body->applyTorqueImpulse(LmToBullet(impulse));
}

void LocoMotor::RigidBody::ApplyCentralImpulse(LMVector3 impulse) {
	_body->applyCentralImpulse(LmToBullet(impulse));
}


void LocoMotor::RigidBody::SetFriction(float fric) {
	_body->setFriction(fric);
}