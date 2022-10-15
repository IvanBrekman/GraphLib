//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include <vector>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Point/Point.hpp"

class Figure : public Drawable, public Moveable {
    public:
        Color  m_outlineColor;
        double m_outlineWidth;
    
    public:
        Figure(Vec2f mainPoint, bool centered);
        Figure()
        : Figure(Vec2f(0, 0), false) {}

        Figure& set_fill_color(Color fillColor, Color outlineColor, double width=1);
        Figure& set_fill_color(Color color);

        virtual bool contains(Vec2f point) = 0;
        virtual void draw_impl_(Window& window, const CoordinateSystem& system) = 0;

    protected:
        void set_shape_color_(sf::Shape& shape);
        void draw(Window& window, const CoordinateSystem& system, Vec2f pixel, sf::Shape& shape);
};

class Circle : public Figure {
    public:
        double m_radius;
    
    protected:
        sf::CircleShape  m_sfml_shape_;
    
    private:
        static const int POINTS_ON_DRAW__ = 100;
    
    public:
        Circle(Vec2f mainPoint,  double radius, bool centered=false);
        Circle(double x, double y, double radius, bool centered=false)
        : Circle(Vec2f(x, y), radius, centered) {}

        bool contains(Vec2f point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center() const                                          override;
};

class Rectangle : public Figure {
    public:
        double m_width;
        double m_height;
    
    private:
        sf::RectangleShape m_sfml_shape__;
    
    public:
        Rectangle(Vec2f mainPoint,  double width, double height);
        Rectangle(double x, double y, double width, double height)
        : Rectangle(Vec2f(x, y), width, height) {}

        bool contains(Vec2f point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center() const                                          override;
};

class RegularPolygon : public Circle {
    public:
        int vertexAmount;
    
    public:
        RegularPolygon(Vec2f mainPoint,  double radius, double vAmount, bool centered=false);
        RegularPolygon(double x, double y, double radius, double vAmount, bool centered=false)
        : RegularPolygon(Vec2f(x, y), radius, vAmount, centered) {};

        bool contains(Vec2f point) override;
};

class Polygon : public Figure {
    using Figure::set_centered;

    protected:
        sf::ConvexShape m_sfml_shape_;
    
    private:
        std::vector <Vec2f> m_vertexes__;
    
    public:
        Polygon(Vec2f* vertexes, int vertexesAmount);
        Polygon(std::vector <Vec2f> vertexes)
        : m_vertexes__(vertexes) {}

        std::vector <Vec2f>* get_vertexes();
        Vec2f                get_vertex  (int index);

        bool contains(Vec2f point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        Vec2f center() const                                          override;
        void move_to_shift_impl_(Vec2f shift)                         override;
    
    protected:
        Polygon(Vec2f mainPoint, bool centered) : Figure(mainPoint, centered) {}
};

class Ellipse : public Polygon {
    using Polygon::get_vertexes;
    using Polygon::get_vertex;

    public:
        Vec2f m_radius;
    
    private:
        static const int POINTS_ON_DRAW__ = 100;
     
    public:
        Ellipse(Vec2f mainPoint,  Vec2f radius,       bool centered=false);
        Ellipse(double x, double y, double rx, double ry, bool centered=false)
        : Ellipse(Vec2f(x, y), Vec2f(rx, ry), centered) {}

        bool contains(Vec2f point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        Vec2f center() const                                          override;
        void move_to_shift_impl_(Vec2f shift)                         override;

    private:
        Vec2f get_point__(int index);
};
