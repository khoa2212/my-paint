#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <memory>
class Tokenizer
{
public:
	static std::vector<std::string>Split(std::string, std::string);
};
class Point
{
private:
	int _x;
	int _y;
public:
	int x();
	int y();
	void setx(int);
	void sety(int);
public:
	Point();
	Point(int, int);
	std::string toString();
	static std::shared_ptr<Point> parse(std::string);
};


