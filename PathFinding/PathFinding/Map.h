#pragma once
#include "Point.h"
#include "Size.h"
#include "Cell.h"
#include <string>


#define S	-1
#define G	-2
#define X	 100	//갈 수 없는 곳
#define R	 0		//weight 0
#define R1	 1		//weight 1
#define W	 10
#define P	 '*'

class MapException
{
public:
	std::string message;
	MapException(const std::string& msg) : message(msg)
	{}
};
class Map
{
private:
	Cell *cells;
	IntPoint startPosition;
	IntPoint goalPosition;
	IntSize  size;
public:
	Map(void);
	Map(const char* mapData, IntSize size);
	Map(const Map& map);
	~Map(void);

	IntPoint& getStartPosition();
	IntPoint& getGoalPosition();
	IntSize&  getSize();
	Cell& getCell(const IntPoint& pos);
	void drawMap(void);
};

