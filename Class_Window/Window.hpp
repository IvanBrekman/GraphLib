//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Class_Color/Color.hpp"
#include "../Class_Manager/EventManager.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "../Class_Figures/Figures.hpp"

class WindowView;

class Window : public Widget {
    public:
        Window(Vec2f mainPoint,    size_t width, size_t height, Window* parent=nullptr);
        Window(double x, double y, size_t width, size_t height, Window* parent=nullptr)
        : Window(Vec2f(x, y), width, height, parent) {}

        void append_view (WindowView* view);
        void extend_views(std::vector <WindowView*> views);
        void show_view   (WindowView* view);

        void append_object (Widget*               object,  int index=CoordinateSystem::LAST_INDEX);
        void extend_objects(std::vector <Widget*> objects, int index=CoordinateSystem::LAST_INDEX);

        // ==================== Getters ====================
        Vec2f                left_up_pixel()    const;
        std::vector<Widget*> objects()          const;
        CoordinateSystem     system()           const;
        // =================================================

        // ==================== Setters ====================
        Window& set_coordinate_system     (CoordinateSystem system);
        Window& set_coordinate_system_type(CoordinateSystem::Type type);
        Window& set_parent                (Window* parent);
        // =================================================

        virtual bool on_event(const Event& event, Eventable::Type type)     override;

        Vec2f center()                          const                       override;
        void draw_impl_(MainWindow& window, const CoordinateSystem& system) override;
    
    protected:
        EventManager                m_childrenManager;
        std::vector<WindowView*>    m_views;
};

class MainWindow : public Window {
    friend class Drawable;

    public:
         MainWindow(size_t width, size_t height, const char* text="GraphLib MainWindow", Color color=Color::White);
        ~MainWindow();

        bool is_open() const;
        bool poll_event();

        void draw_window_coordinate_system();

        void clear();
        void display();
        void close();

        void draw(Widget* object);
        void draw_added_objects();
    
    private:
        sf::Event                   m_sfml_pollEvent;
        sf::RenderWindow            m_sfml_window;

        EventManager                m_mainManager;
};
