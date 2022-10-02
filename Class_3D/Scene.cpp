//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Light.hpp"
#include "Scene.hpp"

Scene::Scene(Point2D main_point, double width, double height)
: Moveable(main_point), m_width(width), m_height(height) {
    m_map__    = PixelMap(0, 0, width, height);
    m_system__ = CoordinateSystem::get_system_by_type(CoordinateSystem::Type::LEFT_UP, m_width, m_height);
}

Color Scene::cast_ray(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, std::vector <Light*> lights, int depth) {
    Point3D  intersection(0, 0, 0);         // ray intersection point with sphere
    Point3D  normal      (0, 0, 0);         // normal vector to intersection point
    Material material;

    if (depth > m_REFLECT_DEPTH__ || !intersect_objects(ray_start, ray_dir, spheres, intersection, normal, material)) {
        return m_background;
    }

    Point3D reflect_dir   = reflect(ray_dir, normal).normalize();
    Point3D reflect_start = intersection - (normal * m_DEFAULT_DEVIATION__) * (2 * (Point3D::scalar_product(reflect_dir, normal) < 0) - 1);
    Color   reflect_color = cast_ray(reflect_start, reflect_dir, spheres, lights, depth + 1);

    double  diffuse_light_intensity = 0;    // coef for diffuse  light
    double specular_light_intensity = 0;    // coef for specular light
    for (Light* light : lights) {
        Point3D light_dir   = (light->m_pos - intersection).normalize();          // light direction
        double  light_dist  = (light->m_pos - intersection).length_square();

        // ==================== Calculate shadows ====================
        Point3D  shadow_start = intersection - (normal * m_DEFAULT_DEVIATION__) * (2 * (Point3D::scalar_product(light_dir, normal) < 0) - 1);
        Point3D  shadow_intersection(0, 0, 0);
        Point3D  shadow_normal      (0, 0, 0);
        Material shadow_material;
        if (
            intersect_objects(shadow_start, light_dir, spheres, shadow_intersection, shadow_normal, shadow_material) &&
            ((shadow_intersection-shadow_start).length_square() < light_dist)
        ) continue;
        // ===========================================================

        /* Means that there isn't any intersections with other scene objects */

         diffuse_light_intensity += light->m_intensity *     std::max(0.0, Point3D::scalar_product(light_dir, normal));
        specular_light_intensity += light->m_intensity * pow(std::max(0.0, Point3D::scalar_product(reflect(light_dir, normal), ray_dir)), material.specularExp);
    }

    double df_coef  =  diffuse_light_intensity * material.albedo.x;             // coef for fidduse  light according to albedo value
    double sc_coef  = specular_light_intensity * material.albedo.y * 255;       // coef for specular light according to albedo value (mult for 255 cause material.diffuse_color value lies between 0 and 255)

    double r = material.diffuseColor.r * df_coef + sc_coef + reflect_color.r * material.albedo.z;
    double g = material.diffuseColor.g * df_coef + sc_coef + reflect_color.g * material.albedo.z;
    double b = material.diffuseColor.b * df_coef + sc_coef + reflect_color.b * material.albedo.z;

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
            material = sphere->m_material;

            intersection = ray_start + ray_dir * dist_i;
            normal       = (intersection - sphere->m_center).normalize();
        }
    }

    // TODO
    double checkerboard_dist = std::numeric_limits<float>::max();
    Point3D n = Point3D(0, 1, 0);
    double  d = -4;

    double c = Point3D::scalar_product(ray_dir, n);
    if (fabs(c) > m_DEFAULT_DEVIATION__) {
        double  alpha = (d - Point3D::scalar_product(ray_start, n)) / c;
        Point3D q     = ray_start + ray_dir * alpha;
        if (alpha > 0 && (-10 < q.x && q.x < 10) && (-30 < q.z && q.z < -10) && alpha < min_dist) {
            checkerboard_dist = alpha;
            intersection      = q;
            normal            = n;
            material.diffuseColor = Color(255,178.5,76.5);
        }
    }
    // TODO

    return std::min(min_dist, checkerboard_dist) < 1000;
}

void Scene::append_sphere(Sphere* sphere) {
    m_spheres.push_back(sphere);
}

void Scene::extend_spheres(std::vector <Sphere*> spheres) {
    for (Sphere* sphere : spheres) {
        append_sphere(sphere);
    }
}

void Scene::append_light(Light* light) {
    m_lights.push_back(light);
}

void Scene::extend_lights(std::vector <Light*> lights) {
    for (Light* light : lights) {
        append_light(light);
    }
}

void Scene::render() {
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            double px =  (2 * (x + 0.5) / (double)m_width  - 1) * tan(m_FOV__ / 2.) * m_width / (double)m_height;
            double py = -(2 * (y + 0.5) / (double)m_height - 1) * tan(m_FOV__ / 2.);

            Point3D dir = Point3D(px, py, -1).normalize();

            m_map__.set_pixel(x, y, cast_ray(Point3D(0, 0, 0), dir, m_spheres, m_lights));
        }
    }
}

void Scene::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (m_hidden) return;

    render();

    Point2D pixel = system.point_to_pixel(m_mainPoint);
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    m_map__.move_to_point(pixel);
    m_map__.draw(window, m_system__);
}

Point2D Scene::center() const {
    return m_mainPoint;
}

Point3D reflect(Point3D light, Point3D normal) {
    return light - normal * 2.0 * Point3D::scalar_product(light, normal);
}
