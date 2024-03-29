
namespace LocoMotor {
	class LMVector3;
	class LMQuaternion;
}
class btVector3;
class btQuaternion;

LocoMotor::LMVector3 BulletToLm(const btVector3& bulletVector);
/// @brief Converts an lmVector to Bullet vector
btVector3 LmToBullet(const LocoMotor::LMVector3& lmVector);
/// @brief Converts an LMQuaternion to Bullet vector
btQuaternion LmToBullet(const LocoMotor::LMQuaternion& LMQuaternion);