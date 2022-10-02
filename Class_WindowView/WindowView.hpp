//
// Created by IvanBrekman on 26.09.2022
//

#pragma once

#include <vector>

#include "../Class_Drawable/Drawable.hpp"

class WindowView {
    public:
        int                     m_size;
        bool                    m_hidden;
        std::vector <Drawable*> m_objects;
    
    public:
        WindowView(int size, ...);

        void set_objects_visibility(bool hidden);
};
