#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Point2D {
private:
	int x;
	int y;

public:
	Point2D() {
		x = 0;
		y = 0;
	}

	Point2D(int fisrtCoordinate, int secondCoordinate) {
		x = fisrtCoordinate;
		y = secondCoordinate;
	}


	int getXcoordinate() const {
		return x;
	}

	int getYcoordinate() const {
		return y;
	}

	void changeXcoordinate(int newX) {
		x = newX;
	}

	void changeYcoordinate(int newY) {
		y = newY;
	}

	Point2D& operator=(const Point2D& point1) {
		x = point1.getXcoordinate();
		y = point1.getYcoordinate();

		return *this;
	}

};

class Segment {
private:
	sf::Color color;

	Point2D point1;
	int w1;

	Point2D point2;
	int w2;

public:
	Segment() {
		color = sf::Color::Green;

		Point2D pt1(0, 0);
		point1 = pt1;
		w1 = 0;

		Point2D pt2(0, 0);
		point2 = pt2;
		w2 = 0;
	}

	Segment(sf::Color c, const Point2D& pt1, int wd1, const Point2D& pt2, int wd2) {
		color = c;

		point1 = pt1;
		w1 = wd1;

		point2 = pt2;
		w2 = wd2;
	}

	Point2D getPoint1() const {
		return point1;
	}

	Point2D getPoint2() const {
		return point2;
	}

	int getWidth1() const {
		return w1;
	}

	int getWidth2() const {
		return w2;
	}

	void changePoint1(const Point2D& new_pt1) {
		point1 = new_pt1;
	}

	void changePoint2(const Point2D& new_pt2) {
		point2 = new_pt2;
	}

	void changeWidth1(int new_w1) {
		w1 = new_w1;
	}

	void changeWidth2(int new_w2) {
		w2 = new_w2;
	}

	Segment& operator=(const Segment& segment1) {
		point1 = segment1.getPoint1();
		point2 = segment1.getPoint2();

		w1 = segment1.getWidth1();
		w2 = segment1.getWidth2();

		return *this;
	}

	void drawSegment(sf::RenderWindow& window) const {
		sf::ConvexShape shape(4);

		shape.setFillColor(color);

		int x1 = point1.getXcoordinate();
		int y1 = point1.getYcoordinate();
		int x2 = point2.getXcoordinate();
		int y2 = point2.getYcoordinate();


		shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
		shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
		shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
		shape.setPoint(3, sf::Vector2f(x1 + w1, y1));

		window.draw(shape);
	}
};

class Player {
private:
	double speed;
	double maxSpeed;
	double playerX;
	double playerY;
public:
	Player () {
		speed = 100;
		maxSpeed = 100;
		playerX = 0;
		playerY = 0;
	}

	double getSpeed() const {
		return speed;
	}

	double getMaxSpeed() const {
		return maxSpeed;
	}

	double getPlayerX() const {
		return playerX;
	}

	double getPlayerY() const {
		return playerY;
	}

	void changePlayerX(int newX) {
		playerX = newX;
	}

	void changePlayerY(int newY) {
		playerY = newY;
	}
};

class Road {
private:
	int roadLength;
	int segmentLength;
	std::vector<Segment> segments;
public:
	Road(int width, int height, int horizonLine) {
		segmentLength = 50;
		roadLength = 100;

		segments = {};

		int x1 = width / 2;
		int y1 = height;
		int w1 = 1.5 * width;

		Point2D point1(x1, y1);

		double coef1 = 1 - (double) segmentLength / (double) (height - horizonLine);
		double coef2 =  w1 / (height - horizonLine);

		int x2 = x1;
		double deltaY = segmentLength;
		double y2_f = height - deltaY;
		int y2 = y2_f;
		int w2 = coef2 * (y2_f - horizonLine);

		Point2D point2(x2, y2);
	
		Segment segment(sf::Color(40, 114, 51), point1, w1, point2, w2);
		segments.push_back(segment);

		for (int i = 1; i < 100; i++) {
			x1 = x2;
			y1 = y2;
			w1 = w2;

			Point2D point1(x1, y1);

			x2 = x1;
			deltaY *= coef1;
			y2_f -= deltaY;
			w2 = coef2 * (y2_f - horizonLine);
			y2 = y2_f;

			Point2D point2(x2, y2);

			//if (y2 < horizonLine) {
			//	break;
			//}
			if (i % 2) {
				Segment segment(sf::Color(40, 114, 51), point1, w1, point2, w2);
				segments.push_back(segment);
			}
			else {
				Segment segment(sf::Color(131, 245, 44), point1, w1, point2, w2);
				segments.push_back(segment);
			}
		}
	}

	int getRoadLength() const {
		return roadLength;
	}

	int getSegmentLength() const {
		return segmentLength;
	}

	std::vector<Segment> getSegments() const {
		return segments;
	}

	void changeRoad(const std::vector<Segment>& new_road, int segL) {
		segments = new_road;
		roadLength = new_road.size();
		segmentLength = segL;
	}

	void drawRoad(sf::RenderWindow& window) const {
		for (int i = 0; i < roadLength; i++) {
			(segments.at(i)).drawSegment(window);
		}
	}

	void drawBackground(sf::RenderWindow& window, int width, int height, int horizonLine) {
		Point2D pt1(width / 2, height);
		Point2D pt2(width / 2, horizonLine);

		Segment background(sf::Color(155, 118, 83), pt1, width / 2, pt2, width / 2);

		background.drawSegment(window);
	}

	void updateRoad(Player& player, double dy, int width, int height, int horizonLine) {
		if (player.getPlayerY() + dy > segmentLength) {
			Road new_road(width, height, horizonLine);
			changeRoad(new_road.getSegments(), segmentLength);
			player.changePlayerY(dy + player.getPlayerY() - segmentLength);
		}
		else {
			player.changePlayerY(player.getPlayerY() + dy);
		}



		double coef1 = 1 - (double) segmentLength / (double) (height - horizonLine);
		//double coef2 = (double) 1.5 * width / (double) (height - horizonLine);

		std::vector<Segment> new_road;
		Segment currentSegment = segments[0];
		Point2D point2 = currentSegment.getPoint2();

		int newY2coordinate = point2.getYcoordinate() + dy;
		point2.changeYcoordinate(newY2coordinate);
		
		//currentSegment.changeWidth2(newY2coordinate * coef2);
		currentSegment.changePoint2(point2);

		new_road.push_back(currentSegment);

		for (int i = 1; i < roadLength; i++) {
			Segment currentSegment = segments[i];
			Point2D point1 = currentSegment.getPoint1();
			Point2D point2 = currentSegment.getPoint2();

			int newY1coordinate = point1.getYcoordinate() + dy;
			dy *= coef1;
			int newY2coordinate = point2.getYcoordinate() + dy;
			
			point1.changeYcoordinate(newY1coordinate);
			point2.changeYcoordinate(newY2coordinate);

			currentSegment.changePoint1(point1);
			//currentSegment.changeWidth1(newY1coordinate * coef2);

			currentSegment.changePoint2(point2);
			//currentSegment.changeWidth2(newY2coordinate * coef2);

			new_road.push_back(currentSegment);
		}

		this->changeRoad(new_road, segmentLength);
	}
};


int main() {
	int fps = 60;

	int width = 1024;
	int height = 768;

	int horizonLine = height / 2;

	Road road(width, height, horizonLine);

	Player player;

	sf::RenderWindow window(sf::VideoMode(width, height), "Outrun Racing!");
	window.setFramerateLimit(fps);
	double dy = 0;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dy += 1;
			if (dy > 50) {
				dy -= 50;
			}
		}


		road.updateRoad(player, dy, width, height, horizonLine);

		road.drawBackground(window, width, height, horizonLine);
		road.drawRoad(window);

		window.display();
		window.clear();
	}

	return 0;
}