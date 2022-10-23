#include "Line.h"

Line::Line()
{
	_start = { 0, 0 };
	_end = { 0, 0 };
}
Line::Line(Point start, Point end)
{
	_start = start;
	_end = end;
}
Point Line::start()
{
	return _start;
}
Point Line::end()
{
	return _end;
}
void Line::setstart(Point value)
{
	_start = value;
}
void Line::setend(Point value)
{
	_end = value;
}
std::string Line::toString()
{
	std::stringstream builder;
	builder << _start.toString() << " " << _end.toString();
	return builder.str();
}
std::shared_ptr<Ishapes> Line::parse(std::string buffer)
{
	std::vector<std::string>tokens = Tokenizer::Split(buffer, " ");
	std::shared_ptr<Point> a = Point::parse(tokens[0]);
	std::shared_ptr<Point> b = Point::parse(tokens[1]);
	return std::make_shared<Line>(*a, *b);
}
std::string Line::type()
{
	return { "Line" };
}
std::shared_ptr<Ishapes>Line::nextShapes(Point start, Point end)
{
	return std::make_shared<Line>(start, end);
}