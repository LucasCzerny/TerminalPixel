#include "terminal.hpp"

#include "platform/terminal_util.hpp"

namespace tp {

	Terminal::Terminal() {
		static bool default_terminal_used = false;

		if (!default_terminal_used) {
			default_terminal_used = true;
			return;
		}

		instantiate_new_terminal();
	}

	bool Terminal::is_open() const {
		// todo
		return true;
	}

	glm::uvec2 Terminal::get_size() const {
		return platform::get_terminal_size();
	}

	void Terminal::instantiate_new_terminal() {
		// todo
	}
}