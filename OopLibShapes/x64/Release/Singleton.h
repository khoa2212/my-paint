#include "Circle.h"
class ShapeFactory
{
private:
	static ShapeFactory* _instance;
	std::vector<std::shared_ptr<Ishapes>>_prototypes;
	ShapeFactory();
public:
	static ShapeFactory* instance();
	int typecount();
	std::shared_ptr<Ishapes>create(int, Point, Point);
	static std::shared_ptr<Ishapes>parse(std::string, std::string);
};

