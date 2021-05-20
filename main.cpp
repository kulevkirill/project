#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "game.hpp"



int main() {
	int width = 1280, height = 720;

	int segmentWidth = 200, segmentLength = 100;
	sf::Vector3f pnt(0, 0, 0);


	sf::RenderWindow window(sf::VideoMode(width, height), "DOOM I");


	int fps = 60;
	window.setFramerateLimit(fps);


	Camera camera;

	Player player;

	Road road(2000, segmentWidth, segmentLength);

	sf::Clock clock;


	bool isMenu = true;
	sf::Texture menuTexture;
	menuTexture.loadFromFile("images\\newMenu.png");
	sf::Sprite menuSprite(menuTexture);
	menuSprite.setPosition(0, 0);


	sf::Texture youDiedTexture;
	youDiedTexture.loadFromFile("images\\youDied.png");
	sf::Sprite youDiedSprite(youDiedTexture);
	youDiedSprite.setPosition(0, 0);


	while (window.isOpen())
	{

		double dt = clock.getElapsedTime().asSeconds();
		double dz = player.getSpeed() * dt;

		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (player.getIsDead()) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (sf::IntRect(423, 293, 435, 65).contains(sf::Mouse::getPosition(window))) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					player.returnToLife();		
				}
			}

			if (sf::IntRect(423, 464, 435, 65).contains(sf::Mouse::getPosition(window))) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
					return 0;		
				}
			}

			window.draw(youDiedSprite);
			window.display();
			window.clear();
		}

		while (isMenu) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (sf::IntRect(423, 293, 435, 65).contains(sf::Mouse::getPosition(window))) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					isMenu = false;
					break;		
				}
			}

			if (sf::IntRect(423, 464, 435, 65).contains(sf::Mouse::getPosition(window))) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
					return 0;		
				}
			}

			window.draw(menuSprite);
			window.display();
			window.clear();
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.jump();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			double newCamX = camera.getCamX() + dz / 10;
			camera.changeCamX(newCamX);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			double newCamX = camera.getCamX() - dz / 10;
			camera.changeCamX(newCamX);
		}
		
		bool isWall = player.isWallSoon(camera, road);
		player.jumping();

		double newCamZ = camera.getCamZ() + dz;
		camera.changeCamZ(newCamZ);

		double newSpeed = player.getSpeed() + player.getSpeed() * dt;

		//if (newSpeed < 500) {
		//	player.changeSpeed(newSpeed);
		//}


		if ((player.isWallSoon(camera, road)) && (!player.getIsJumping())) {
			player.die();
		}


		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("images\\background.png");
		sf::Sprite backgroundSprite(backgroundTexture);
		window.draw(backgroundSprite);


		road.drawRoad(window, camera, sf::Color::Green, sf::Color::Yellow, width, height);
		player.drawPlayer(window);

		window.display();
		window.clear();
	}

	return 0;
}
