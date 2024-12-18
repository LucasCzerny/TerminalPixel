#include "box.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace tp {

	std::optional<Sample> Box::intersect(const Ray& ray) const {
        const glm::mat4 transform = calculate_transform();
        const glm::mat4 inverse = glm::inverse(transform);

        const Ray transformed_ray = {
            inverse * glm::vec4(ray.origin, 1.0f),
            glm::normalize(inverse * glm::vec4(ray.direction, 0.0f))
        };

        const std::optional<std::pair<float, glm::vec3>> intersection_result = intersect_local_space(transformed_ray);
        if (!intersection_result.has_value()) return std::nullopt;

        const auto [local_distance, local_normal] = intersection_result.value();

        const glm::vec3 local_intersection_point = transformed_ray.origin + local_distance * transformed_ray.direction;
        const glm::vec3 intersection_point = glm::vec3(transform * glm::vec4(local_intersection_point, 1.0f));

        const float distance = glm::length(intersection_point - ray.origin);
        const glm::vec3 normal = glm::normalize(glm::mat3(glm::transpose(inverse)) * local_normal);

        return Sample{
            distance,
            intersection_point, normal,
            color, brightness
        };
	}

    BoundingBox Box::get_bounding_box() const {
        return {};
    }

    glm::mat4 Box::calculate_transform() const {
        return glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), scale)
            * glm::toMat4(glm::quat(rotation));
    }

    std::optional<std::pair<float, glm::vec3>> Box::intersect_local_space(const Ray& ray) const {
        float t_min = 0.0f, t_max = std::numeric_limits<float>::max();
        glm::vec3 hit_normal(0.0f);

        for (int i = 0; i < 3; ++i) {
            if (std::abs(ray.direction[i]) < 1e-6) {
                if (ray.origin[i] < -0.5f || ray.origin[i] > 0.5f) {
                    return std::nullopt;
                }
            } else {
                float t1 = (-0.5f - ray.origin[i]) / ray.direction[i];
                float t2 = (0.5f - ray.origin[i]) / ray.direction[i];

                if (t1 > t2) std::swap(t1, t2);

                if (t1 > t_min) {
                    t_min = t1;
                    hit_normal = glm::vec3(0.0f);
                    hit_normal[i] = (ray.direction[i] > 0.0f) ? -1.0f : 1.0f; // Determine the normal direction
                }
                t_max = std::min(t_max, t2);

                if (t_min > t_max) {
                    return std::nullopt;
                }
            }
        }

        return std::make_pair(t_min, hit_normal);
    }
}