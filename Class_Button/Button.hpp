//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Figures/Figures.hpp"
#include "../Class_Text/Text.hpp"

class Button : public Drawable {
    public:
        enum Button_Type {
            DEFAULT = 0,
            ELLIPSE = 1,
            CIRCLE  = 2
        };

        Button_Type type;

        const char* text;

        bool    centered = false;

        Point2D start_point;
        double  width;
        double  height;
    
    private:
        Text                    __text;
        Figure*                 __shape;
        Color                   __shape_color;

        std::vector <Drawable*> __drawing_objects;
    
    public:
        Button(Point2D start_point, const char* text, int text_size, Button_Type type=Button_Type::DEFAULT);
        Button(double x, double y,  const char* text, int text_size, Button_Type type=Button_Type::DEFAULT)
        : Button(Point2D(x, y), text, text_size, type) {}

        bool is_pressed(Point2D point);

        Point2D center();

        void move_to(Point2D shift);

        void hide() override;

        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();
        void set_button_hovered();

        void draw(Window& window, const CoordinateSystem& system);
};
