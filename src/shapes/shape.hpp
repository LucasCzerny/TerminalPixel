#pragma once

#include <optional>

#include <glm/glm.hpp>

#include "ray/ray.hpp"
#include "renderer/color.hpp"

namespace tp {

	struct Sample {
		float distance;

		glm::vec3 position;
		glm::vec3 normal;

		Color color;
		float brightness;
	};

	struct BoundingBox {
		glm::vec3 origin;
		float width, height, depth;
	};

	// interface
	class Shape {
	public:
		virtual ~Shape() {}

		virtual std::optional<Sample> intersect(const Ray& ray) const = 0;
		virtual BoundingBox get_bounding_box() const = 0;
	};
}
