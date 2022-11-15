//
// Created by IvanBrekman on 03.11.2022
//

#include <cstring>

#include "../Class_Utils/baselib.hpp"

#include "Widget.hpp"

Widget::Widget(Vec2f mainPoint, double width, double height, Window* parent)
: Drawable(),       Moveable(mainPoint),           Eventable(),
  m_width(width),   m_height(height),              m_status(0), m_parent(parent),
  m_name("Widget"), m_seqNum(++widgets_count__()), m_logVal(2)
  { }

Widget::~Widget() {
    --widgets_count__();
}

// ==================== Getters ====================
size_t Widget::width() const {
    return m_width;
}

size_t Widget::height() const {
    return m_height;
}

Window* Widget::parent() const {
    return m_parent;
}

bool Widget::is_clicked() const {
    return status_bit__(Status::CLICKED);
}

bool Widget::is_hovered() const {
    return status_bit__(Status::HOVERED);
}
// =================================================

// ==================== Setters ====================
Widget& Widget::set_width(size_t width) {
    m_width = width;

    return *this;
}

Widget& Widget::set_height(size_t height) {
    m_height = height;

    return *this;
}

Widget& Widget::set_parent(Window* parent) {
    m_parent = parent;

    return *this;
}

Widget& Widget::set_name(const char* name) {
    m_name = name;

    return *this;
}

Widget& Widget::set_log_val(size_t logVal) {
    m_logVal = logVal;

    return *this;
}
// =================================================

// @virtual
bool Widget::contains(Vec2f pixel, CoordinateSystem system) {
    Vec2f point = system.pixel_to_point(pixel);
    Vec2f start = center() - Vec2f(m_width / 2, m_height / 2);

    return (start.x <= point.x && point.x <= (start.x + m_width )) &&
           (start.y <= point.y && point.y <= (start.y + m_height));
}

bool Widget::on_event(const Event& event, Eventable::Type type) {
    return (this->*funcs[type])(event);
}

// @virtual
bool Widget::on_move(const Event& event) {
    if (m_hidden) return false;

    bool containsFlag = contains(event.mouse.pos, event.system);

    if ( containsFlag) log_with_name__("on_move    event caught", m_logVal);

    if ( containsFlag && !is_hovered()) on_hover  (event);
    if (!containsFlag &&  is_hovered()) on_unhover(event);

    return containsFlag && Eventable::on_move(event);
}

// @virtual
bool Widget::on_tick(const Event& event) {
    if (m_hidden) return false;

    log_with_name__("on_tick    event caught", m_logVal + 5);

    Eventable::on_tick(event);
    return false;
}

// @virtual
bool Widget::on_click(const Event& event) {
    if (m_hidden) return false;

    if (!contains(event.mouse.pos, event.system)) return false;
    log_with_name__("on_click   event caught", m_logVal);

    m_status |= 1 << Widget::Status::CLICKED;

    return Eventable::on_click(event);
}

// @virtual
bool Widget::on_hover(const Event& event) {
    if (m_hidden) return false;

    log_with_name__("on_hover   event caught", m_logVal);
    ASSERT_IF(contains(event.mouse.pos, event.system) && !is_hovered(), "on_hover widget event called, but widget doesn't contain mouse pos", false);

    m_status |= 1 << Widget::Status::HOVERED;

    return Eventable::on_hover(event);
}

// @virtual
bool Widget::on_release(const Event& event) {
    if (m_hidden) return false;

    if (!is_clicked()) return false;

    log_with_name__("on_release event caught", m_logVal);

    m_status &= ~(1 << Widget::Status::CLICKED);

    return Eventable::on_release(event);
}

// @virtual
bool Widget::on_unhover(const Event& event) {
    if (m_hidden) return false;

    log_with_name__("on_unhover event caught", m_logVal);
    ASSERT_IF(is_hovered(), "on_unhover widget event called, but widget is already unhovered", false);

    m_status &= ~(1 << Widget::Status::HOVERED);

    return Eventable::on_unhover(event);
}

bool Widget::status_bit__(size_t bit) const {
    ASSERT_IF(bit < Widget::Status::STATUS_NUM, "bit value is greater than status amount", false);

    return (m_status >> bit) & 1;
}

void Widget::log_with_name__(const char* text, int level) const {
    LOGN(level, printf("%8s_%zd - %s\n", m_name, m_seqNum, text););
}

size_t& Widget::widgets_count__() const {
    static size_t wCount = 0;
    return wCount;
}
