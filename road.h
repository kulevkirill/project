#include <SFML/Graphics.hpp>
#include <vector>

class Segment {
private:
	sf::ConvexShape roadbed; 
	sf::ConvexShape kerbLeft;
	sf::ConvexShape kerbRight; 
	sf::ConvexShape background;

	sf::Vector2f segmentStart;
	static int roadLength;

	float segmentWidth;
	float segmentHeight;

	float curve;
	float hill;

	float visualHeight;

	const float distanceCoeff = 0.90;
	const float curveCoeff = 0.0001;
	const float hillCoeff = 0.01;

public:
	float getDistanceCoeff() const;
	float getCurveCoeff() const;
	float getHillCoeff() const;

	Segment(sf::Vector2f segmentStart, float width, float height, int curve, int hill);
	Segment(int curve, int hill);

	void updateSegment(Segment newSegment);
	void changeSegment(const Segment& newSegment);

	void drawSegment(sf::RenderWindow& window);
	
	int getRealCurve() const;
	float getRealHill() const;

	void changeHill(float hill);

	float getSegmentHighestPoint();
};

class Road {
private:
	float roadWidth;
	float roadHeight;
	
	sf::Vector2f roadStart;
	std::vector<Segment> road;

	std::vector<Segment>::iterator iter;
	int currentSegment;

	const int nSegmentsToDraw = 85;

public:
	Road(sf::Vector2f roadStart, float roadWidth, float roadHeight);

	void changeRoad(int roadLength, int curve, int hill);
	void updateRoad();

	void drawRoad(sf::RenderWindow& window);
	
	int getNSegmentsToDraw() const;
};