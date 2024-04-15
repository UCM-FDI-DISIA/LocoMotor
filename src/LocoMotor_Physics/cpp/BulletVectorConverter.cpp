#include "BulletVectorConverter.h"
#include "LMVector.h"
#include "btBulletDynamicsCommon.h"

LocoMotor::LMVector3 BulletToLm(const btVector3& bulletVector) {
    return LocoMotor::LMVector3(bulletVector.x(), bulletVector.y(), bulletVector.z());
}

btVector3 LmToBullet(const LocoMotor::LMVector3& lmVector) {
    return btVector3((float) lmVector.GetX(), (float) lmVector.GetY(), (float) lmVector.GetZ());
}
btQuaternion LmToBullet(const LocoMotor::LMQuaternion& LMQuaternion) {
    return btQuaternion((float) LMQuaternion.GetX(), (float) LMQuaternion.GetY(), (float) LMQuaternion.GetZ(), (float) LMQuaternion.GetW());
}

LocoMotor::LMQuaternion BulletToLm(const btQuaternion& bulletQuaternion)
{
    return LocoMotor::LMQuaternion(bulletQuaternion.w(), bulletQuaternion.x(), bulletQuaternion.y(), bulletQuaternion.z());
}
