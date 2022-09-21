#include "GraphLib.hpp"

int main(void) {
    Window window(600, 600);
    window.set_coordinate_system_type(Window::Coordinate_System_Type::LEFT_BOTTOM);

    Vector second_hand(0, 0, 0, 100);
    second_hand.set_color(Color::Red);

    Vector minute_hand(0, 0, 0, 75);
    minute_hand.set_color(Color::Red);

    Vector vector(40, 40, 100, 100);

    CoordinateSystem system1(100, 300, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::RIGHT);
    system1.show();
    system1.append_object(&second_hand);
    system1.append_object(&minute_hand);

    CoordinateSystem system2(500, 300, CoordinateSystem::AxisY_Direction::DOWN, CoordinateSystem::AxisX_Direction::RIGHT);
    system2.show();
    system2.append_object(&vector);

    window.append_object(&system1);
    window.append_object(&system2);

    Ellipse rect(100, 100, 50, 100, true);
    rect.center().dump();
    rect.set_figure_color(Color::Red, Color::Blue, 10);

    Event::MouseEvent::Button_Type button_presed = Event::MouseEvent::Button_Type::NONE;

    Clock clock(15);
    while (window.is_open()) {
        Event event;
        while (window.poll_event(&event)) {
            switch (event.type) {
                case Event::WINDOW_CLOSED:
                    window.close();
                    break;
                
                case Event::MOUSE_BUTTON_PRESSED:
                    button_presed = event.mouse.button;
                    break;
                
                case Event::MOUSE_BUTTON_RELEASED:
                    button_presed = Event::MouseEvent::Button_Type::NONE;
                    break;
            }

            if (button_presed == Event::MouseEvent::Button_Type::LEFT  && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                vector.end = system2.pixel_to_point(event.mouse.pos);
            }

            if (button_presed == Event::MouseEvent::Button_Type::RIGHT && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                vector.move_to(system2.pixel_to_point(event.mouse.pos));
            }
        }

        if (clock.get_elapsed_seconds() > 1) {
            second_hand.rotate(-360.0 / (60     ));
            minute_hand.rotate(-360.0 / (60 * 60));

            clock.restart();
        }

        window.clear();

        window.draw_window_coordinate_system();
        window.draw_added_objects();

        rect.draw(window, system1);

        window.display();
    }

    return 0;
}
