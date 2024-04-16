#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"
#include "LMVector.h"
class btRigidBody;
namespace LocoMotor {
	/// @brief Info to create a RigidBody
	/// @param type 1=BoxShape, 2=SphereShape, 3=CapsuleShapeZ
	/// @param btVector3 boxSize The size of the box if is Box
	/// @param float size The size of the sphere if is Sphere
	/// @param capsuleRadius if is capsule
	/// @param capsuleHeight if is capsule
	/// @param btVector3 origin The origin point of transform
	/// @param float mass The mass of rigidbody, if mass !=0 , it is dynamic
	struct RigidBodyInfo {
		int type;
		LMVector3 boxSize;
		float sphereSize;
		float capsuleRadius;
		float capsuleHeight;
		LMVector3 origin;
		float mass;
		RigidBodyInfo();
	};

	class MOTOR_API RigidBody : public Component {
	public:
		RigidBody();
		~RigidBody();
		void setParameters(ComponentMap& params) override;
		void awake() override;
		void start() override;
		void update(float dt)override;
		void fixedUpdate()override;
		/// @brief Add force to the body
		/// @param force to add
		void AddForce(LMVector3 force);
		/// @brief Sets the body rotation
		/// @param rot Rotation to set
		void SetRotation(LMQuaternion rot);
		/// @brief Sets the body rotation
		/// @param rot Rotation to set
		void SetPosition(LMVector3 pos);
		/// @brief Enable/Disable the gravity force affected to this body
		/// @param gravity 
		void UseGravity(LMVector3 gravity);
		/// @brief Freeze the position of the rigidbody , limit the motion of position in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezePosition(LMVector3 freezeAxis);
		/// @brief Freeze the rotation of the rigidbody , limit the motion of rotation in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezeRotation(LMVector3 freezeAxis);
		/// @brief Checks if the rigid body component of a game object collides with another
		/// @param other The parameter "other" is a pointer to a GameObject object, which is being checked for
		/// collision with the current object's RigidBodyComponent.
		/// @return Boolean value. It returns true if the rigid body component of the current game object
		/// collides with the rigid body component of the other game object passed as a parameter, and false
		/// otherwise.
		bool CheckCollision(GameObject* other);
		/// @brief Returns the rigid body component of a locomotor.
		/// @return a pointer to a btRigidBody object, which is the physics body component of the LocoMotor.
		btRigidBody* GetBody();
		/// @brief Convert the body to be a Trigger(No contact Response)
		void BeATrigger();
		/// @brief Methods to return RaycastInfo
		/// @param from The starting point of the raycast in 3D space.
		/// @param to The "to" parameter is a 3D vector representing the end point of the raycast. It is the
		/// point in space where the raycast endsand checks for collisions or intersections with objects in the
		/// scene.
		/// @return A boolean value indicating whether a raycast from the "from" point to the "to" point has hit
		/// any objects in the physics simulation.
		/// /// @brief Set the body to be a group of collision , if not set the group is 0
		/// @param group To set
		void SetCollisionGroup(int group);
		/// @brief Gets the number of rigidbodys group 
		/// @return The number of group
		int GetCollisionGroup();
		/// @brief Set the mask that want to collide , the number is the group you want to collide
		/// @param mask The group number
		void SetCollisionMask(int mask);
		/// @brief Gets actual collision mask
		/// @return the number of collsion mask
		int GetCollisionMask();
		/// @brief Gets the linearvelocity of the body
		/// @return Return a LMVector3 of linear velocity
		LMVector3 GetLinearVelocity();
		/// @brief Sets the linear velocity of the body
		/// @param newAngularVelocity 
		void SetLinearVelocity(LMVector3 newLinearVelocity);
		/// @brief Gets the total torque of the body
		/// @return Return a LMVector3 of total torque
		LMVector3 GetTotalTorque();
		/// @brief Gets the turn velocity of the body
		/// @return Return a LMVector3 of turn velocity
		LMVector3 GetTurnVelocity();
		/// @brief Gets/Sets the angular velocity of the body
		/// @return Return a LMVector3 of turn velocity
		LMVector3 GetAngularVelocity();
		/// @brief Sets the angular velocity of a rigid body component using a given LMVector3 value.
		/// @param newAngularVelocity Variable that represents the new angular velocity to be set for
		/// the rigid body component.
		void SetAngularVelocity(LMVector3 newAngularVelocity);
		/// @brief Applies a torque impulse to the body
		/// @param impulse the impulse to aplly
		void ApplyTorqueImpulse(LMVector3 impulse);
		/// @brief Applies a central impulse to the body
		/// @param impulse the impulse to aplly
		void ApplyCentralImpulse(LMVector3 impulse);
		/// @brief Set the friction of this rigidbody
		/// @param fric the new friction value
		void SetFriction(float fric);
	private:
		btRigidBody* CreateRigidBody(RigidBodyInfo info);
		float _mass;
		btRigidBody* _body;
		float _damping;
		float _angDamping;
		bool _gravity;
		bool _trigger = false;
		int _collisionGroup;
		int _collisionMask;
		bool _raycast = false;
		bool _beATrigger = false;
		RigidBodyInfo info;
	};
}
#endif // !1
