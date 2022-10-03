//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "PixelMap.hpp"

PixelMap::PixelMap(Point2D mainPoint, int width, int height)
: Drawable(), Moveable(mainPoint), m_width(width), m_height(height) {
    m_sfml_pixels__ = new sf::Uint8[width * height * 4];
    m_sfml_texture__.create(width, height);
}

void PixelMap::set_pixel(int x, int y, Color color) {
    sf::Uint8* pixel = m_sfml_pixels__ + (x + y * m_width) * 4;

    pixel[0] = color.r;
    pixel[1] = color.g;
    pixel[2] = color.b;
    pixel[3] = color.a;
}

Color PixelMap::get_pixel(int x, int y) {
    sf::Uint8* pixel = m_sfml_pixels__ + (x + y * m_width) * 4;

    return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

void PixelMap::load_image(const char* path) {
    sf::Image img;
    img.loadFromFile(path);

    m_width  = img.getSize().x;
    m_height = img.getSize().y;

    m_sfml_pixels__ = new sf::Uint8[m_width * m_height * 4];
    m_sfml_texture__.create(m_width, m_height);

    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            set_pixel(x, y, img.getPixel(x, y));
        }
    }
}

// @virtual
void PixelMap::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (m_hidden) return;

    Point2D pixel = system.point_to_pixel(m_mainPoint);
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    m_sfml_texture__.update(m_sfml_pixels__);

    m_sfml_sprite__ = sf::Sprite(m_sfml_texture__);
    m_sfml_sprite__.setPosition(pixel.to_sfml_vector());

    get_sfml_window_(window).draw(m_sfml_sprite__);
}

// @virtual
Point2D PixelMap::center() const {
    if (m_centered) return m_mainPoint;
    return m_mainPoint + Point2D(m_width / 2, m_height / 2);
}
