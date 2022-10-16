//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"

class Light {
    public:
        Light(Vec3f pos, double intensity)
        : m_pos(pos), m_intensity(intensity) {}

        // ==================== Getters ====================
        Vec3f  pos()       const { return m_pos; }
        double intensity() const { return m_intensity; }
        // =================================================

        // ==================== Setters ====================
        Light& set_pos      (Vec3f  newPos)       { m_pos       = newPos;       return *this; }
        Light& set_intensity(double newIntensity) { m_intensity = newIntensity; return *this; }
        // =================================================
    
    private:
        Vec3f   m_pos;
        double  m_intensity;
};
