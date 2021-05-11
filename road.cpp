#include "road.h"


/////////////////////////////////////// Segment

int Segment::roadLength = 0;

Segment::Segment(sf::Vector2f segmentStart, float width, float height, int curve, int hill) {
	sf::ConvexShape newRoadbed(4);
	sf::ConvexShape newKerbLeft(4);
	sf::ConvexShape newKerbRight(4);
	sf::ConvexShape newBackground(4);

	roadbed = newRoadbed;
	kerbLeft = newKerbLeft;
	kerbRight = newKerbRight;
	background = newBackground;


	segmentWidth = width;
	segmentHeight = height;

	this->curve = curve * curveCoeff;
	this->hill = hill * hillCoeff;

	float kerbWidth = width / 10.0;

	roadbed.setPoint(0, sf::Vector2f(segmentStart.x - (width / 2.0), segmentStart.y));
	roadbed.setPoint(1, sf::Vector2f(segmentStart.x - ((width / 2.0) * distanceCoeff), segmentStart.y - (segmentHeight * this->hill)));
	roadbed.setPoint(2, sf::Vector2f(segmentStart.x + ((width / 2.0) * distanceCoeff), segmentStart.y - (segmentHeight * this->hill)));
	roadbed.setPoint(3, sf::Vector2f(segmentStart.x + (width / 2.0), segmentStart.y));

	float curveOffset = roadbed.getPoint(1).x * curve;

	roadbed.setPoint(1, sf::Vector2f(curveOffset + roadbed.getPoint(1).x, roadbed.getPoint(1).y));
	roadbed.setPoint(2, sf::Vector2f(curveOffset + roadbed.getPoint(2).x, roadbed.getPoint(2).y));

	kerbLeft.setPoint(0, sf::Vector2f(roadbed.getPoint(0).x - kerbWidth, roadbed.getPoint(0).y));
	kerbLeft.setPoint(1, sf::Vector2f(roadbed.getPoint(1).x - (kerbWidth * distanceCoeff), roadbed.getPoint(1).y));
	kerbLeft.setPoint(2, roadbed.getPoint(1));
	kerbLeft.setPoint(3, roadbed.getPoint(0));

	kerbRight.setPoint(3, sf::Vector2f(roadbed.getPoint(3).x + kerbWidth, roadbed.getPoint(3).y));
	kerbRight.setPoint(2, sf::Vector2f(roadbed.getPoint(2).x + (kerbWidth * distanceCoeff), roadbed.getPoint(2).y));
	kerbRight.setPoint(1, roadbed.getPoint(2));
	kerbRight.setPoint(0, roadbed.getPoint(3));

	background.setPoint(0, sf::Vector2f(segmentStart.x - 9000.0, segmentStart.y));
	background.setPoint(1, sf::Vector2f(segmentStart.x - 9000.0, segmentStart.y - (segmentHeight * distanceCoeff)));
	background.setPoint(2, sf::Vector2f(segmentStart.x + 9000.0, segmentStart.y - (segmentHeight * distanceCoeff)));
	background.setPoint(3, sf::Vector2f(segmentStart.x + 9000.0, segmentStart.y));

	if (Segment::roadLength % 2 == 0) {
		roadbed.setFillColor(sf::Color(100, 100, 100));
		kerbLeft.setFillColor(sf::Color(255, 0, 0));
		kerbRight.setFillColor(sf::Color(255, 255, 255));
	}
	else {
		roadbed.setFillColor(sf::Color(100, 100, 100));
		kerbLeft.setFillColor(sf::Color(255, 255, 255));
		kerbRight.setFillColor(sf::Color(255, 0, 0));
	}

	Segment::roadLength++;
}

Segment::Segment(int curve, int hill) {
	sf::ConvexShape newRoadbed(4);
	sf::ConvexShape newKerbLeft(4);
	sf::ConvexShape newKerbRight(4);
	sf::ConvexShape newBackground(4);

	roadbed = newRoadbed;
	kerbLeft = newKerbLeft;
	kerbRight = newKerbRight;
	background = newBackground;

	Segment::roadLength++;

	this->curve = curve * curveCoeff;
	this->hill = hill * hillCoeff;

	if (Segment::roadLength % 20 <= 9) {
		//std::cout << "1: "<< Segment::roadLength << std::endl;
		roadbed.setFillColor(sf::Color(100, 100, 100));
		kerbLeft.setFillColor(sf::Color(255, 0, 0));
		kerbRight.setFillColor(sf::Color(255, 255, 255));
		background.setFillColor(sf::Color(0, 150, 0));
	}
	else {
		//std::cout << "2: "<< Segment::roadLength << std::endl;
		roadbed.setFillColor(sf::Color(97, 97, 97));
		kerbLeft.setFillColor(sf::Color(255, 255, 255));
		kerbRight.setFillColor(sf::Color(255, 0, 0));
		background.setFillColor(sf::Color(0, 130, 0));
	}
}


void Segment::updateSegment(Segment newSegment) {
	segmentWidth = (newSegment.roadbed.getPoint(2).x - newSegment.roadbed.getPoint(1).x);
	segmentHeight = newSegment.segmentHeight * distanceCoeff;

	float kerbWidth = segmentWidth / 10.0;

	visualHeight =  segmentHeight * hill;

	segmentStart.x = (newSegment.roadbed.getPoint(2).x + newSegment.roadbed.getPoint(1).x) / 2.0;
	segmentStart.y = newSegment.roadbed.getPoint(1).y;
	

	roadbed.setPoint(0, sf::Vector2f(segmentStart.x - (segmentWidth / 2.0), segmentStart.y));
	roadbed.setPoint(1, sf::Vector2f(segmentStart.x - ((segmentWidth / 2.0) * distanceCoeff), segmentStart.y - visualHeight));
	roadbed.setPoint(2, sf::Vector2f(segmentStart.x + ((segmentWidth / 2.0) * distanceCoeff), segmentStart.y - visualHeight));
	roadbed.setPoint(3, sf::Vector2f(segmentStart.x + (segmentWidth / 2.0), segmentStart.y));

	float curveOffset;
	if (curve < 0) {
		curveOffset = (roadbed.getPoint(1).x + (segmentWidth / 2.0)) * curve;
	} else {
		curveOffset = (roadbed.getPoint(1).x - (segmentWidth / 2.0)) * curve;
	}


	roadbed.setPoint(1, sf::Vector2f(curveOffset + roadbed.getPoint(1).x, roadbed.getPoint(1).y));
	roadbed.setPoint(2, sf::Vector2f(curveOffset + roadbed.getPoint(2).x, roadbed.getPoint(2).y));

	kerbLeft.setPoint(0, sf::Vector2f(roadbed.getPoint(0).x - kerbWidth, roadbed.getPoint(0).y));
	kerbLeft.setPoint(1, sf::Vector2f(roadbed.getPoint(1).x - (kerbWidth * distanceCoeff), roadbed.getPoint(1).y));
	kerbLeft.setPoint(2, roadbed.getPoint(1));
	kerbLeft.setPoint(3, roadbed.getPoint(0));

	kerbRight.setPoint(3, sf::Vector2f(roadbed.getPoint(3).x + kerbWidth, roadbed.getPoint(3).y));
	kerbRight.setPoint(2, sf::Vector2f(roadbed.getPoint(2).x + (kerbWidth * distanceCoeff), roadbed.getPoint(2).y));
	kerbRight.setPoint(1, roadbed.getPoint(2));
	kerbRight.setPoint(0, roadbed.getPoint(3));

	background.setPoint(0, sf::Vector2f(segmentStart.x - 9000.0, segmentStart.y));
	background.setPoint(1, sf::Vector2f(segmentStart.x - 9000.0, segmentStart.y - visualHeight));
	background.setPoint(2, sf::Vector2f(segmentStart.x + 9000.0, segmentStart.y - visualHeight));
	background.setPoint(3, sf::Vector2f(segmentStart.x + 9000.0, segmentStart.y));
}

void Segment::changeSegment(const Segment& newSegment) {
	for (int i = 0; i < 4; i++) {
		sf::Vector2f newRoadbed = newSegment.roadbed.getPoint(i);
		roadbed.setPoint(i, newRoadbed);

		sf::Vector2f newKerbLeft = newSegment.kerbLeft.getPoint(i);
		kerbLeft.setPoint(i, newKerbLeft);

		sf::Vector2f newKerbRight = newSegment.kerbRight.getPoint(i);
		kerbRight.setPoint(i, newKerbRight);

		sf::Vector2f newBackground = newSegment.background.getPoint(i);
		background.setPoint(i, newBackground);


		segmentHeight = newSegment.segmentHeight;
	}

}


void Segment::drawSegment(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(roadbed);
	window.draw(kerbLeft);
	window.draw(kerbRight);
}


int Segment::getRealCurve() const {
	return curve / curveCoeff;
}

float Segment::getRealHill() const {
	return hill / hillCoeff;
}

void Segment::changeHill(float hill) {
	this->hill = hill * hillCoeff;
}

float Segment::getSegmentHighestPoint() {
	return roadbed.getPoint(1).y;
}


float Segment::getDistanceCoeff() const {
	return distanceCoeff;
}

float Segment::getCurveCoeff() const {
	return curveCoeff;
}
	
float Segment::getHillCoeff() const {
	return hillCoeff;
}











///////////////////////////////////////// Road

int Road::getNSegmentsToDraw() const {
	return nSegmentsToDraw;
}

Road::Road(sf::Vector2f roadStart, float roadWidth, float roadHeight) {
	currentSegment = 0;

	this->roadStart = roadStart;
	this->roadWidth = roadWidth;
	this->roadHeight = roadHeight;

	road.push_back(Segment(roadStart, roadWidth, roadHeight, 0, 100));
}

void Road::changeRoad(int roadLength, int curve, int hill)
{
	if (curve > 100)
		curve = 100;
	else if (curve < -100)
		curve = -100;

	float currentCurve = (*(road.end() - 1)).getRealCurve();
	float curveStep;

	if (currentCurve < curve)
		curveStep = (curve - currentCurve) / (roadLength / 3);
	else if (currentCurve > curve)
		curveStep = (curve - currentCurve) / (roadLength / 3);
	else
		curveStep = 0;

	for (int i = 0; i < roadLength; i++) {
		if ((*(road.end() - 1)).getRealCurve() < curve) {
			currentCurve += curveStep;
			road.push_back(Segment(currentCurve, hill));
			(*(road.end() - 1)).updateSegment((*(road.end() - 2)));
		}
		else if ((*(road.end() - 1)).getRealCurve() > curve) {
			currentCurve += curveStep;
			road.push_back(Segment(currentCurve, hill));
			(*(road.end() - 1)).updateSegment((*(road.end() - 2)));
		}
		else {
			road.push_back(Segment(currentCurve, hill));
			(*(road.end() - 1)).updateSegment((*(road.end() - 2)));
		}
	}
}

void Road::drawRoad(sf::RenderWindow& window) {
	std::vector<Segment>::iterator iterStart = road.begin() + currentSegment + this->getNSegmentsToDraw();
	std::vector<Segment>::iterator iterEnd = road.begin() + currentSegment;

	for (iter = iterStart; iter > iterEnd; iter--) {
		(*iter).drawSegment(window);
	}
}

void Road::updateRoad() {
	currentSegment++;

	(*(road.begin() + currentSegment)).changeSegment((*(road.begin() + currentSegment - 1)));


	for (int i = 0; i < 10; i++) {
		float viewHeight = road[currentSegment + i].getRealHill() - 100;
		viewHeight *= i * (1.0 / 10.0);
		viewHeight += 100;
		road[currentSegment + i].changeHill(viewHeight);
	}

	std::vector<Segment>::iterator iterStart = road.begin() + currentSegment;
	std::vector<Segment>::iterator iterEnd = road.begin() + currentSegment + this->getNSegmentsToDraw() + 1;

	for (iter = iterStart; iter < iterEnd; iter++) {
		(*(iter + 1)).updateSegment((*iter));
	}
}