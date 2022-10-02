//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"

class Light {
    public:
        Point3D m_pos;
        double  m_intensity;
    
    public:
        Light(Point3D pos, double intensity)
        : m_pos(pos), m_intensity(intensity) {}
};
