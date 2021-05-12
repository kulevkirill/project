#include <SFML/Graphics.hpp>
#include <vector>
#include "game.hpp"


Camera::Camera() {
	camX = 0.0;
	camY = 150.0;
	camZ = - 0.5;

	d = 0.82;
}

Camera::Camera(double newCamX, double newCamY, double newCamZ, double newD) {
	camX = newCamX;
	camY = newCamY;
	camZ = newCamZ;

	d = newD;		
}

double Camera::getCamX() const {
	return camX;
}

double Camera::getCamY() const {
	return camX;
}

double Camera::getCamZ() const {
	return camZ;
}

double Camera::getD() const {
	return d;
}

void Camera::changeCamX(double newCamX) {
	camX = newCamX;
}

void Camera::changeCamY(double newCamY) {
	camY = newCamY;
}

void Camera::changeCamZ(double newCamZ) {
	camZ = newCamZ;
}

sf::Vector2f Camera::projection(const sf::Vector3f point3D, int width, int height) const {
	double x = point3D.x;
	double y = point3D.y;
	double z = point3D.z;

	double xCam = x - camX;
	double yCam = y - camY;
	double zCam = z - camZ;

	double xProjection = xCam * d / zCam;
	double yProjection = yCam * d / zCam;

	double xScreen = width / 2 + (width / 2) * xProjection;
	double yScreen = height / 2 - (height / 2) * yProjection;

	sf::Vector2f point2D(xScreen, yScreen);

	return point2D;
}



Segment::Segment(const sf::Vector3f& centerPoint, double width, double length) {
	center = centerPoint;
	segWidth = width;
	segLength = length;
}

double Segment::getSegmentWidth() const {
	return segWidth;
}

double Segment::getSegmentLength() const {
	return segLength;
}

sf::Vector3f Segment::getPoint0() const {
	sf::Vector3f point0;

	point0.x = center.x - segWidth / 2;
	point0.y = center.y;
	point0.z = center.z;

	return point0;
}

sf::Vector3f Segment::getPoint1() const {
	sf::Vector3f point1;

	point1.x = center.x - segWidth / 2;
	point1.y = center.y;
	point1.z = center.z + segLength;

	return point1;
}

sf::Vector3f Segment::getPoint2() const {
	sf::Vector3f point2;

	point2.x = center.x + segWidth / 2;
	point2.y = center.y;
	point2.z = center.z + segLength;

	return point2;
}

sf::Vector3f Segment::getPoint3() const {
	sf::Vector3f point3;

	point3.x = center.x + segWidth / 2;
	point3.y = center.y;
	point3.z = center.z;

	return point3;
}

void Segment::drawSegment(sf::RenderWindow& window, const Camera& camera, sf::Color color, int width, int height) const {
	sf::ConvexShape shape(4);

	shape.setFillColor(color);

	sf::Vector2f point0 = camera.projection(this->getPoint0(), width, height);
	sf::Vector2f point1 = camera.projection(this->getPoint1(), width, height);
	sf::Vector2f point2 = camera.projection(this->getPoint2(), width, height);
	sf::Vector2f point3 = camera.projection(this->getPoint3(), width, height);

	if ((point0.y < height / 2) || (point1.y < height / 2) || (point2.y < height / 2) || (point3.y < height / 2)) {
		return;
	}

	shape.setPoint(0, point0);	
	shape.setPoint(1, point1);
	shape.setPoint(2, point2);
	shape.setPoint(3, point3);

	window.draw(shape);
}

sf::Vector3f Segment::getNextCenter() const {
	sf::Vector3f nextCenter;

	nextCenter.x = center.x;
	nextCenter.y = center.y;
	nextCenter.z = center.z + segLength;

	return nextCenter;
}



Road::Road(int roadLen, double segmentWidth, double segmentLength) {
	roadLength = roadLen;

	sf::Vector3f center(0, 0, 0);
	for (int i = 0; i < roadLength; i++) {
		Segment newSegment(center, segmentWidth, segmentLength);
		road.push_back(newSegment);

		center = newSegment.getNextCenter();
	}
}

int Road::getRoadLength() const {
	return roadLength;
}

double Road::getRoadSegmentWidth() const {
	return road.at(0).getSegmentWidth();
}

void Road::drawRoad(sf::RenderWindow& window, const Camera& camera, sf::Color color1, sf::Color color2, int width, int height) const {
	for (int i = 0; i < roadLength; i++) {
		sf::Color color;
		if (i % 2) {
			color = color1;
		} else {
			color = color2;
		}
		
		(road.at(i)).drawSegment(window, camera, color, width, height);
	}
}


Player::Player() {
	speed = 200;
	maxSpeed = 2000;

	accel = 500;
	brake = 800;

	decel = 100;
	decelOffGround = 1400;
		
	playerTexture.loadFromFile("images\\playerSprite.png");
	shootTexture.loadFromFile("images\\shootSprite.png");
}

double Player::getSpeed() const {
	return speed;
}

double Player::getMaxSpeed() const {
	return maxSpeed;
}

void Player::accelerate(double dt) {
	double dv = accel * dt;
	speed += dv;

	if (speed > maxSpeed) {
		speed = maxSpeed;
	}
}

void Player::braking(double dt) {
	double dv = brake * dt;
	speed -= dv;

	if (speed < 0) {
		speed = 0;
	}
}

void Player::decelerate(double dt, const Camera& camera, const Road& road) {
	double realDecel = decel;

	if ((camera.getCamX() > road.getRoadSegmentWidth() / 2) || (camera.getCamX() < - road.getRoadSegmentWidth() / 2)) {
		realDecel = decelOffGround;

		if (speed < maxSpeed / 10) {
			realDecel = decel;
		}
	}

	double dv = realDecel * dt;
	speed -= dv;

	if (speed < 0) {
		speed = 0;
	}
}

void Player::drawPlayer(sf::RenderWindow& window) {
	sf::Sprite playerSprite(playerTexture);
	playerSprite.setPosition(500, 400);

	window.draw(playerSprite);
}

void Player::drawShoot(sf::RenderWindow& window) {
	sf::Sprite shootSprite(shootTexture);

	double xShoot = 670;
	double yShoot = 450;

	shootSprite.setPosition(xShoot, yShoot);

	window.draw(shootSprite);
}
