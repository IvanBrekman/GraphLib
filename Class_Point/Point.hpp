//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Class_Utils/baselib.hpp"

// TODO how use inheritance for methods?
template<typename T, size_t DIM>
class VecN {
    private:
        T m_coords[DIM];
    
    public:
        VecN() { for (size_t i = 0; i < DIM; i++) m_coords[i] = T(); }
        VecN(const std::initializer_list<T>& initData) {
            size_t index = 0;
            for (const T& coord : initData) {
                m_coords[index++] = coord;
            }
        }

              T& operator [](size_t index)       { ASSERT_IF(index < DIM, "Index greater than DIM size", T()); return m_coords[index]; }
        const T& operator [](size_t index) const { return const_cast<const T&> (const_cast<VecN*> (this)->operator[](index)); }

        double length_squared() const { return lengthSquaredVecN(*this); }
        double length()         const { return lengthVecN(*this); }

        VecN   normalize()      const { return normalizeVecN(*this); }
        void   dump()           const { return dumpVecN(*this); }
};

typedef VecN<float, 2> Vec2f;
typedef VecN<float, 3> Vec3f;

template<typename T>
class VecN<T, 2> {
    public:
        T x;
        T y;
    
    public:
        VecN<T, 2>(T x, T y)
        : x(x), y(y) {}

        VecN<T, 2>()
        : VecN<T, 2>(T(), T()) {}
        
              T& operator [](size_t index)       { ASSERT_IF(index < 2, "Index greater than DIM size (2)", x); return index == 0 ? x : y; }
        const T& operator [](size_t index) const { return const_cast<const T&> (const_cast<VecN*> (this)->operator[](index)); }

        sf::Vector2f to_sfml_vector() const { return sf::Vector2<T>(x, y); }

        double length_squared() const { return lengthSquaredVecN(*this); }
        double length()         const { return lengthVecN(*this); }

        VecN   normalize()      const { return normalizeVecN(*this); }
        void   dump()           const { return dumpVecN(*this); }
};

template<typename T>
class VecN<T, 3> {
    public:
        T x;
        T y;
        T z;
    
    public:
        VecN<T, 3>(T x, T y, T z)
        : x(x), y(y), z(z) {}

        VecN<T, 3>()
        : VecN<T, 3>(T(), T(), T()) {}

              T& operator [](size_t index)       { ASSERT_IF(index < 3, "Index greater than DIM size (3)", x); return index == 0 ? x : (index == 1 ? y : z); }
        const T& operator [](size_t index) const { return const_cast<const T&> (const_cast<VecN*> (this)->operator[](index)); }

        double length_squared() const { return lengthSquaredVecN(*this); }
        double length()         const { return lengthVecN(*this); }

        VecN   normalize()      const { return normalizeVecN(*this); }
        void   dump()           const { return dumpVecN(*this); }
};

template<typename T, size_t DIM> VecN<T, DIM> operator +=(VecN<T, DIM>& lhs, const VecN<T, DIM>& rhs) {
    for (size_t i = 0; i < DIM; i++) lhs[i] += rhs[i];

    return lhs;
}

template<typename T, size_t DIM> VecN<T, DIM> operator -=(VecN<T, DIM>& lhs, const VecN<T, DIM>& rhs) {
    return lhs += -rhs;
}

template<typename T, size_t DIM> VecN<T, DIM> operator *=(VecN<T, DIM>& lhs, const double scalar) {
    for (size_t i = 0; i < DIM; i++) lhs[i] *= scalar;

    return lhs;
}

template<typename T, size_t DIM> VecN<T, DIM> operator /=(VecN<T, DIM>& lhs, const double scalar) {
    return lhs * (1 / scalar);
}

template<typename T, size_t DIM> VecN<T, DIM> operator +(const VecN<T, DIM>& lhs, const VecN<T, DIM>& rhs) {
    VecN<T, DIM> tmp(lhs);
    return tmp += rhs;
}

template<typename T, size_t DIM> VecN<T, DIM> operator -(const VecN<T, DIM>& lhs, const VecN<T, DIM>& rhs) {
    return lhs + -rhs;
}

template<typename T, size_t DIM> VecN<T, DIM> operator *(const VecN<T, DIM>& lhs, const double scalar) {
    VecN<T, DIM> tmp(lhs);
    return tmp *= scalar;
}

template<typename T, size_t DIM> VecN<T, DIM> operator /(const VecN<T, DIM>& lhs, const double scalar) {
    return lhs * (1 / scalar);
}

template<typename T, size_t DIM> VecN<T, DIM> operator -(const VecN<T, DIM>& vec) {
    VecN<T, DIM> tmp(vec);
    for (size_t i = 0; i < DIM; i++) tmp[i] *= -1;

    return tmp;
}

template<typename T, size_t DIM> double scalarProduct(const VecN<T, DIM>& vec1, const VecN<T, DIM>& vec2) {
    double res = 0;

    for (size_t i = 0; i < DIM; i++) res += vec1[i] * vec2[i];

    return res;
}

template<typename T, size_t DIM> double lengthSquaredVecN(const VecN<T, DIM>& vec) {
    double res = 0;

    for (size_t i = 0; i < DIM; i++) res += vec[i] * vec[i];

    return res;
}

template<typename T, size_t DIM> double lengthVecN(const VecN<T, DIM>& vec) {
    return sqrt(lengthSquaredVecN(vec));
}

template<typename T, size_t DIM> VecN<T, DIM> normalizeVecN(const VecN<T, DIM>& vec) {
    return vec / lengthVecN(vec);
}

template<typename T, size_t DIM> void dumpVecN(const VecN<T, DIM>& vec) {
    printf("<Vec%zd%s: (", DIM, typeid(T).name());

    for (size_t i = 0; i < DIM; i++) {
        std::cout << vec[i];
        if ((i + 1) < DIM) printf(", ");
    }

    printf(") >\n");
}
