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

Color Scene::cast_ray(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, std::vector <Light*> lights, int depth) {
    Point3D  intersection(0, 0, 0);         // ray intersection point with sphere
    Point3D  normal      (0, 0, 0);         // normal vector to intersection point
    Material material;

    if (depth > this->__REFLECT_DEPTH || !this->intersect_objects(ray_start, ray_dir, spheres, intersection, normal, material)) {
        return this->background;
    }

    Point3D reflect_dir   = reflect(ray_dir, normal).normalize();
    Point3D reflect_start = intersection - (normal * this->__DEFAULT_DEVIATION) * (2 * (Point3D::scalar_product(reflect_dir, normal) < 0) - 1);
    Color   reflect_color = this->cast_ray(reflect_start, reflect_dir, spheres, lights, depth + 1);

    double  diffuse_light_intensity = 0;    // coef for diffuse  light
    double specular_light_intensity = 0;    // coef for specular light
    for (Light* light : lights) {
        Point3D light_dir   = (light->pos - intersection).normalize();          // light direction
        double  light_dist  = (light->pos - intersection).length_square();

        // ==================== Calculate shadows ====================
        Point3D  shadow_start = intersection - (normal * this->__DEFAULT_DEVIATION) * (2 * (Point3D::scalar_product(light_dir, normal) < 0) - 1);
        Point3D  shadow_intersection(0, 0, 0);
        Point3D  shadow_normal      (0, 0, 0);
        Material shadow_material;
        if (
            this->intersect_objects(shadow_start, light_dir, spheres, shadow_intersection, shadow_normal, shadow_material) &&
            ((shadow_intersection-shadow_start).length_square() < light_dist)
        ) continue;
        // ===========================================================

        /* Means that there isn't any intersections with other scene objects */

         diffuse_light_intensity += light->intensity *     std::max(0.0, Point3D::scalar_product(light_dir, normal));
        specular_light_intensity += light->intensity * pow(std::max(0.0, Point3D::scalar_product(reflect(light_dir, normal), ray_dir)), material.specular_exp);
    }

    double df_coef  =  diffuse_light_intensity * material.albedo.x;             // coef for fidduse  light according to albedo value
    double sc_coef  = specular_light_intensity * material.albedo.y * 255;       // coef for specular light according to albedo value (mult for 255 cause material.diffuse_color value lies between 0 and 255)

    double r = material.diffuse_color.r * df_coef + sc_coef + reflect_color.r * material.albedo.z;
    double g = material.diffuse_color.g * df_coef + sc_coef + reflect_color.g * material.albedo.z;
    double b = material.diffuse_color.b * df_coef + sc_coef + reflect_color.b * material.albedo.z;

    double max = std::max(r, std::max(g, b));
    if (max > 255) {                                                            // Check color channel overflow
        r *= (255 / max);
        g *= (255 / max);
        b *= (255 / max);
    }

    Color res_color = Color(r, g, b, 255);

    return res_color;
}

bool Scene::intersect_objects(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, Point3D& intersection, Point3D& normal, Material& material) {
    double min_dist = std::numeric_limits<double>::max();
    for (Sphere* sphere : spheres) {
        double dist_i;
        if (sphere->intersect_ray(ray_start, ray_dir, dist_i) && dist_i < min_dist) {
            min_dist = dist_i;
            material = sphere->material;

            intersection = ray_start + ray_dir * dist_i;
            normal       = (intersection - sphere->center).normalize();
        }
    }

    // TODO
    double checkerboard_dist = std::numeric_limits<float>::max();
    Point3D n = Point3D(0, 1, 0);
    double  d = -4;

    double c = Point3D::scalar_product(ray_dir, n);
    if (fabs(c) > this->__DEFAULT_DEVIATION) {
        double  alpha = (d - Point3D::scalar_product(ray_start, n)) / c;
        Point3D q     = ray_start + ray_dir * alpha;
        if (alpha > 0 && (-10 < q.x && q.x < 10) && (-30 < q.z && q.z < -10) && alpha < min_dist) {
            checkerboard_dist = alpha;
            intersection      = q;
            normal            = n;
            material.diffuse_color = Color(255,178.5,76.5);
        }
    }
    // TODO

    return std::min(min_dist, checkerboard_dist) < 1000;
}

void Scene::append_sphere(Sphere* sphere) {
    this->spheres.push_back(sphere);
}

void Scene::extend_spheres(std::vector <Sphere*> spheres) {
    for (Sphere* sphere : spheres) {
        this->append_sphere(sphere);
    }
}

void Scene::append_light(Light* light) {
    this->lights.push_back(light);
}

void Scene::extend_lights(std::vector <Light*> lights) {
    for (Light* light : lights) {
        this->append_light(light);
    }
}

void Scene::render() {
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            double px =  (2 * (x + 0.5) / (double)width  - 1) * tan(this->__FOV / 2.) * width / (double)height;
            double py = -(2 * (y + 0.5) / (double)height - 1) * tan(this->__FOV / 2.);

            Point3D dir = Point3D(px, py, -1).normalize();

            this->__map.set_pixel(x, y, this->cast_ray(Point3D(0, 0, 0), dir, spheres, lights));
        }
    }
}

void Scene::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (this->m_hidden) return;

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

Point3D reflect(Point3D light, Point3D normal) {
    return light - normal * 2.0 * Point3D::scalar_product(light, normal);
}
