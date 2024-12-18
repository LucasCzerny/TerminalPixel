#include "renderer.hpp"

#include <iostream>
#include <limits>
// TODO: remove
#include <chrono>
#include <thread>

#include "platform/terminal_util.hpp"
#include "ray/ray.hpp"

namespace tp {

	void Renderer::draw(const std::vector<std::unique_ptr<Shape>>& shapes, const Light& light) {
		platform::new_frame();
		set_background_color(clear_color);
		
		const glm::uvec2 size = terminal.get_size();

		for (uint32_t y = 0; y < size.y; y++) {
			for (uint32_t x = 0; x < size.x; x++) {
				float horizontal_coeff = static_cast<float>(x) / size.x;
				horizontal_coeff = 2.0f * horizontal_coeff - 1.0f;

				float vertical_coeff = static_cast<float>(y) / size.y;
				vertical_coeff = 2.0f * vertical_coeff - 1.0f;

				vertical_coeff *= static_cast<float>(size.y) / (0.5f * size.x);

				const glm::vec3 direction = glm::normalize(
					camera.get_forward() + horizontal_coeff * camera.get_right() + vertical_coeff * camera.get_up()
				);

				const Ray ray{ camera.get_position(), direction };
                const std::optional<Sample> ray_tracing_result = ray_tracing(ray, shapes, light);

				if (ray_tracing_result.has_value()) {
                    const Sample sample = ray_tracing_result.value();
                    const glm::vec3 light_direction = glm::normalize(light.get_origin() - sample.position);

					const auto [color, brightness] = blinn_phong(sample, light_direction, ray.direction);
					draw_character(color, brightness);
				} else {
					std::cout << ' ';
				}
			}

			std::cout << '\n';
		}

		std::flush(std::cout);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		set_text_color(Color::reset);
		set_background_color(ClearColor::reset);
	}

	void Renderer::set_clear_color(ClearColor clear_color) {
		this->clear_color = clear_color;
	}

    std::optional<Sample> Renderer::ray_tracing(const Ray& ray, const std::vector<std::unique_ptr<Shape>>& shapes, const Light& light) {
        float closest_distance = std::numeric_limits<float>::infinity();
        Sample closest_sample;

        if (light.is_visible()) {
            std::optional<Sample> intersection_result = light.intersect(ray);
            if (intersection_result.has_value()) {
                closest_sample = intersection_result.value();
                closest_distance = closest_sample.distance;
            }
        }

        for (const std::unique_ptr<Shape>& shape : shapes) {
            std::optional<Sample> intersection_result = shape->intersect(ray);
            if (!intersection_result.has_value()) continue;

            const Sample sample = intersection_result.value();
            if (sample.distance < closest_distance) {
				closest_distance = sample.distance;
                closest_sample = sample;
            }
        }

        if (closest_distance == std::numeric_limits<float>::infinity()) {
            return std::nullopt;
        }

        return closest_sample;
    }

	std::pair<Color, float> Renderer::blinn_phong(const Sample& sample, const glm::vec3& light_direction, const glm::vec3& view_direction) {
		const glm::vec3& normal = sample.normal;
		const float brightness = sample.brightness;

		// ambient
		const float ambient = 0.05f * brightness;

		// diffuse
		const float light_dot_normal = glm::dot(light_direction, normal);
		const float diffuse_factor = glm::max(light_dot_normal, 0.0f);
		const float diffuse = diffuse_factor * brightness;

		// specular
		float specular = 0.0f;
		if (light_dot_normal > 0.0f) {
			const glm::vec3 halfway_direction = glm::normalize(light_direction + view_direction);
			specular = glm::pow(glm::max(glm::dot(view_direction, halfway_direction), 0.0f), 64.0f);
		}

        constexpr float constant = 1.0f;
        constexpr float linear = 0.09f;
        constexpr float quadratic = 0.032f;
        const float distance = sample.distance;

        const float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

		return { sample.color, attenuation * (ambient + diffuse + specular) };
	}

	void Renderer::draw_character(Color color, float brightness) {
		using namespace std::string_literals;

		static constexpr std::array<float, 92> brightness_levels = { 0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999 };
		static constexpr const char* chars = " `.-':_,^=;><+!rc*/z?s_l_tv)j7(|fi{c}f_i31tlu[neo_z5_yxjya]2e_swqk_p6h9d4_vp_o_gb_uakx_hm8rd#$bg0mnwq%&@";

		set_text_color(color);

		const auto it = std::lower_bound(brightness_levels.begin(), brightness_levels.end(), brightness);
		if (it == brightness_levels.end()) {
			std::cout << chars[brightness_levels.size() - 1];
		}

		const size_t index = std::distance(brightness_levels.begin(), it);
		std::cout << chars[index];
	}
}
