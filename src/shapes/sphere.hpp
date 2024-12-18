#pragma once

#include <glm/glm.hpp>

#include "shape.hpp"

namespace tp {

	class Sphere : public Shape {
	public:
		Sphere() = default;
		Sphere(const glm::vec3& origin, float radius, Color color, float brightness)
			: origin(origin), radius(radius), color(color), brightness(brightness) {}

		std::optional<Sample> intersect(const Ray& ray) const override;
		BoundingBox get_bounding_box() const override;
		
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

	private:
		glm::vec3 origin;
		float radius;

		Color color;
		float brightness;
	};
}
