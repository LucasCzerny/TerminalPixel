#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

// Quaternions are still experimental :o
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace tp {

	glm::vec3 Camera::get_forward() const {
		return glm::rotate(glm::quat(rotation), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 Camera::get_right() const {
		return glm::rotate(glm::quat(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::get_up() const {
		return glm::rotate(glm::quat(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::set_position(const glm::vec3& position) {
		this->position = position;
	}

	void Camera::change_position(const glm::vec3& change) {
		position += change;
	}

	glm::vec3 Camera::get_position() const {
		return position;
	}

	void Camera::set_rotation(const glm::vec3& rotation) {
		this->rotation = rotation;
	}

	void Camera::change_rotation(const glm::vec3& change) {
		rotation += change;
	}

	glm::vec3 Camera::get_rotation() const {
		return rotation;
	}
}