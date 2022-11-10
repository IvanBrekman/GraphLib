//
// Created by IvanBrekman on 26.09.2022
//

#pragma once

#include <vector>

#include "../Class_Widget/Widget.hpp"

class WindowView {
    public:
        WindowView(std::initializer_list<Widget*> objects);
        WindowView()
        : WindowView({}) {}

        ~WindowView();

        // ==================== Getters ====================
        size_t                  size()    const;
        bool                    hidden()  const;
        std::vector<Widget*>    objects() const;
        // =================================================

        // ==================== Setters ====================
        WindowView& set_hidden (bool hidden);
        WindowView& set_objects(std::initializer_list<Widget*> objects);
        // =================================================

    private:
        size_t                 m_size;
        bool                   m_hidden;
        std::vector<Widget*>   m_objects;
};
