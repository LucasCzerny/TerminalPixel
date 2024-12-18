#pragma once

#include <glm/glm.hpp>

#include "shape.hpp"

#include "renderer/color.hpp"

namespace tp {

	class Box : public Shape {
	public:
		Box() = default;
		Box(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Color color, float brightness)
			: position(position), rotation(rotation), scale(scale), color(color), brightness(brightness) {}

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
		glm::vec3 position, rotation, scale;

        Color color;
        float brightness;

    private:
        glm::mat4 calculate_transform() const;
        std::optional<std::pair<float, glm::vec3>> intersect_local_space(const Ray& ray) const;
	};
}
