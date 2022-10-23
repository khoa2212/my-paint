#include "Rectangle.h"

class Square : public Ishapes
{
private:
	Point _topleft;
	Point _rightbottom;
public:
	Point topleft();
	Point rightbottom();
	void settopleft(Point);
	void setrightbottom(Point);
public:
	Square();
	Square(Point, Point);
	std::string toString();
	std::string type();
	static std::shared_ptr<Ishapes> parse(std::string);
	std::shared_ptr<Ishapes>nextShapes(Point, Point);
};

