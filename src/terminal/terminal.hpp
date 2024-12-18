#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace tp {

	class Terminal {
	public:
		Terminal();

		bool is_open() const;

		glm::uvec2 get_size() const;

	private:
		void instantiate_new_terminal();
	};
}