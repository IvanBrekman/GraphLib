//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include "..//Class_Widget/Widget.hpp"
#include "../Class_Event/Event.hpp"
#include "../Class_Text/Text.hpp"

class Figure;

class Button : public Widget {
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
        
        // ==================== Getters ====================
        Button_Type type()  const;

        size_t width()      const;
        size_t height()     const;
        // =================================================
        
        // ==================== Setters ====================
        void set_button_type(Button_Type type);

        void set_button_pressed();
        void set_button_released();
        void set_button_hovered();
        // =================================================

        bool on_click  (const Event& event) override;
        bool on_hover  (const Event& event) override;
        bool on_release(const Event& event) override;
        bool on_unhover(const Event& event) override;

        bool contains(Vec2f pixel, CoordinateSystem system)             override;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()      const                                       override;
    
    private:
        Button_Type             m_type;
        Text                    m_text;
        Figure*                 m_shape;

        const Color             CLICK_COLOR     = Color::Green;
        const Color             HOVER_COLOR     = Color::Yellow;
        const Color             FRAME_COLOR     = Color::Black;
        const int               FRAME_WIDTH     = 5;

        const size_t            EXTRA_WIDTH     = 30;
        const size_t            EXTRA_HEIGHT    = 15;
        const double            EXTRA_TEXT_COEF = 0.5;
};
