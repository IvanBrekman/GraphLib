//
// Created by IvanBrekman on 18.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

class Event {
    public:
        enum Type {
            NO_EVENT        = 0,

            WINDOW_CLOSED   = 1
        };

        Type type = NO_EVENT;
};
