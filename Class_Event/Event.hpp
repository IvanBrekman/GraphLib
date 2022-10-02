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
        Type m_type = Type::NO_EVENT;

        struct MouseEvent {
            enum Button_Type {
                NONE    = -1,
                LEFT    =  0,
                RIGHT   =  1,
                MIDDLE  =  2
            };

            Button_Type m_button = Button_Type::NONE;
            Point2D     m_pos    = Point2D(0, 0);
        };

        union {
            MouseEvent mouse;
        };
    
    private:
        Point2D get_mouse_button_pos__(sf::Event event) { return Point2D(event.mouseButton.x, event.mouseButton.y); }
        Point2D get_mouse_move_pos__  (sf::Event event) { return Point2D(event.mouseMove.x,   event.mouseMove.y);   }
};
