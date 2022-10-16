//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Class_Event/Event.hpp"
#include "../Class_Color/Color.hpp"
#include "../Class_Drawable/Drawable.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

class Button;
class WindowView;

class Window {
    friend class Drawable;

    public:
        Window(int width, int height, const char* text="GraphLib Window", Color color=Color::White);
        ~Window();

        bool is_open() const;
        bool poll_event(Event* event);

        void draw_window_coordinate_system();

        void clear();
        void display();
        void close();

        void append_view (WindowView* view);
        void extend_views(std::vector <WindowView*> views);
        void show_view   (WindowView* view);

        void append_object (Drawable*               object,  int index=CoordinateSystem::LAST_INDEX);
        void extend_objects(std::vector <Drawable*> objects, int index=CoordinateSystem::LAST_INDEX);

        void draw(Drawable* object);
        void draw_added_objects();

        // ==================== Getters ====================
        size_t width ()                         const;
        size_t height()                         const;
        Color  color ()                         const;

        std::vector<Drawable*> objects()        const;

        CoordinateSystem coordinate_system()    const;
        // =================================================

        // ==================== Setters ====================
        Window& set_color                 (Color newColor);
        Window& set_coordinate_system     (CoordinateSystem system);
        Window& set_coordinate_system_type(CoordinateSystem::Type type);
        // =================================================
    
    private:
        size_t m_width;
        size_t m_height;

        Color  m_color;

        sf::Event                   m_sfml_pollEvent;
        sf::RenderWindow            m_sfml_window;

        CoordinateSystem            m_coordinateSystem;
        std::vector<Button    *>    m_buttons;
        std::vector<WindowView*>    m_views;
};
