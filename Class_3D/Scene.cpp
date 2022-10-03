//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Light.hpp"
#include "Scene.hpp"

Scene::Scene(Point2D mainPoint, double width, double height)
: Moveable(mainPoint), m_width(width), m_height(height) {
    m_map__    = PixelMap(0, 0, width, height);
    m_system__ = CoordinateSystem::get_system_by_type(CoordinateSystem::Type::LEFT_UP, m_width, m_height);
}

Color Scene::cast_ray(Point3D rayStart, Point3D rayDir, std::vector <Sphere*> spheres, std::vector <Light*> lights, int depth) {
    Point3D  intersection;                  // ray intersection point with sphere
    Point3D  normal;                        // normal vector to intersection point
    Material material;

    if (depth > Scene::REFLECT_DEPTH__ || !intersect_objects(rayStart, rayDir, spheres, intersection, normal, material)) {
        return m_background;
    }

    Point3D reflectDir   = reflect(rayDir, normal).normalize();
    Point3D reflectStart = intersection - (normal * Scene::DEFAULT_DEVIATION__) * (2 * (Point3D::scalar_product(reflectDir, normal) < 0) - 1);
    Color   reflectColor = cast_ray(reflectStart, reflectDir, spheres, lights, depth + 1);

    double  diffuseLightIntensity = 0;      // coef for diffuse  light
    double specularLightIntensity = 0;      // coef for specular light
    for (Light* light : lights) {
        Point3D lightDir   = (light->m_pos - intersection).normalize();         // light direction
        double  lightDist  = (light->m_pos - intersection).length_square();

        // ==================== Calculate shadows ====================
        Point3D  shadowStart = intersection - (normal * Scene::DEFAULT_DEVIATION__) * (2 * (Point3D::scalar_product(lightDir, normal) < 0) - 1);
        Point3D  shadowIntersection;
        Point3D  shadowNormal;
        Material shadowMaterial;
        if (
            intersect_objects(shadowStart, lightDir, spheres, shadowIntersection, shadowNormal, shadowMaterial) &&
            ((shadowIntersection-shadowStart).length_square() < lightDist)
        ) continue;
        // ===========================================================

        /* Means that there isn't any intersections with other scene objects */

         diffuseLightIntensity += light->m_intensity *     std::max(0.0, Point3D::scalar_product(lightDir, normal));
        specularLightIntensity += light->m_intensity * pow(std::max(0.0, Point3D::scalar_product(reflect(lightDir, normal), rayDir)), material.specularExp);
    }

    double dfCoef  =  diffuseLightIntensity * material.albedo.x;               // coef for fidduse  light according to albedo value
    double scCoef  = specularLightIntensity * material.albedo.y * 255;         // coef for specular light according to albedo value (mult for 255 cause material.diffuse_color value lies between 0 and 255)

    double r = material.diffuseColor.r* dfCoef + scCoef + reflectColor.r * material.albedo.z;
    double g = material.diffuseColor.g* dfCoef + scCoef + reflectColor.g * material.albedo.z;
    double b = material.diffuseColor.b* dfCoef + scCoef + reflectColor.b * material.albedo.z;

    double max = std::max(r, std::max(g, b));
    if (max > 255) {                                                            // Check color channel overflow
        r *= (255 / max);
        g *= (255 / max);
        b *= (255 / max);
    }

    return Color(r, g, b, 255);
}

bool Scene::intersect_objects(Point3D rayStart, Point3D rayDir, std::vector <Sphere*> spheres, Point3D& intersection, Point3D& normal, Material& material) {
    double minDist = std::numeric_limits<double>::max();
    for (Sphere* sphere : spheres) {
        double distI;
        if (sphere->intersect_ray(rayStart, rayDir, distI) && distI < minDist) {
            minDist  = distI;
            material = sphere->m_material;

            intersection = rayStart + rayDir * distI;
            normal       = (intersection - sphere->m_center).normalize();
        }
    }

    // TODO
    double checkerboardDist = std::numeric_limits<double>::max();
    Point3D n = Point3D(0, 1, 0);
    double  d = -4;

    double c = Point3D::scalar_product(rayDir, n);
    if (fabs(c) > Scene::DEFAULT_DEVIATION__) {
        double  alpha = (d - Point3D::scalar_product(rayStart, n)) / c;
        Point3D q     = rayStart + rayDir * alpha;
        if (alpha > 0 && (-10 < q.x && q.x < 10) && (-30 < q.z && q.z < -10) && alpha < minDist) {
            checkerboardDist  = alpha;
            intersection      = q;
            normal            = n;
            material.diffuseColor = Color(255,178.5,76.5);
        }
    }
    // TODO

    return std::min(minDist, checkerboardDist) < std::numeric_limits<double>::max();
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
            double px =  (2 * (x + 0.5) / (double)m_width  - 1) * tan(Scene::FOV__ / 2.) * m_width / (double)m_height;
            double py = -(2 * (y + 0.5) / (double)m_height - 1) * tan(Scene::FOV__ / 2.);

            Point3D dir = Point3D(px, py, -1).normalize();

            m_map__.set_pixel(x, y, cast_ray(Point3D(0, 0, 0), dir, m_spheres, m_lights));
        }
    }
}

// @virtual
void Scene::draw_impl_(Window& window, const CoordinateSystem& system) {
    render();

    Point2D pixel = system.point_to_pixel(m_mainPoint);
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    m_map__.move_to_point(pixel);
    m_map__.draw(window, m_system__);
}

// @virtual
Point2D Scene::center() const {
    return m_mainPoint;
}

Point3D reflect(Point3D light, Point3D normal) {
    return light - normal * 2.0 * Point3D::scalar_product(light, normal);
}
