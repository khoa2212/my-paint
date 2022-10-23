#include "Point.h"

const int ceiling = 100;
class Ishapes
{
public:
	virtual std::shared_ptr<Ishapes>nextShapes(Point, Point) = 0;
	virtual std::string toString() = 0;
	virtual std::string type() = 0;
};


