#include "light.hpp"

namespace tp {

    std::optional<Sample> Light::intersect(const Ray& ray) const {
        return sphere.intersect(ray);
    }

    BoundingBox Light::get_bounding_box() const {
        return sphere.get_bounding_box();
    }
    
    void Light::set_origin(const glm::vec3& origin) {
        sphere.set_origin(origin);
    }

    void Light::change_origin(const glm::vec3& change) {
        sphere.change_origin(change);
    }

    glm::vec3 Light::get_origin() const {
        return sphere.get_origin();
    }

    void Light::set_radius(float radius) {
        sphere.set_radius(radius);
    }

    void Light::change_radius(float change) {
        sphere.change_radius(change);
    }

    float Light::get_radius() const {
        return sphere.get_radius();
    }

    void Light::set_color(Color color) {
        sphere.set_color(color);
    }

    Color Light::get_color() const {
        return sphere.get_color();
    }

    void Light::set_brightness(float brightness) {
        sphere.set_brightness(brightness);
    }

    float Light::get_brightness() const {
        return sphere.get_brightness();
    }

    void Light::change_visibility(bool visible) {
        this->visible = visible;
    }

    bool Light::is_visible() const {
        return visible;
    }
}