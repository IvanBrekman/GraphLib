//
// Created by IvanBrekman on 26.09.2022
//

#include <cstdarg>

#include "WindowView.hpp"

WindowView::WindowView(int size, ...)
: m_size(size), m_hidden(false) {
    va_list  args;
    va_start(args, size);

    for (int i = 0; i < size; i++) {
        this->m_objects.push_back(va_arg(args, Drawable*));
    }

    va_end(args);
}

void WindowView::set_objects_visibility(bool hidden) {
    this->m_hidden = hidden;
    
    for (Drawable* object : this->m_objects) {
        object->set_hidden(hidden);
    }
}
