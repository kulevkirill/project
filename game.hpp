#include <SFML/Graphics.hpp>
#include <vector>



class Camera {
private:
	double camX;
	double camY;
	double camZ;
	double d;

public:
	Camera();

	Camera(double newCamX, double newCamY, double newCamZ, double newD);

	double getCamX() const;
	double getCamY() const;
	double getCamZ() const;
	double getD() const;

	void changeCamX(double newCamX);
	void changeCamY(double newCamY);
	void changeCamZ(double newCamZ);

	sf::Vector2f projection(const sf::Vector3f point3D, int width, int height) const;
};


class Segment {
private:
	sf::Vector3f center;

	double segWidth;
	double segLength;

	bool isWall;
public:
	Segment(const sf::Vector3f& centerPoint, double width, double length, bool wall);

	double getSegmentWidth() const;
	double getSegmentLength() const;
	bool getIsWall() const;

	sf::Vector3f getPoint0() const;
	sf::Vector3f getPoint1() const;
	sf::Vector3f getPoint2() const;
	sf::Vector3f getPoint3() const;

	sf::Vector3f getNextCenter() const;

	void drawSegment(sf::RenderWindow& window, const Camera& camera, sf::Color color, int width, int height) const;
};


class Road {
private:
	std::vector<Segment> road;

	int roadLength;
public:
	Road(int roadLen, double segmentWidth, double segmentLength);

	std::vector<Segment> getRoad() const;

	int getRoadLength() const;
	double getRoadSegmentWidth() const;

	void drawRoad(sf::RenderWindow& window, const Camera& camera, sf::Color color1, sf::Color color2, int width, int height) const;
};


class Player {
private:
	int xPosition;
	int yPosition;

	double speed;
	double maxSpeed;

	double accel;
	double brake;

	double decel;
	double decelOffGround;

	sf::Texture playerTexture;
	sf::Texture shootTexture;

	double xShoot;
	double yShoot;

	int jumpAnimationStage;

	bool isJumping;

	bool isDead;
public:
	Player();

	double getSpeed() const;
	double getMaxSpeed() const;
	bool getIsJumping() const;
	bool getIsDead() const;

	void changeSpeed(double newSpeed);

	void accelerate(double dt);
	void specialMovement(double dt);
	void braking(double dt);
	void decelerate(double dt, const Camera& camera, const Road& road);

	void drawPlayer(sf::RenderWindow& window);
	void drawShoot(sf::RenderWindow& window);

	void jump();
	void jumping();

	void die();
	void returnToLife();

	bool isWallSoon(const Camera& camera, const Road& road) const;
	double coordinateOnCurrentSegment(const Camera& camera, const Road& road) const;
};
