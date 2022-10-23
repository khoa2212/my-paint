#include "Rectangle.h"

Rectangle::Rectangle()
{
	_topleft = { 0, 0 };
	_rightbottom = { 0, 0 };
}
Rectangle::Rectangle(Point x, Point y)
{
	_topleft = x;
	_rightbottom = y;
}
Point Rectangle::topleft()
{
	return _topleft;
}
Point Rectangle::rightbottom()
{
	return _rightbottom;
}
void Rectangle::settopleft(Point value)
{
	_topleft = value;
}
void Rectangle::setrightbottom(Point value)
{
	_rightbottom = value;
}
std::string Rectangle::toString()
{
	std::stringstream builder;
	builder << _topleft.toString() << " " << _rightbottom.toString();
	return builder.str();
}
std::shared_ptr<Ishapes> Rectangle::parse(std::string buffer)
{
	std::vector<std::string>tokens = Tokenizer::Split(buffer, " ");
	std::shared_ptr<Point> a = Point::parse(tokens[0]);
	std::shared_ptr<Point> b = Point::parse(tokens[1]);
	return std::make_shared<Rectangle>(*a, *b);
}
std::shared_ptr<Ishapes> Rectangle::nextShapes(Point topleft, Point rightbottom)
{
	return std::make_shared<Rectangle>(topleft, rightbottom);
}
std::string Rectangle::type()
{
	return { "Rectangle" };
}
