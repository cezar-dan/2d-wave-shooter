#include "EnemyFly.h"
#include "../Primitives/Circle.h"
#include "../Primitives/Rectangle.h"
#include "Player.h"

using namespace std;
using namespace m1;


EnemyFly::EnemyFly()
{

}

EnemyFly::EnemyFly(float xc, float yc)
	: EnemyFly(xc, yc, 1, 0, 0.3f)
{
}

EnemyFly::EnemyFly(float xc, float yc, float size, float angle, float velocity)
	: Enemy(xc, yc, size, angle, velocity)
{
	primitives["body"] = new Circle(xc, yc, size, size / 2, angle, contourColor, "flyContour");
	primitives["leftWing"] = new Circle(xc + wingOffsetOx, yc + wingOffsetOy, size, size / 2, angle + wingAngleToOx, wingColor, "flyWing");
	primitives["leftWingContour"] = new Circle(xc + wingOffsetOx, yc + wingOffsetOy, size * 1.1f, size / 2 * 1.2f, angle + wingAngleToOx, contourColor, "flyContour");
	primitives["rightWing"] = new Circle(xc + wingOffsetOx, yc - wingOffsetOy, size, size / 2, angle - wingAngleToOx, wingColor, "flyWing");
	primitives["rightWingContour"] = new Circle(xc + wingOffsetOx, yc - wingOffsetOy, size * 1.1f, size / 2 * 1.2f, angle - wingAngleToOx, contourColor, "flyContour");

	orderedPrimitives.push_back(primitives["body"]);
	orderedPrimitives.push_back(primitives["leftWing"]);
	orderedPrimitives.push_back(primitives["leftWingContour"]);
	orderedPrimitives.push_back(primitives["rightWing"]);
	orderedPrimitives.push_back(primitives["rightWingContour"]);
}

EnemyFly::~EnemyFly()
{

}

void EnemyFly::placeAt(float tx, float ty, float sx, float sy, float u)
{
	this->Shape::placeAt(tx, ty, sx, sy, u);
	primitives["body"]->placeAt(tx, ty, sx, sy / 2, u);
	primitives["leftWing"]->placeAt(tx + wingOffsetOx, ty + wingOffsetOy, sx, sy / 2, 0);
	primitives["leftWingContour"]->placeAt(tx + wingOffsetOx, ty + wingOffsetOy, sx * 1.1f, sy / 2 * 1.2f, 0);
	primitives["rightWing"]->placeAt(tx + wingOffsetOx, ty - wingOffsetOy, sx, sy / 2, 0);
	primitives["rightWingContour"]->placeAt(tx + wingOffsetOx, ty - wingOffsetOy, sx * 1.1f, sy / 2 * 1.2f, 0);

	primitives["leftWing"]->rotateAround(xc, yc, u + wingAngleToOx);
	primitives["leftWingContour"]->rotateAround(xc, yc, u + wingAngleToOx);
	primitives["rightWing"]->rotateAround(xc, yc, u - wingAngleToOx);
	primitives["rightWingContour"]->rotateAround(xc, yc, u - wingAngleToOx);
}
