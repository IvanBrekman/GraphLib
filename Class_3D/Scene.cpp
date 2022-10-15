//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Light.hpp"
#include "Scene.hpp"
#include "Plane.hpp"

Scene::Scene(Vec2f mainPoint, double width, double height, const char* backImgPath)
: Moveable(mainPoint), m_width(width), m_height(height) {
    m_map__    = PixelMap(0, 0, width, height);
    m_system__ = CoordinateSystem::get_system_by_type(CoordinateSystem::Type::LEFT_UP, m_width, m_height);

    if (VALID_PTR(backImgPath)) m_background.load_image(backImgPath);
    else {
        m_background = PixelMap(mainPoint, width, height);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                m_background.set_pixel(x, y, Scene::DEFAULT_BACK_COLOR__);
            }
        }
    }
}

Color Scene::cast_ray(Vec3f rayStart, Vec3f rayDir, int x, int y, int depth) {
    Vec3f  intersection;                  // ray intersection point with sphere
    Vec3f  normal;                        // normal vector to intersection point
    Material material;

    if (depth > Scene::REFLECT_DEPTH__ || !intersect_objects(rayStart, rayDir, intersection, normal, material)) {
        return m_background.get_pixel(x, y);
    }

    Vec3f reflectDir   = reflect(rayDir, normal).normalize();
    Vec3f reflectStart = intersection - (normal * Scene::DEFAULT_DEVIATION__) * (2 * (scalarProduct(reflectDir, normal) < 0) - 1);
    Color   reflectColor = cast_ray(reflectStart, reflectDir, x, y, depth + 1);

    double  diffuseLightIntensity = 0;      // coef for diffuse  light
    double specularLightIntensity = 0;      // coef for specular light
    for (Light* light : m_lights) {
        Vec3f lightDir   = (light->m_pos - intersection).normalize();         // light direction
        double  lightDist  = (light->m_pos - intersection).length_squared();

        // ==================== Calculate shadows ====================
        Vec3f  shadowStart = intersection - (normal * Scene::DEFAULT_DEVIATION__) * (2 * (scalarProduct(lightDir, normal) < 0) - 1);
        Vec3f  shadowIntersection;
        Vec3f  shadowNormal;
        Material shadowMaterial;
        if (
            intersect_objects(shadowStart, lightDir, shadowIntersection, shadowNormal, shadowMaterial) &&
            ((shadowIntersection-shadowStart).length_squared() < lightDist)
        ) continue;
        // ===========================================================

        /* Means that there isn't any intersections with other scene objects */

         diffuseLightIntensity += light->m_intensity *     std::max(0.0, scalarProduct(lightDir, normal));
        specularLightIntensity += light->m_intensity * pow(std::max(0.0, scalarProduct(reflect(lightDir, normal), rayDir)), material.specularExp);
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

bool Scene::intersect_objects(Vec3f rayStart, Vec3f rayDir, Vec3f& intersection, Vec3f& normal, Material& material) {
    double minDist = std::numeric_limits<double>::max() - 1;
    for (SceneObject* object : m_objects) {
        double distI = minDist + 1;
        if (object->intersect_ray(rayStart, rayDir, distI) && distI < minDist) {
            minDist  = distI;
            material = object->m_material;

            intersection = rayStart + rayDir * distI;
            normal       = object->get_normal(intersection);
        }
    }

    return minDist < std::numeric_limits<double>::max();
}

void Scene::append_scene_object(SceneObject* object) {
    m_objects.push_back(object);
}

void Scene::extend_scene_objects(std::vector <SceneObject*> objects) {
    for (SceneObject* object : objects) {
        append_scene_object(object);
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

            Vec3f dir = Vec3f(px, py, -1).normalize();

            m_map__.set_pixel(x, y, cast_ray(Vec3f(0, 0, 0), dir, x, y));
        }
    }
}

// @virtual
void Scene::draw_impl_(Window& window, const CoordinateSystem& system) {
    render();

    Vec2f pixel = system.point_to_pixel(main_point());
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    m_map__.move_to_point(pixel);
    m_map__.draw(window, m_system__);
}

// @virtual
Vec2f Scene::center() const {
    return main_point();
}

Vec3f reflect(Vec3f light, Vec3f normal) {
    return light - normal * 2.0 * scalarProduct(light, normal);
}
