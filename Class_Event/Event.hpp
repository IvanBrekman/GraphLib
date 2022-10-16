//
// Created by IvanBrekman on 18.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Point/Point.hpp"

class Window;

class Event {
    friend class Window;

    public:
        Event() {}

        enum Type {
            NO_EVENT                = 0,

            WINDOW_CLOSED           = 1,
            MOUSE_BUTTON_PRESSED    = 2,
            MOUSE_BUTTON_RELEASED   = 3,
            MOUSE_MOVED             = 4,
        };
        Type type = Type::NO_EVENT;

        struct MouseEvent {
            enum Button_Type {
                NONE    = -1,
                LEFT    =  0,
                RIGHT   =  1,
                MIDDLE  =  2
            };

            Button_Type button = Button_Type::NONE;
            Vec2f       pos    = Vec2f(0, 0);
        };

        union {
            MouseEvent mouse;
        };
    
    private:
        Vec2f get_mouse_button_pos__(sf::Event event) { return Vec2f(event.mouseButton.x, event.mouseButton.y); }
        Vec2f get_mouse_move_pos__  (sf::Event event) { return Vec2f(event.mouseMove.x,   event.mouseMove.y);   }
};
