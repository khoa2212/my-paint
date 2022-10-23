#include "Square.h"
Square::Square()
{
	_topleft = { 0, 0 };
	_rightbottom = { 0, 0 };
}
Square::Square(Point a, Point b)
{
	int d0 = abs(a.x() - b.x());
	int d1 = abs(a.y() - b.y());
	int d = abs(d0 - d1);
	if (d0 < d1) {
		if (a.y() > b.y()) {
			b.sety(b.y() + d);
		}
		else {
			b.sety(b.y() - d);
		}
	}
	else {
		if (a.x() > b.x()) {
			b.setx(b.x() + d);
		}
		else {
			b.setx(b.x() - d);
		}
	}
	_topleft = a;
	_rightbottom = b;
}
Point Square::topleft()
{
	return _topleft;
}
Point Square::rightbottom()
{
	return _rightbottom;
}
void Square::settopleft(Point value)
{
	_topleft = value;
}
void Square::setrightbottom(Point value)
{
	_rightbottom = value;
}
std::string Square::toString()
{
	std::stringstream builder;
	builder << _topleft.toString() << " " << _rightbottom.toString();
	return builder.str();
}
std::shared_ptr<Ishapes> Square::parse(std::string buffer)
{
	std::vector<std::string>tokens = Tokenizer::Split(buffer, " ");
	std::shared_ptr<Point> a = Point::parse(tokens[0]);
	std::shared_ptr<Point> b = Point::parse(tokens[1]);
	return std::make_shared<Square>(*a, *b);
}
std::shared_ptr<Ishapes> Square::nextShapes(Point topleft, Point rightbottom)
{
	return std::make_shared<Square>(topleft, rightbottom);
}
std::string Square::type()
{
	return { "Square" };
}