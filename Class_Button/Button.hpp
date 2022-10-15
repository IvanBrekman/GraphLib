//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Event/Event.hpp"
#include "../Class_Text/Text.hpp"

class Figure;

class Button : public Drawable, public Moveable {
    public:
        enum Button_Type {
            DEFAULT = 0,
            ELLIPSE = 1,
            CIRCLE  = 2
        };

        Button_Type m_type;
    
    private:
        Text                    m_text__;
        Figure*                 m_shape__;
        Color                   m_shapeColor__;

        const double            EXTRA_WIDTH__     = 30;
        const double            EXTRA_HEIGHT__    = 15;
        const double            EXTRA_TEXT_COEF__ = 0.3;
    
    public:
        Button(Vec2f mainPoint,  const char* text, int textSize, Button_Type type=Button_Type::DEFAULT);
        Button(double x, double y, const char* text, int textSize, Button_Type type=Button_Type::DEFAULT)
        : Button(Vec2f(x, y), text, textSize, type) {}

        double width()  const;
        double height() const;

        bool is_pressed(Vec2f point, Event::MouseEvent::Button_Type button);

        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();
        void set_button_hovered();

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center() const                                          override;
};
