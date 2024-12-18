#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "color.hpp"

#include "camera/camera.hpp"
#include "light/light.hpp"
#include "shapes/shape.hpp"
#include "terminal/terminal.hpp"

namespace tp {

	class Renderer {
	public:
		Renderer(Camera& camera, Terminal& terminal, ClearColor clear_color = ClearColor::reset)
			: camera(camera), terminal(terminal), clear_color(clear_color) {}

		void draw(const std::vector<std::unique_ptr<Shape>>& shapes, const Light& light);

		void set_clear_color(ClearColor clear_color);

	private:
		Camera& camera;
		Terminal& terminal;

		ClearColor clear_color;

	private:
        std::optional<Sample> ray_tracing(const Ray& ray, const std::vector<std::unique_ptr<Shape>>& shapes, const Light& light);
		std::pair<Color, float> blinn_phong(const Sample& sample, const glm::vec3& light_direction, const glm::vec3& view_direction);
		void draw_character(Color color, float brightness);
	};
}
