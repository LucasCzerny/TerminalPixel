#include "sphere.hpp"

#include <iostream>
#include <limits>

namespace tp {

	std::optional<Sample> Sphere::intersect(const Ray& ray) const {
		const glm::vec3 origin = ray.origin - this->origin;

		const float a = glm::dot(ray.direction, ray.direction);
		const float b = 2.0f * glm::dot(origin, ray.direction);
		const float c = glm::dot(origin, origin) - radius * radius;

		// quadratic formula discriminant:
		// b^2 - 4ac

		const float discriminant = b * b - 4.0 * a * c;
		if (discriminant < 0.0f) {
			return std::nullopt;
		}

		const float first_distance = (-b - glm::sqrt(discriminant)) / (2.0f * a);
		const float second_distance = (-b + glm::sqrt(discriminant)) / (2.0f * a);

		float local_distance;

		if (first_distance <= 0.0f) {
			local_distance = second_distance;
		} else if (second_distance <= 0.0f) {
			local_distance = first_distance;
		} else {
			local_distance = std::min(first_distance, second_distance);
		}

		if (local_distance <= 0.0f) {
			return std::nullopt;
		}

		const glm::vec3 local_intersection_point = origin + local_distance * glm::normalize(ray.direction);
		const glm::vec3 intersection_point = local_intersection_point + this->origin;

		const float distance = glm::length(intersection_point - ray.origin);
		const glm::vec3 normal = glm::normalize(intersection_point - this->origin);

		return Sample{
			distance,
			intersection_point, normal,
			color, brightness
		};
	}

	BoundingBox Sphere::get_bounding_box() const {
		return BoundingBox{
			origin,
			2.0f * radius, 2.0f * radius, 2.0f * radius
		};
	}

	void Sphere::set_origin(const glm::vec3& origin) {
		this->origin = origin;
	}

	void Sphere::change_origin(const glm::vec3& change) {
		origin += change;
	}

	glm::vec3 Sphere::get_origin() const {
		return origin;
	}

	void Sphere::set_radius(float radius) {
		this->radius = radius;
	}

	void Sphere::change_radius(float change) {
		radius += change;
	}

	float Sphere::get_radius() const {
		return radius;
	}

	void Sphere::set_color(Color color) {
		this->color = color;
	}

	Color Sphere::get_color() const {
		return color;
	}

	void tp::Sphere::set_brightness(float brightness) {
		this->brightness = brightness;	
	}

	float tp::Sphere::get_brightness() const {
		return brightness;	
	}
}
