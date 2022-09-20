//
// Created by IvanBrekman on 16.09.2022
//

#include "Drawable.hpp"

#include "../Class_Window/Window.hpp"

void Drawable::draw_on_window(Window& window) {
    if (this->hidden) return;

    this->draw(window, window.__coordinate_system);
}