#pragma once

#include <glm/glm.hpp>

namespace tp::platform {

	glm::uvec2 get_terminal_size();

	void clear();
	void new_frame();
}