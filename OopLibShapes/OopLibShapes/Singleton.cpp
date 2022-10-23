#include "Singleton.h"
ShapeFactory* ShapeFactory::_instance = NULL;
ShapeFactory::ShapeFactory()
{
	_prototypes.push_back(std::make_shared<Line>());
	_prototypes.push_back(std::make_shared<Rectangle>());
	_prototypes.push_back(std::make_shared<Circle>());
	_prototypes.push_back(std::make_shared<Square>());
}
int ShapeFactory::typecount()
{
	return (int)_prototypes.size();
}
std::shared_ptr<Ishapes>ShapeFactory::create(int type, Point start, Point end)
{
	return _prototypes[type]->nextShapes(start, end);
}
ShapeFactory* ShapeFactory::instance()
{
	if (_instance == NULL) {
		_instance = new ShapeFactory();
	}
	return _instance;
}
std::shared_ptr<Ishapes> ShapeFactory::parse(std::string type, std::string value)
{
	std::shared_ptr<Ishapes>shape = NULL;
	if (type == "Line") {
		shape = Line::parse(value);
	}
	else if (type == "Rectangle") {
		shape = Rectangle::parse(value);
	}
	else if (type == "Square") {
		shape = Square::parse(value);
	}
	else {
		shape = Circle::parse(value);
	}
	return shape;
}