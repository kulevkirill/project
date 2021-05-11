#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "road.h"


int main() {
	int width = 1440;
	int height = 900;

	sf::RenderWindow window(sf::VideoMode(width, height), "Racing");
	Road road(sf::Vector2f(720, 975), 1540, 25);

	int hill = 0;
	int curve = 0;

	road.changeRoad(100, 0, 100);

	for (int i = 0; i < 1000; i++) {
		hill = (sin((i * 5) * M_PI / 180.0) * 250);
		hill += 200;
		curve = (sin((i * 3) * M_PI / 180.0) * 100);
		road.changeRoad(3, curve, hill);
	}

	int fps = 30;
	window.setFramerateLimit(fps);

	double dy = 0;
	double dt = 1.0 / fps;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			road.updateRoad();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				road.updateRoad();
			}
		}


		window.clear();
		road.drawRoad(window);
		window.display();
	}

	return 0;
}