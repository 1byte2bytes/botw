#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>

namespace ksys::phys {

inline void toVec3(sead::Vector3f* out, const hkVector4f& vec) {
    out->x = vec.getX();
    out->y = vec.getY();
    out->z = vec.getZ();
}

[[nodiscard]] inline sead::Vector3f toVec3(const hkVector4f& vec) {
    return {vec.getX(), vec.getY(), vec.getZ()};
}

inline void toHkVec4(hkVector4f* out, const sead::Vector3f& vec) {
    out->set(vec.x, vec.y, vec.z);
}

[[nodiscard]] inline hkVector4f toHkVec4(const sead::Vector3f& vec) {
    return {vec.x, vec.y, vec.z};
}

inline void storeToVec3(sead::Vector3f* out, const hkVector4f& vec) {
    vec.store<3>(out->e.data());
}

inline void loadFromVec3(hkVector4f* out, const sead::Vector3f& vec) {
    out->load<3>(vec.e.data());
    out->setW(0);
}

inline void toQuat(sead::Quatf* out, const hkQuaternionf& quat) {
    out->set(quat.m_vec.getW(), quat.m_vec.getX(), quat.m_vec.getY(), quat.m_vec.getZ());
}

[[nodiscard]] inline sead::Quatf toQuat(const hkQuaternionf& quat) {
    return {quat.m_vec.getW(), quat.m_vec.getX(), quat.m_vec.getY(), quat.m_vec.getZ()};
}

inline void toHkQuat(hkQuaternionf* out, const sead::Quatf& quat) {
    out->set(quat.x, quat.y, quat.z, quat.w);
}

[[nodiscard]] inline hkQuaternionf toHkQuat(const sead::Quatf& quat) {
    return {quat.x, quat.y, quat.z, quat.w};
}

inline void toMtx34(sead::Matrix34f* out, const hkTransformf& transform) {
    const hkRotationf& rotate = transform.getRotation();
    const hkVector4f& translate = transform.getTranslation();

    hkVector4f mtx[3];
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 3; ++i) {
            mtx[i][j] = rotate(i, j);
        }
    }
    for (int i = 0; i < 3; ++i)
        mtx[i][3] = translate(i);

    mtx[0].store<4>(out->m[0]);
    mtx[1].store<4>(out->m[1]);
    mtx[2].store<4>(out->m[2]);
}

inline void toHkTransform(hkTransformf* out, const sead::Matrix34f& mtx) {
    sead::Quatf rotate;
    mtx.toQuat(rotate);
    rotate.normalize();

    sead::Vector3f translate;
    mtx.getTranslation(translate);

    out->set(toHkQuat(rotate), toHkVec4(translate));
}

// Consider using toMtx34 if you have an hkTransform and wish to set both rotation and translation.
inline void setMtxRotation(sead::Matrix34f* mtx, const hkRotationf& rotation) {
    mtx->setBase(0, toVec3(rotation.getColumn(0)));
    mtx->setBase(1, toVec3(rotation.getColumn(1)));
    mtx->setBase(2, toVec3(rotation.getColumn(2)));
}

// Consider using toMtx34 if you have an hkTransform and wish to set both rotation and translation.
inline void setMtxTranslation(sead::Matrix34f* mtx, const hkVector4f& translation) {
    mtx->setTranslation(toVec3(translation));
}

}  // namespace ksys::phys
