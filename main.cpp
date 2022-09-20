#include <SFML/Graphics.hpp>

#include "GraphLib.hpp"


int main(void) {
    Window window(400, 400);
    window.set_coordinate_system_type(Window::Coordinate_System_Type::CENTER);

    Vector v1(0, 0, 100, 100, Color::Red);

    CoordinateSystem system(350, 350, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::LEFT);
    system.show();

    window.append_object(&v1);
    window.append_object(&system);

    while (window.is_open()) {
        Event event;
        while (window.poll_event(&event)) {
            if (event.type == Event::WINDOW_CLOSED) {
                window.close();
            }
        }

        window.clear();

        // window.draw_window_coordinate_system();
        window.draw_added_objects();

        window.display();
    }

    return 0;
}
