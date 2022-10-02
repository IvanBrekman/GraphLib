//
// Created by IvanBrekman on 19.09.2022
//

#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(Point2D center, AxisY_Direction diry, AxisX_Direction dirx)
: center(center), show_axis(false), axis_x_direction(dirx), axis_y_direction(diry), Drawable() {
    set_fill_color(Color::Blue);

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

CoordinateSystem CoordinateSystem::get_system_by_type(CoordinateSystem::Type type, double width, double height) {
    switch (type) {
        case CoordinateSystem::Type::CENTER:
            return CoordinateSystem(width / 2, height / 2, CoordinateSystem::AxisY_Direction::UP);
        case CoordinateSystem::Type::LEFT_UP:
            return CoordinateSystem(0, 0);
        case CoordinateSystem::Type::LEFT_BOTTOM:
            return CoordinateSystem(0, height, CoordinateSystem::AxisY_Direction::UP);
        
        default:
            ASSERT_IF(0, "Unknown Coordinate_System_Type value", CoordinateSystem(width, height));
    }
}

void CoordinateSystem::set_show_axis(bool show_axis_val) {
    show_axis = show_axis_val;
}

void CoordinateSystem::draw_axis(Window& window) {
    if (show_axis) {
        this->__axis_x.draw(window, CoordinateSystem(0, 0));
        this->__axis_y.draw(window, CoordinateSystem(0, 0));
    }
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

void CoordinateSystem::draw_impl_(Window& window, const CoordinateSystem& system) {
    for (Drawable* object : this->objects) {
        object->draw(window, *this);
    }

    draw_axis(window);
}
