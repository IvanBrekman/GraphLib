//
// Created by IvanBrekman on 19.09.2022
//

#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(Point2D center, AxisY_Direction diry, AxisX_Direction dirx)
: center(center), axis_x_direction(dirx), axis_y_direction(diry), Drawable() {
    this->hidden     = true;
    this->fill_color = Color::Blue;

    double x = dirx * CoordinateSystem::__DRAW_AXIS_LENGTH;
    double y = diry * CoordinateSystem::__DRAW_AXIS_LENGTH;

    this->__axis_x = Vector(center - Point2D(x, 0), center + Point2D(x, 0));
    this->__axis_y = Vector(center - Point2D(0, y), center + Point2D(0, y));

    this->__axis_x.set_fill_color(this->fill_color);
    this->__axis_y.set_fill_color(this->fill_color);
}

Point2D CoordinateSystem::point_to_pixel(Point2D point) const {
    double new_x = this->axis_x_direction * point.x + center.x;
    double new_y = this->axis_y_direction * point.y + center.y;

    return Point2D(new_x, new_y);
}

Point2D CoordinateSystem::pixel_to_point(Point2D pixel) const {
    double new_x = this->axis_x_direction * (pixel.x - center.x);
    double new_y = this->axis_y_direction * (pixel.y - center.y);

    return Point2D(new_x, new_y);
}

void CoordinateSystem::set_draw_status(bool need_to_draw) {
    this->hidden = !need_to_draw;
}

void CoordinateSystem::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (index == CoordinateSystem::__LAST_INDEX) this->objects.push_back(object);
    else                                         this->objects.emplace(this->objects.cbegin() + index, object);
}

void CoordinateSystem::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        this->append_object(object, index++);
    }
}

void CoordinateSystem::draw_added_objects(Window& window) {
    for (Drawable* object : this->objects) {
        object->draw(window, *this);
    }
}

void CoordinateSystem::dump() const {
    printf(
        "<CoordinateSystem: center - (%5.1lf, %5.1lf) | type - '%4s-%-5s'\n",
        this->center.x, this->center.y,
        this->axis_y_direction == CoordinateSystem::AxisY_Direction::UP   ? "UP"   : "DOWN",
        this->axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT ? "LEFT" : "RIGHT"
    );
    printf("    AxisX - "); this->__axis_x.dump();
    printf("    AxisY - "); this->__axis_y.dump();
    printf(">\n");
}

void CoordinateSystem::hide() {
    for (Drawable* object : objects) {
        object->hide();
    }
}

void CoordinateSystem::show() {
    for (Drawable* object : objects) {
        object->show();
    }
}

void CoordinateSystem::draw_on_window(Window& window) {
    this->draw(window, CoordinateSystem(0, 0));
}

void CoordinateSystem::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;
    
    this->__axis_x.draw(window, system);
    this->__axis_y.draw(window, system);
}
