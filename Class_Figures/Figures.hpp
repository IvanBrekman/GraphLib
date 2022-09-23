//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include <vector>

#include "../Class_Point/Point.hpp"
#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Window/Window.hpp"

class Figure : public Drawable {
    using Drawable::set_color;
    
    public:
        Point2D start_point;

        Color  fill_color;
        Color  outline_color;

        double outline_width = 0;
    
    public:
        Figure() : Figure(Point2D(0, 0)) {}
        Figure(Point2D start_point) : start_point(start_point) {};

        virtual Point2D center  () = 0;
        virtual bool    contains(Point2D point) = 0;
        virtual void    move_to (Point2D shift);

        void set_figure_color(Color fill_color, Color outline_color, double width=1);
        void set_figure_color(Color color) { set_figure_color(color, color, 0); }

    protected:
        sf::RenderWindow* _get_sfml_window(Window& window) { return &window.__sfml_window; }

        void _set_shape_color (sf::Shape& shape);
        void draw(Window& window, const CoordinateSystem& system, Point2D pixel, sf::Shape& shape);
};

class Circle : public Figure {
    public:
        double  radius;
        bool    centered = false;
    
    protected:
        sf::CircleShape  _sfml_shape;
    
    private:
        static const int __POINTS_ON_DRAW = 100;
    
    public:
        Circle(Point2D start_point, double radius, bool centered=false);
        Circle(double x, double y,  double radius, bool centered=false)
        : Circle(Point2D(x, y), radius, centered) {}

        Point2D center  ()              override;
        bool    contains(Point2D point) override;

        void move_center_to_start_point() { this->centered = true; }

        void draw(Window& window, const CoordinateSystem& system) override;
};

class Rectangle : public Figure {
    public:
        double width;
        double height;
    
    private:
        sf::RectangleShape __sfml_shape;
    
    public:
        Rectangle(Point2D start_point, double width, double height);
        Rectangle(double x, double y,  double width, double height)
        : Rectangle(Point2D(x, y), width, height) {}

        Point2D center  ()              override;
        bool    contains(Point2D point) override;

        void draw(Window& window, const CoordinateSystem& system) override;
};

class RegularPolygon : public Circle {
    public:
        int vertex_amount;
    
    public:
        RegularPolygon(Point2D start_point, double radius, double v_amount, bool centered=false);
        RegularPolygon(double x, double y,  double radius, double v_amount, bool centered=false)
        : RegularPolygon(Point2D(x, y), radius, v_amount, centered) {};

        bool contains(Point2D point) override;
};

// TODO написать приватный метод в Point2D.__sfml_vector2f(), изза чего будет много friend;
class Polygon : public Figure {
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

        Point2D center  ()              override;
        bool    contains(Point2D point) override;
        void    move_to (Point2D shift) override;

        void draw(Window& window, const CoordinateSystem& system) override;
    
    protected:
        Polygon(Point2D start_point) : Figure(start_point) {}
};

class Ellipse : public Polygon {
    using Polygon::get_vertexes;
    using Polygon::get_vertex;

    public:
        Point2D radius;
        bool    centered;
    
    private:
        static const int __POINTS_ON_DRAW = 100;
     
    public:
        Ellipse(Point2D start_point, Point2D radius,       bool centered=false);
        Ellipse(double x, double y,  double rx, double ry, bool centered=false)
        : Ellipse(Point2D(x, y), Point2D(rx, ry), centered) {}

        Point2D center  ()              override;
        bool    contains(Point2D point) override;
        void    move_to (Point2D shift) override;
        
        void move_center_to_start_point() { this->centered = true; }

        void draw(Window& window, const CoordinateSystem& system);

    private:
        Point2D __get_point(int index);
};
