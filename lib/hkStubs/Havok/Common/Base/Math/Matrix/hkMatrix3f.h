#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkMatrix3f {
public:
    hkMatrix3f() {}  // NOLINT(modernize-use-equals-default)

    HK_FORCE_INLINE hkFloat32& operator()(int row, int col);
    HK_FORCE_INLINE const hkFloat32& operator()(int row, int col) const;
    template <int Row, int Col>
    HK_FORCE_INLINE hkSimdFloat32 get() const;
    template <int Row, int Col>
    HK_FORCE_INLINE void set(hkSimdFloat32Parameter s);

    HK_FORCE_INLINE hkVector4f& getColumn(int i);
    HK_FORCE_INLINE const hkVector4f& getColumn(int i) const;
    template <int I>
    HK_FORCE_INLINE const hkVector4f& getColumn() const;

    HK_FORCE_INLINE void getRows(hkVector4f& r0, hkVector4f& r1, hkVector4f& r2) const;

    HK_FORCE_INLINE void setZero();
    HK_FORCE_INLINE void setIdentity();

    hkVector4f m_col0;
    hkVector4f m_col1;
    hkVector4f m_col2;
};

inline hkFloat32& hkMatrix3f::operator()(int row, int col) {
    return getColumn(col)(row);
}

inline const hkFloat32& hkMatrix3f::operator()(int row, int col) const {
    return getColumn(col)(row);
}

template <int Row, int Col>
inline hkSimdFloat32 hkMatrix3f::get() const {
    return getColumn<Col>().template getComponent<Row>();
}

template <int Row, int Col>
inline void hkMatrix3f::set(hkSimdFloat32Parameter s) {
    getColumn<Col>().template setComponent<Row>(s);
}

inline hkVector4f& hkMatrix3f::getColumn(int i) {
    return (&m_col0)[i];
}

inline const hkVector4f& hkMatrix3f::getColumn(int i) const {
    return (&m_col0)[i];
}

template <int I>
inline const hkVector4f& hkMatrix3f::getColumn() const {
    return (&m_col0)[I];
}

inline void hkMatrix3f::getRows(hkVector4f& r0, hkVector4f& r1, hkVector4f& r2) const {
    hkVector4f c0;
    c0.set(m_col0(0), m_col1(0), m_col2(0));
    hkVector4f c1;
    c1.set(m_col0(1), m_col1(1), m_col2(1));
    hkVector4f c2;
    c2.set(m_col0(2), m_col1(2), m_col2(2));

    r0 = c0;
    r1 = c1;
    r2 = c2;
}

inline void hkMatrix3f::setZero() {
    m_col0.setZero();
    m_col1.setZero();
    m_col2.setZero();
}

inline void hkMatrix3f::setIdentity() {
    hkMatrix3f* __restrict d = this;
    d->m_col0 = hkVector4f::getConstant<HK_QUADREAL_1000>();
    d->m_col1 = hkVector4f::getConstant<HK_QUADREAL_0100>();
    d->m_col2 = hkVector4f::getConstant<HK_QUADREAL_0010>();
}
