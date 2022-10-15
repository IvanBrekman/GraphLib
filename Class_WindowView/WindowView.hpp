//
// Created by IvanBrekman on 26.09.2022
//

#pragma once

#include <vector>

#include "../Class_Drawable/Drawable.hpp"

class WindowView {
    public:
         WindowView(std::initializer_list<Drawable*> objects);
        ~WindowView();

        // ==================== Getters ====================
        size_t                  size()    const;
        bool                    hidden()  const;
        std::vector<Drawable*>  objects() const;
        // =================================================

        // ==================== Setters ====================
        WindowView& set_hidden (bool hidden);
        WindowView& set_objects(std::initializer_list<Drawable*> objects);
        // =================================================

    private:
        size_t                 m_size;
        bool                   m_hidden;
        std::vector<Drawable*> m_objects;
};
