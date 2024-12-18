#pragma once

#include <glm/glm.hpp>

#include "shapes/sphere.hpp"

namespace tp {

    // this is basically a point light
    class Light {
    public:
        Light(const glm::vec3& position, float radius, Color color, float brightness, bool is_visible = false)
            : sphere(position, radius, color, brightness), visible(is_visible) {}

		std::optional<Sample> intersect(const Ray& ray) const;
		BoundingBox get_bounding_box() const;
		
		void set_origin(const glm::vec3& origin);
		void change_origin(const glm::vec3& change);
		glm::vec3 get_origin() const;

		void set_radius(float radius);
		void change_radius(float change);
		float get_radius() const;

		void set_color(Color color);
		Color get_color() const;

		void set_brightness(float brightness);
		float get_brightness() const;

		void change_visibility(bool visible);
		bool is_visible() const;

    private:
        Sphere sphere;
		bool visible;
    };
}