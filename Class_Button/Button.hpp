//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Figures/Figures.hpp"

class Button : public Drawable {
    public:
        enum Button_Type {
            DEFAULT = 0,
            ELLIPSE = 1,
            CIRCLE  = 2
        };

        Button_Type type;

        Point2D start_point;
        double  width;
        double  height;
    
    private:
        Figure*                 __shape;
        Color                   __shape_color;

        std::vector <Drawable*> __drawing_objects;
    
    public:
        Button(Point2D start_point, double width, double height, Button_Type type=Button_Type::DEFAULT);
        Button(double x, double y,  double width, double height, Button_Type type=Button_Type::DEFAULT)
        : Button(Point2D(x, y), width, height, type) {}

        bool is_pressed(Point2D point);

        void move_to(Point2D shift);

        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();

        void draw(Window& window, const CoordinateSystem& system);
};
