//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Light.hpp"
#include "Scene.hpp"

Scene::Scene(Point2D main_point, double width, double height)
: Moveable(main_point), width(width), height(height) {
    this->__map    = PixelMap(0, 0, width, height);
    this->__system = CoordinateSystem::get_system_by_type(CoordinateSystem::Type::LEFT_UP, this->width, this->height);
}

Color Scene::cast_ray(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, std::vector <Light*> lights) {
    Point3D  intersection(0, 0, 0);     // ray intersection point with sphere
    Point3D  normal      (0, 0, 0);     // normal vector to intersection point
    Material material;

    if (!this->intersect_objects(ray_start, ray_dir, spheres, intersection, normal, material)) {
        return this->background;
    }

    double diffuse_light_intensity = 0;
    for (Light* light : lights) {
        Point3D light_dir        = (light->pos - intersection).normalize();     // light direction
        // light_dir.dump();
        // normal.dump();
        diffuse_light_intensity += light->intensity * std::max(0.0, Point3D::scalar_product(light_dir, normal));
    }
    // printf("\n");

    Color c = material.diffuse_color;
    Color res_color = Color(
        keep_in_range(0, 255, c.r * diffuse_light_intensity),
        keep_in_range(0, 255, c.g * diffuse_light_intensity),
        keep_in_range(0, 255, c.b * diffuse_light_intensity),
        255
    );

    return res_color;
}

bool Scene::intersect_objects(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, Point3D& intersection, Point3D& normal, Material& material) {
    double min_dist = std::numeric_limits<double>::max();
    int i = 0;
    for (Sphere* sphere : spheres) {
        double dist_i;
        if (sphere->intersect_ray(ray_start, ray_dir, dist_i) && dist_i < min_dist) {
            min_dist = dist_i;
            material = sphere->material;

            intersection = ray_start + ray_dir * dist_i;
            normal       = (intersection - sphere->center).normalize();
        }
    }

    return min_dist < std::numeric_limits<double>::max();
}


void Scene::render() {
    std::vector <Sphere*> spheres = {
        new Sphere(Point3D(-3.0,  0.0, -16.0), 2, EMERALD),
        new Sphere(Point3D(-1.0, -1.5, -12.0), 2, RUBIN),
        new Sphere(Point3D( 1.5, -0.5, -18.0), 3, RUBIN),
        new Sphere(Point3D( 7.0,  5.0, -18.0), 4, EMERALD),
    };

    std::vector <Light*>  lights  = {
        new Light (Point3D(-20, 20, 20), 1.5),
    };

    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            double px =  (2 * (x + 0.5) / (double)width  - 1) * tan(this->__fov / 2.) * width / (double)height;
            double py = -(2 * (y + 0.5) / (double)height - 1) * tan(this->__fov / 2.);

            Point3D dir = Point3D(px, py, -1).normalize();

            this->__map.set_pixel(x, y, this->cast_ray(Point3D(0, 0, 0), dir, spheres, lights));
        }
    }
}

void Scene::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    this->render();

    Point2D pixel = system.point_to_pixel(this->main_point);
    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->height;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->width;

    this->__map.move_to_point(pixel);
    this->__map.draw(window, this->__system);
}

double keep_in_range(double min, double max, double val) {
    return std::max(min, std::min(val, max));
}
