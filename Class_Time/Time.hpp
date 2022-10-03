//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

class Clock {
    public:
        int speedMultiplier;

    private:
        sf::Clock m_sfml_clock__;
    
    public:
        Clock(int speed_m = 1)
        : speedMultiplier(speed_m)   { this->restart(); }

        void restart()               { this->m_sfml_clock__.restart(); }

        double get_elapsed_seconds() { return this->speedMultiplier * this->m_sfml_clock__.getElapsedTime().asSeconds(); }
};
