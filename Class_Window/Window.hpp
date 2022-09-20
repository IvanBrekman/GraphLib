//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Class_Color/Color.hpp"
#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Event/Event.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

class Window {
    friend class Line;
    friend class Drawable;

    public:
        enum Coordinate_System_Type {
            CENTER      = 0,
            LEFT_UP     = 1,
            LEFT_BOTTOM = 2
        };
        
        int width;
        int height;

        Color color;

        std::vector <Drawable*> objects;

    private:
        sf::Event           __poll_event;
        sf::RenderWindow    __sfml_window;
        CoordinateSystem    __coordinate_system;

        static const int    __LAST_INDEX = -1;

    public:
        Window(int width, int height, const char* text="GraphLib Window", Color color=Color::White);
        ~Window();

        bool is_open() const;
        bool poll_event(Event* event);

        void set_coordinate_system     (CoordinateSystem system);
        void set_coordinate_system_type(Coordinate_System_Type type);
        void draw_window_coordinate_system();

        void clear();
        void display();
        void close();

        void append_object (Drawable*               object,  int index=Window::__LAST_INDEX);
        void extend_objects(std::vector <Drawable*> objects, int index=Window::__LAST_INDEX);

        void draw(Drawable* object);
        void draw_added_objects();
};
