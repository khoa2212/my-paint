#include "function.h"

class Line : public Ishapes
{
private:
	Point _start;
	Point _end;
public:
	Point start();
	Point end();
	void setstart(Point);
	void setend(Point);
public:
	Line();
	Line(Point, Point);
	std::string toString();
	static std::shared_ptr<Ishapes> parse(std::string);
	std::string type();
	std::shared_ptr<Ishapes>nextShapes(Point, Point);
};
