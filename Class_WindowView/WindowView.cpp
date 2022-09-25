//
// Created by IvanBrekman on 26.09.2022
//

#include <cstdarg>

#include "WindowView.hpp"

WindowView::WindowView(int size, ...)
: size(size), hidden(false) {
    va_list  args;
    va_start(args, size);

    for (int i = 0; i < size; i++) {
        this->objects.push_back(va_arg(args, Drawable*));
    }

    va_end(args);
}

void WindowView::set_objects_visibility(bool hidden) {
    this->hidden = hidden;
    
    for (Drawable* object : this->objects) {
        if (hidden) object->hide();
        else        object->show();
    }
}
