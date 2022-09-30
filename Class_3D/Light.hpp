//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"

class Light {
    public:
        Point3D pos;
        double  intensity;
    
    public:
        Light(Point3D pos, double intensity)
        : pos(pos), intensity(intensity) {}
};
