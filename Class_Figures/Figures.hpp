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
        Figure(Point2D mainPoint, bool centered);
        Figure()
        : Figure(Point2D(0, 0), false) {}

        void set_fill_color(Color fillColor, Color outlineColor, double width=1);
        void set_fill_color(Color color);

        virtual bool contains(Point2D point) = 0;
        virtual void draw_impl_(Window& window, const CoordinateSystem& system) = 0;

    protected:

        void set_shape_color_(sf::Shape& shape);
        void draw(Window& window, const CoordinateSystem& system, Point2D pixel, sf::Shape& shape);
};

class Circle : public Figure {
    public:
        double m_radius;
    
    protected:
        sf::CircleShape  m_sfml_shape_;
    
    private:
        static const int POINTS_ON_DRAW__ = 100;
    
    public:
        Circle(Point2D mainPoint,  double radius, bool centered=false);
        Circle(double x, double y, double radius, bool centered=false)
        : Circle(Point2D(x, y), radius, centered) {}

        bool contains(Point2D point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Point2D center() const                                          override;
};

class Rectangle : public Figure {
    public:
        double m_width;
        double m_height;
    
    private:
        sf::RectangleShape m_sfml_shape__;
    
    public:
        Rectangle(Point2D mainPoint,  double width, double height);
        Rectangle(double x, double y, double width, double height)
        : Rectangle(Point2D(x, y), width, height) {}

        bool contains(Point2D point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Point2D center() const                                          override;
};

class RegularPolygon : public Circle {
    public:
        int vertexAmount;
    
    public:
        RegularPolygon(Point2D mainPoint,  double radius, double vAmount, bool centered=false);
        RegularPolygon(double x, double y, double radius, double vAmount, bool centered=false)
        : RegularPolygon(Point2D(x, y), radius, vAmount, centered) {};

        bool contains(Point2D point) override;
};

// TODO написать приватный метод в Point2D.__sfml_vector2f(), изза чего будет много friend;
class Polygon : public Figure {
    using Figure::set_centered;

    protected:
        sf::ConvexShape m_sfml_shape_;
    
    private:
        std::vector <Point2D> m_vertexes__;
    
    public:
        Polygon(Point2D* vertexes, int vertexesAmount);
        Polygon(std::vector <Point2D> vertexes)
        : m_vertexes__(vertexes) {}

        std::vector <Point2D>* get_vertexes();
        Point2D                get_vertex  (int index);

        bool contains(Point2D point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        Point2D center() const                                          override;
        void move_to_shift_impl_(Point2D shift)                         override;
    
    protected:
        Polygon(Point2D mainPoint, bool centered) : Figure(mainPoint, centered) {}
};

class Ellipse : public Polygon {
    using Polygon::get_vertexes;
    using Polygon::get_vertex;

    public:
        Point2D m_radius;
    
    private:
        static const int POINTS_ON_DRAW__ = 100;
     
    public:
        Ellipse(Point2D mainPoint,  Point2D radius,       bool centered=false);
        Ellipse(double x, double y, double rx, double ry, bool centered=false)
        : Ellipse(Point2D(x, y), Point2D(rx, ry), centered) {}

        bool contains(Point2D point)                                    override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        Point2D center() const                                          override;
        void move_to_shift_impl_(Point2D shift)                         override;

    private:
        Point2D get_point__(int index);
};
