//
// Created by IvanBrekman on 03.11.2022
//

#pragma once

#include <cinttypes>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Eventable/Eventable.hpp"

#include "../Class_Point/Point.hpp"

class Window;

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
        Widget(Vec2f mainPoint,    double width, double height, Window* parent=nullptr);
        Widget(double x, double y, double width, double height, Window* parent=nullptr)
        : Widget(Vec2f(x, y), width, height, parent) {}

        ~Widget();

        // ==================== Getters ====================
        size_t  width ()   const;
        size_t  height()   const;
        Window* parent()   const;

        bool is_clicked() const;
        bool is_hovered() const;
        // =================================================

        // ==================== Setters ====================
        Widget& set_width  (size_t      width );
        Widget& set_height (size_t      height);
        Widget& set_parent (Window*     parent);
        Widget& set_name   (const char* name  );
        Widget& set_log_val(size_t      logVal);
        // =================================================

        virtual bool contains(Vec2f pixel, CoordinateSystem system);

        virtual bool on_event  (const Event& event, Eventable::Type type);

        virtual bool on_move   (const Event& event) override;
        virtual bool on_tick   (const Event& event) override;
        virtual bool on_click  (const Event& event) override;
        virtual bool on_hover  (const Event& event) override;
        virtual bool on_release(const Event& event) override;
        virtual bool on_unhover(const Event& event) override;

    protected:
        size_t  m_width;
        size_t  m_height;

        uint8_t m_status;
        Window* m_parent;
    
    private:
        const char*  m_name;
        const size_t m_seqNum;
        size_t       m_logVal;

        bool (Widget::*funcs[6]) (const Event&) {
            &Widget::on_move,
            &Widget::on_tick,
            &Widget::on_click,
            &Widget::on_hover,
            &Widget::on_release,
            &Widget::on_unhover,
        };
    
    private:
        bool    status_bit__(size_t bit)                        const;
        void    log_with_name__(const char* text, int level=2)  const;
        size_t& widgets_count__()                               const;
};
