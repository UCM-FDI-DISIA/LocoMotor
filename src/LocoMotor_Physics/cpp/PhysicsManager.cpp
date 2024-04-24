#include "PhysicsManager.h"
#include "RigidBody.h"
#include "GameObject.h"

#include "assert.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "CallBackBullet.h"
using namespace LocoMotor;
using namespace Physics;
PhysicsManager* PhysicsManager::_instance = nullptr;

bool PhysicsManager::Init() {
	assert(_instance == nullptr);
	_instance = new PhysicsManager();
	return _instance->init();
}

PhysicsManager* PhysicsManager::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void PhysicsManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

void LocoMotor::Physics::PhysicsManager::update(double dt) {

	for (int i = 0; i < _dynamicWorld->getCollisionObjectArray().size(); i++) {
		GameObject* rb = static_cast<GameObject*>(_dynamicWorld->getCollisionObjectArray().at(i)->getUserPointer());
		if (rb != nullptr) {
			RigidBody* body = rb->getComponent<RigidBody>();
			if (body) {
				body->prePhysUpdate();
			}
		}
	}

	_dynamicWorld->stepSimulation(dt / 1000.f, 0);

	for (int i = 0; i < _dynamicWorld->getCollisionObjectArray().size(); i++) {
		GameObject* rb = static_cast<GameObject*>(_dynamicWorld->getCollisionObjectArray().at(i)->getUserPointer());
		if (rb != nullptr) {
			RigidBody* body = rb->getComponent<RigidBody>();
			if (body) {
				body->posPhysUpdate();
			}
		}
	}
}

void LocoMotor::Physics::PhysicsManager::setWorldGravity(btVector3 gravity) {
	_dynamicWorld->setGravity(gravity);
}

btDynamicsWorld* LocoMotor::Physics::PhysicsManager::getDynamicWorld() {
	return _dynamicWorld;
}

void LocoMotor::Physics::PhysicsManager::setContactStartCallback(ContactStartedCallback funtion) {
	//gContactStartedCallback = funtion;
}

void LocoMotor::Physics::PhysicsManager::setContactProcessCallback(ContactProcessedCallback funtion) {
	//gContactProcessedCallback = funtion;
}

void LocoMotor::Physics::PhysicsManager::setContactEndedCallback(ContactEndedCallback funtion) {
	//gContactEndedCallback = funtion;
}


LocoMotor::Physics::PhysicsManager::PhysicsManager() : _dynamicWorld(nullptr), _solver(nullptr), _overlappingPairCache(nullptr), _dispatcher(nullptr), _collisionConfiguration(nullptr) {

}

LocoMotor::Physics::PhysicsManager::~PhysicsManager() {
	delete _dynamicWorld;
	delete _solver;
	delete _overlappingPairCache;
	delete _dispatcher;
	delete _collisionConfiguration;
}

bool LocoMotor::Physics::PhysicsManager::init() {
	//Set default configuration
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_overlappingPairCache = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver;
	//Create Dynamic world
	_dynamicWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
	//Set default gravity
	_dynamicWorld->setGravity(btVector3(0, -9.8f, 0));
	gContactStartedCallback = LMcontactStart;
	gContactProcessedCallback = LMcontactProcessed;
	gContactEndedCallback = LMcontactExit;

	return true;
}
