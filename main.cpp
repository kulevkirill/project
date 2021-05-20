#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "game.hpp"



int main() {
	int width = 1280, height = 720;

	int points = 0;
	int maxPoints = 0;

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

	camera.changeCamZ(380);


	while (window.isOpen())
	{

		double dt = clock.getElapsedTime().asSeconds();
		//double dt = 1 / fps;
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

			sf::Font font;
			font.loadFromFile("images\\font.otf");

			std::string results = "RESULT: " + std::to_string(points);
			sf::Text result(results, font);
			result.setFillColor(sf::Color::White);
			result.setPosition(20, 300);

			std::string recordValue = "RECORD: " + std::to_string(maxPoints);
			sf::Text record(recordValue, font);
			record.setFillColor(sf::Color::White);
			record.setPosition(20, 400);

			

			if (sf::IntRect(423, 293, 435, 65).contains(sf::Mouse::getPosition(window))) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					player.returnToLife();

					camera.changeCamX(0);
					camera.changeCamZ(380);

					clock.restart();	
				}
			}

			if (sf::IntRect(423, 464, 435, 65).contains(sf::Mouse::getPosition(window))) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
					return 0;		
				}
			}

			window.draw(youDiedSprite);
			window.draw(result);
			window.draw(record);

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

		if (!player.getIsDead()) {
			double newCamZ = camera.getCamZ() + dz;
			camera.changeCamZ(newCamZ);
		}

		double newSpeed = player.getSpeed() +  dt * 10;

		if (newSpeed < 500) {
			player.changeSpeed(newSpeed);
		}

		std::cout << camera.getCamZ() << std::endl;


		if ((player.isWallSoon(camera, road)) && (!player.getIsJumping())) {
			points = (int) camera.getCamZ();
			if (points > maxPoints) {
				maxPoints = points;
			}

			player.changeSpeed(200);

			camera.changeCamX(0);
			camera.changeCamZ(380);
			player.die();
		}

		if ((camera.getCamX() < -105) || (camera.getCamX() > 100)) {
			points = (int) camera.getCamZ();
			if (points > maxPoints) {
				maxPoints = points;
			}

			player.changeSpeed(200);

			camera.changeCamX(0);
			camera.changeCamZ(380);
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
