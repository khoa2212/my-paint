#include "Circle.h"

const double pi = 3.14159265358979323846;

Circle::Circle()
{
	_topleft = { 0, 0 };
	_rightbottom = { 0, 0 };
}
Circle::Circle(Point x, Point y)
{
	_topleft = x;
	_rightbottom = y;
}
Point Circle::topleft()
{
	return _topleft;
}
Point Circle::rightbottom()
{
	return _rightbottom;
}
void Circle::settopleft(Point value)
{
	_topleft = value;
}
void Circle::setrightbottom(Point value)
{
	_rightbottom = value;
}
std::string Circle::toString()
{
	std::stringstream builder;
	builder << _topleft.toString() << " " << _rightbottom.toString();
	return builder.str();
}
std::string Circle::type()
{
	return { "Circle" };
}
std::shared_ptr<Ishapes> Circle::parse(std::string buffer)
{
	std::vector<std::string>tokens = Tokenizer::Split(buffer, " ");
	std::shared_ptr<Point> a = Point::parse(tokens[0]);
	std::shared_ptr<Point> b = Point::parse(tokens[1]);
	return std::make_shared<Circle>(*a, *b);
}
std::shared_ptr<Ishapes>Circle::nextShapes(Point topleft, Point rightbottom)
{
	return std::make_shared<Circle>(topleft, rightbottom);
}