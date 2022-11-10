//
// Created by IvanBrekman on 03.11.2022
//

#pragma once

#include <cinttypes>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Eventable/Eventable.hpp"

#include "../Class_Point/Point.hpp"

class Widget : public Drawable,
               public Moveable,
               public Eventable {
    public:
        enum Status {
            CLICKED = 0,
            HOVERED = 1,

            STATUS_NUM,
        };

    public:
        Widget(Vec2f mainPoint,    double width, double height);
        Widget(double x, double y, double width, double height)
        : Widget(Vec2f(x, y), width, height) {}

        ~Widget();

        // ==================== Getters ====================
        size_t width ()   const;
        size_t height()   const;

        bool is_clicked() const;
        bool is_hovered() const;
        // =================================================

        // ==================== Setters ====================
        Widget& set_width (size_t      width );
        Widget& set_height(size_t      height);
        Widget& set_name  (const char* name  );
        // =================================================

        virtual bool contains(Vec2f pixel, CoordinateSystem system);

        virtual bool on_move   (const Event& event) override;
        virtual bool on_click  (const Event& event) override;
        virtual bool on_hover  (const Event& event) override;
        virtual bool on_release(const Event& event) override;
        virtual bool on_unhover(const Event& event) override;

    protected:
        size_t  m_width;
        size_t  m_height;

        uint8_t m_status;
    
    private:
        const char*  m_name;
        const size_t m_seqNum;
    
    private:
        bool    status_bit__(size_t bit)                        const;
        void    log_with_name__(const char* text, int level=2)  const;
        size_t& widgets_count__()                               const;
};
