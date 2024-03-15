#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H
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

	class RigidBody : public Component {
	public:
		RigidBody();
		~RigidBody();
		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void awake() override;
		void start() override;
		void update(float dt)override;
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
	};
}
#endif // !1
