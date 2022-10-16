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
        Figure(Vec2f mainPoint, bool centered);
        Figure()
        : Figure(Vec2f(0, 0), false) {}

        // ==================== Getters ====================
        Color  outline_color() const;
        double outline_width() const;
        // =================================================

        // ==================== Setters ====================
        Figure& set_fill_color(Color fillColor, Color outlineColor, double width=1);
        Figure& set_fill_color(Color color);
        // =================================================

        virtual bool contains(Vec2f point) = 0;
        virtual void draw_impl_(Window& window, const CoordinateSystem& system) = 0;

    protected:
        Color  m_outlineColor;
        double m_outlineWidth;

    protected:
        void set_shape_color_(sf::Shape& shape);
        void draw(Window& window, const CoordinateSystem& system, Vec2f pixel, sf::Shape& shape);
};

class Circle : public Figure {
    public:
        Circle(Vec2f mainPoint,  double radius, bool centered=false);
        Circle(double x, double y, double radius, bool centered=false)
        : Circle(Vec2f(x, y), radius, centered) {}

        // ==================== Getters ====================
        double radius() const;
        // =================================================

        // ==================== Setters ====================
        Circle& set_radius(double newRadius);
        // =================================================

        bool contains(Vec2f point)                                      override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()  const                                           override;
    
    protected:
        double           m_radius;
        sf::CircleShape  m_sfml_shape;
    
    private:
        static const int POINTS_ON_DRAW = 100;
    
};

class Rectangle : public Figure {
    public:
        Rectangle(Vec2f mainPoint,  double width, double height);
        Rectangle(double x, double y, double width, double height)
        : Rectangle(Vec2f(x, y), width, height) {}

        // ==================== Getters ====================
        double width()  const;
        double height() const;
        // =================================================

        // ==================== Setters ====================
        Rectangle& set_width (double newWidth );
        Rectangle& set_height(double newHeight);
        // =================================================

        bool contains(Vec2f point)                                      override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()  const                                            override;
    
    private:
        double m_width;
        double m_height;

        sf::RectangleShape m_sfml_shape;
};

class RegularPolygon : public Circle {
    public:
        RegularPolygon(Vec2f mainPoint,  double radius, double vAmount, bool centered=false);
        RegularPolygon(double x, double y, double radius, double vAmount, bool centered=false)
        : RegularPolygon(Vec2f(x, y), radius, vAmount, centered) {};

        // ==================== Getters ====================
        double vertex_amount() const;
        // =================================================

        // ==================== Setters ====================
        RegularPolygon& set_vertex_amount(double newVertexAmount);
        // =================================================

        bool contains(Vec2f point) override;
    
    private:
        size_t m_vertexAmount;
};

class Polygon : public Figure {
    using Figure::set_centered;

    protected:
        sf::ConvexShape m_sfml_shape;
    
    private:
        std::vector <Vec2f> m_vertexes;
    
    public:
        Polygon(Vec2f* vertexes, int vertexesAmount);
        Polygon(std::vector <Vec2f> vertexes)
        : m_vertexes(vertexes) {}

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
        Ellipse(Vec2f mainPoint,  Vec2f radius,       bool centered=false);
        Ellipse(double x, double y, double rx, double ry, bool centered=false)
        : Ellipse(Vec2f(x, y), Vec2f(rx, ry), centered) {}

        // ==================== Getters ====================
        Vec2f radius() const;
        // =================================================

        // ==================== Setters ====================
        Ellipse& set_radius(Vec2f newRadius);
        // =================================================

        bool contains(Vec2f point)                                      override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        Vec2f center() const                                            override;
        void  move_to_shift_impl_(Vec2f shift)                          override;

    private:
        Vec2f m_radius;
        static const int POINTS_ON_DRAW = 100;
    
    private:
        Vec2f get_point__(int index);
};
