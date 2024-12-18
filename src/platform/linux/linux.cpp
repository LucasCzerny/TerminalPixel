#ifndef TPIXEL_LINUX // TODO: should be ifdef but dis shit doesnt work

#include "platform/terminal_util.hpp"

#include <iostream>
#include <format>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace tp::platform {

	glm::uvec2 get_terminal_size() {
		winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

		return glm::uvec2(
			static_cast<std::uint32_t>(size.ws_col),
			static_cast<std::uint32_t>(size.ws_row)
		);
	}

	void clear() {
		std::system("clear");
	}

	void new_frame() {
		const unsigned int y = get_terminal_size().y;
		std::cout << std::format("\033[{}A", y);
	}
}

#endif
