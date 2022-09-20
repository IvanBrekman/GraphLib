#include <SFML/Graphics.hpp>

#include "GraphLib.hpp"


int main(void) {
    Window window(600, 600);
    window.set_coordinate_system_type(Window::Coordinate_System_Type::CENTER);

    Vector v(10, 0, 100, 100);
    v.set_color(Color::Red);

    CoordinateSystem system1(350, 350, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::RIGHT);
    system1.show();
    system1.append_object(&v);

    CoordinateSystem system2(100, 100, CoordinateSystem::AxisY_Direction::DOWN, CoordinateSystem::AxisX_Direction::RIGHT);
    system2.show();
    system2.append_object(&v);

    window.append_object(&system1);
    window.append_object(&system2);

    Event::MouseEvent::Button_Type button_presed = Event::MouseEvent::Button_Type::NONE;

    while (window.is_open()) {
        Event event;
        while (window.poll_event(&event)) {
            switch (event.type) {
                case Event::WINDOW_CLOSED:
                    window.close();
                    break;
                
                case Event::MOUSE_BUTTON_PRESSED:
                    button_presed = event.mouse.button;

                    printf("Button: %d\n", button_presed);

                    break;
                
                case Event::MOUSE_BUTTON_RELEASED:
                    button_presed = Event::MouseEvent::Button_Type::NONE;
                    break;
            }

            if (button_presed == Event::MouseEvent::Button_Type::LEFT  && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                v.end = system1.pixel_to_point(event.mouse.pos);
            }

            if (button_presed == Event::MouseEvent::Button_Type::RIGHT && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                printf("move to\n");
                v.move_to(system1.pixel_to_point(event.mouse.pos));
            }
        }

        window.clear();

        window.draw_added_objects();

        window.display();
    }

    return 0;
}
