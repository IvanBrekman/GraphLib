//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Text/Text.hpp"

class Figure;

class Button : public Drawable, public Moveable {
    public:
        enum Button_Type {
            DEFAULT = 0,
            ELLIPSE = 1,
            CIRCLE  = 2
        };

        Button_Type type;
        bool        centered = false;
    
    private:
        Text                    __text;
        Figure*                 __shape;
        Color                   __shape_color;

        const double            __EXTRA_WIDTH       = 30;
        const double            __EXTRA_HEIGHT      = 15;
        const double            __EXTRA_TEXT_COEF   = 0.3;
    
    public:
        Button(Point2D main_point, const char* text, int text_size, Button_Type type=Button_Type::DEFAULT);
        Button(double x, double y, const char* text, int text_size, Button_Type type=Button_Type::DEFAULT)
        : Button(Point2D(x, y), text, text_size, type) {}

        double width();
        double height();

        bool is_pressed(Point2D point);

        Point2D center();
        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();
        void set_button_hovered();

        void draw(Window& window, const CoordinateSystem& system) override;
};
