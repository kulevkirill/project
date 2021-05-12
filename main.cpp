#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "game.hpp"



int main() {
	int width = 1280, height = 720;

	int segmentWidth = 200, segmentLength = 100;
	sf::Vector3f pnt(0, 0, 0);


	sf::RenderWindow window(sf::VideoMode(width, height), "Outrun Racing!");


	int fps = 60;
	window.setFramerateLimit(fps);


	Camera camera;

	Player player;

	Road road(1000, segmentWidth, segmentLength);


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		double dt = 1.0 / fps;
		double dz = player.getSpeed() * dt;

		std::cout << dt << "   " << dz << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.accelerate(dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.braking(dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			double newCamX = camera.getCamX() + dz / 10;
			camera.changeCamX(newCamX);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			double newCamX = camera.getCamX() - dz / 10;
			camera.changeCamX(newCamX);
		}

		player.decelerate(dt, camera, road);

		double newCamZ = camera.getCamZ() + dz;
		camera.changeCamZ(newCamZ);



		road.drawRoad(window, camera, sf::Color::Green, sf::Color::Yellow, width, height);
		player.drawPlayer(window);
		//player.drawShoot(window);

		window.display();
		window.clear();
	}

	return 0;
}
