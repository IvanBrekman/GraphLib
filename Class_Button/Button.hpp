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
    
    public:
        Button(Vec2f mainPoint,  const char* text, int textSize, Button_Type type=Button_Type::DEFAULT);
        Button(double x, double y, const char* text, int textSize, Button_Type type=Button_Type::DEFAULT)
        : Button(Vec2f(x, y), text, textSize, type) {}
        
        bool is_pressed(Vec2f point, Event::MouseEvent::Button_Type button);

        // ==================== Getters ====================
        Button_Type type()  const;

        double width()      const;
        double height()     const;
        // =================================================
        
        // ==================== Setters ====================
        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();
        void set_button_hovered();
        // =================================================

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()      const                                       override;
    
    private:
        Button_Type             m_type;
        Text                    m_text;
        Figure*                 m_shape;
        Color                   m_shapeColor;

        const double            EXTRA_WIDTH     = 30;
        const double            EXTRA_HEIGHT    = 15;
        const double            EXTRA_TEXT_COEF = 0.3;
};
