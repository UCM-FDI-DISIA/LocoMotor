
namespace LocoMotor {
	class LMVector3;
}
class btVector3;

LocoMotor::LMVector3 BulletToLm(const btVector3& bulletVector);
/// @brief Converts an lmVector to Bullet vector
btVector3 LmToBullet(const LocoMotor::LMVector3& lmVector);