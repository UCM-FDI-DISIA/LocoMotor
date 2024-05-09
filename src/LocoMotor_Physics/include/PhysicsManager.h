#pragma once
#ifndef _PHYSICS_MANAGER_H
#define _PHYSICS_MANAGER_H
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <unordered_map>
#include <string>
class btVector3;
class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;

class btPersistentManifold;
class btManifoldPoint;

typedef void(*ContactStartedCallback)(btPersistentManifold* const&);
typedef bool(*ContactProcessedCallback)(btManifoldPoint&, void*, void*);
typedef void(*ContactEndedCallback)(btPersistentManifold* const&);
namespace LocoMotor{
	namespace Physics{

		class PhysicsManager {
		public:
			static bool Init();
			MOTOR_API static PhysicsManager* GetInstance();
			static void Release();
			/// @brief Update the physics world , steps the physic simulation
			void update(double dt);
			/// @brief Sets the worlds gravity
			/// @param gravity The Vector3 gravity you want to set
			MOTOR_API void setWorldGravity(btVector3 gravity);
			/// @brief Gets dynamic World
			btDynamicsWorld* getDynamicWorld();
			/// @brief Sets the callback when two body starts contact
			void setContactStartCallback(ContactStartedCallback funtion);
			/// @brief Sets the callback when two body is in contact
			void setContactProcessCallback(ContactProcessedCallback funtion);
			/// @brief Sets the callback when two body ends contact
			void setContactEndedCallback(ContactEndedCallback funtion);
			/// @brief Gets the number of a layer in Bullet by name
			/// @param layer Name of the layer
			int getlayerNumber(std::string layer);
		private:
			static PhysicsManager* _instance;
			btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
			btCollisionDispatcher* _dispatcher = nullptr;
			btBroadphaseInterface* _overlappingPairCache = nullptr;
			btSequentialImpulseConstraintSolver* _solver = nullptr;
			btDynamicsWorld* _dynamicWorld = nullptr;
			int _layerCount;
			std::unordered_map<std::string, int> _layers;
			PhysicsManager();
			~PhysicsManager();
			bool init();

		};
	}
}
#endif // !1
