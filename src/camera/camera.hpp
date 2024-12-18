#pragma once

#include <glm/glm.hpp>

namespace tp {

	class Camera {
	public:
		Camera(const glm::vec3& position, const glm::vec3& rotation)
			: position(position), rotation(rotation) {}

		glm::vec3 get_forward() const;
		glm::vec3 get_right() const;
		glm::vec3 get_up() const;

		void set_position(const glm::vec3& position);
		void change_position(const glm::vec3& change);
		glm::vec3 get_position() const;

		void set_rotation(const glm::vec3& rotation);
		void change_rotation(const glm::vec3& change);
		glm::vec3 get_rotation() const;

	private:
		glm::vec3 position, rotation;
	};
}