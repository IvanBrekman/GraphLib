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
        Color  outline_color;
        double outline_width = 0;

        bool   centered      = false;
    
    public:
        Figure()
        : Figure(Point2D(0, 0), false) {}

        Figure(Point2D main_point, bool centered)
        : Moveable(main_point), centered(centered) {}

        void set_fill_color(Color fill_color, Color outline_color, double width=1);
        void set_fill_color(Color color) { this->set_fill_color(color, color, 0); }

        virtual Point2D center      ()              = 0;
        virtual void    set_centered();
        virtual bool    contains    (Point2D point) = 0;

    protected:
        sf::RenderWindow* _get_sfml_window(Window& window);

        void _set_shape_color(sf::Shape& shape);
        void _draw(Window& window, const CoordinateSystem& system, Point2D pixel, sf::Shape& shape);
};

class Circle : public Figure {
    public:
        double  radius;
    
    protected:
        sf::CircleShape  _sfml_shape;
    
    private:
        static const int __POINTS_ON_DRAW = 100;
    
    public:
        Circle(Point2D main_point, double radius, bool centered=false);
        Circle(double x, double y, double radius, bool centered=false)
        : Circle(Point2D(x, y), radius, centered) {}

        Point2D center  ()                                              override;
        bool    contains(Point2D point)                                 override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
};

class Rectangle : public Figure {
    public:
        double width;
        double height;
    
    private:
        sf::RectangleShape __sfml_shape;
    
    public:
        Rectangle(Point2D main_point, double width, double height);
        Rectangle(double x, double y, double width, double height)
        : Rectangle(Point2D(x, y), width, height) {}

        Point2D center  ()                                              override;
        bool    contains(Point2D point)                                 override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
};

class RegularPolygon : public Circle {
    public:
        int vertex_amount;
    
    public:
        RegularPolygon(Point2D main_point, double radius, double v_amount, bool centered=false);
        RegularPolygon(double x, double y, double radius, double v_amount, bool centered=false)
        : RegularPolygon(Point2D(x, y), radius, v_amount, centered) {};

        bool contains(Point2D point) override;
};

// TODO написать приватный метод в Point2D.__sfml_vector2f(), изза чего будет много friend;
class Polygon : public Figure {
    using Figure::set_centered;

    protected:
        sf::ConvexShape _sfml_shape;
    
    private:
        std::vector <Point2D> __vertexes;
    
    public:
        Polygon(Point2D* vertexes, int vertexes_amount);
        Polygon(std::vector <Point2D> vertexes)
        : __vertexes(vertexes) {}

        std::vector <Point2D>* get_vertexes();
        Point2D                get_vertex  (int index);

        Point2D center  ()                                              override;
        bool    contains(Point2D point)                                 override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        void move_to_shift(Point2D shift)                               override;
    
    protected:
        Polygon(Point2D main_point, bool centered) : Figure(main_point, centered) {}
};

class Ellipse : public Polygon {
    using Polygon::get_vertexes;
    using Polygon::get_vertex;

    public:
        Point2D radius;
    
    private:
        static const int __POINTS_ON_DRAW = 100;
     
    public:
        Ellipse(Point2D main_point, Point2D radius,       bool centered=false);
        Ellipse(double x, double y, double rx, double ry, bool centered=false)
        : Ellipse(Point2D(x, y), Point2D(rx, ry), centered) {}

        Point2D center  ()                                              override;
        bool    contains(Point2D point)                                 override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        void move_to_shift(Point2D shift)                               override;

    private:
        Point2D __get_point(int index);
};
