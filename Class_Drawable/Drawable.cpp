//
// Created by IvanBrekman on 16.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Drawable.hpp"

void Drawable::draw_on_window(Window& window) {
    if (this->hidden) return;

    this->draw(window, window.__coordinate_system);
}
