#include <iostream>
#include <memory>

#include <glm/glm.hpp>

#include "camera/camera.hpp"
#include "light/light.hpp"
#include "platform/terminal_util.hpp"
#include "renderer/renderer.hpp"
#include "shapes/sphere.hpp"
#include "shapes/box.hpp"
#include "terminal/terminal.hpp"

/*
todo:
- new_frame() ???
- actually use the bounding box (maybe)
*/

int main() {
	// the scene :o

	tp::Camera camera(
		{ 0.0f, 0.0f, 2.0f }, // right: 1, up: 1, towards the viewer: 2
		{ 0.0f, 0.0f, 0.0f }
	);

	std::vector<std::unique_ptr<tp::Shape>> penis;
    penis.reserve(3);

    // the left ball
    penis.push_back(
        std::make_unique<tp::Sphere>(
            glm::vec3(-0.5f, 0.4f, 0.0f),
            0.25f,
            tp::Color::magenta, 0.5f
        )
    );

    // the right ball
    penis.push_back(
        std::make_unique<tp::Sphere>(
            glm::vec3(0.5f, 0.4f, 0.0f),
            0.25f,
            tp::Color::magenta, 0.5f
        )
    );

    // the main event
    penis.push_back(
        std::make_unique<tp::Box>(
            glm::vec3(0.0f, -0.1f, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.0f, 0.5f),
            tp::Color::magenta, 0.5f
        )
    );

	tp::Light light(
		// sphere parameters
		{ 1.25f, 0.0f, 0.0f },
		0.1f,
		tp::Color::red, 0.75f,
		true // is visible
	);

	// important classes!!!!!!!

	tp::Terminal terminal;
	tp::Renderer renderer(camera, terminal);

	// epic render loop :o

	float light_angle = 0.0f;

	while (terminal.is_open()) {
		light_angle += glm::radians(10.0f);
		light.set_origin({ 1.25f * glm::cos(light_angle), 0.0f, 1.25f * glm::sin(light_angle) });

		renderer.draw(penis, light);
	}

	// clear the output so that the last frame isn't visible after the program terminates
	tp::platform::clear();
}
