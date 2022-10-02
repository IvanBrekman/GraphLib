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
    friend class Line;
    friend class Figure;
    friend class PixelMap;
    friend class Text;

    public:
        int width;
        int height;

        Color color;

    private:
        sf::Event                   __sfml_poll_event;
        sf::RenderWindow            __sfml_window;

        CoordinateSystem            __coordinate_system;
        std::vector <Button*>       __buttons;
        std::vector <WindowView*>   __views;

    public:
        Window(int width, int height, const char* text="GraphLib Window", Color color=Color::White);
        ~Window();

        bool is_open() const;
        bool poll_event(Event* event);

        std::vector <Drawable*>* objects();

        CoordinateSystem* get_system();

        void set_coordinate_system     (CoordinateSystem system);
        void set_coordinate_system_type(CoordinateSystem::Type type);
        void draw_window_coordinate_system();

        void clear();
        void display();
        void close();

        void append_view (WindowView* view);
        void extend_views(std::vector <WindowView*> views);
        void show_view(WindowView* view);

        void append_object (Drawable*               object,  int index=CoordinateSystem::LAST_INDEX__);
        void extend_objects(std::vector <Drawable*> objects, int index=CoordinateSystem::LAST_INDEX__);

        void draw(Drawable* object);
        void draw_added_objects();
};
