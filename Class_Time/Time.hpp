//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

class Clock {
    public:
        int speed_multiplier;

    private:
        sf::Clock __sfml_clock;
    
    public:
        Clock(int speed_m = 1)
        : speed_multiplier(speed_m)  { this->restart(); }

        void restart()               { this->__sfml_clock.restart(); }

        double get_elapsed_seconds() { return this->speed_multiplier * this->__sfml_clock.getElapsedTime().asSeconds(); }
};
