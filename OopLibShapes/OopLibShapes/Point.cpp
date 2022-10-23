#include "Point.h"

std::vector<std::string>Tokenizer::Split(std::string haystack, std::string neddle = " ")
{
	std::vector<std::string>tokens;
	int startpos = 0;
	size_t  foundpos = 0;
	while (true)
	{
		foundpos = haystack.find(neddle, startpos);
		if (foundpos != std::string::npos)
		{
			std::string token = haystack.substr(startpos, foundpos - startpos);
			tokens.push_back(token);
			startpos = (int)foundpos + (int)neddle.length();
		}
		else
		{
			std::string token = haystack.substr(startpos, haystack.length() - foundpos);
			tokens.push_back(token);
			break;
		}
	}
	return tokens;
}
Point::Point()
{
	_x = 0;
	_y = 0;
}
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}
int Point::x()
{
	return _x;
}
int Point::y()
{
	return _y;
}
void Point::setx(int value)
{
	_x = value;
}
void Point::sety(int value)
{
	_y = value;
}
std::string Point::toString()
{
	std::stringstream builder;
	builder << _x << "," << _y;
	return builder.str();
}
std::shared_ptr<Point> Point::parse(std::string buffer)
{
	std::vector<std::string>tokens = Tokenizer::Split(buffer, ",");
	int x = stoi(tokens[0]);
	int y = stoi(tokens[1]);
	return std::make_shared<Point>(x, y);
}