//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

class Clock {
    public:
        Clock(size_t speed_m = 1)
        : m_speedMultiplier(speed_m) { this->restart(); }

        void restart()               { this->m_sfml_clock.restart(); }

        double get_elapsed_seconds() { return this->m_speedMultiplier * this->m_sfml_clock.getElapsedTime().asSeconds(); }

        // ==================== Getters ====================
        size_t speed_multiplier()    { return m_speedMultiplier; }
        // =================================================

        // ==================== Setters ====================
        Clock& set_speed_multiplier(size_t newSpeed) { m_speedMultiplier = newSpeed; return *this; }
        // =================================================
    
    private:
        size_t    m_speedMultiplier;
        sf::Clock m_sfml_clock;
};
