#include "Map.h"

Map::Map(void)
{
	cells = NULL;
	size  = IntSize(0, 0);
	startPosition = IntPoint(0, 0);
	goalPosition = IntPoint(0, 0);
}
Map::Map(const char* mapData, IntSize size)
{
	this->size = size;
	cells = new Cell[size.getW()*size.getH()];
	int i, j, m;
	bool isThereStart = false;
	bool isThereGoal  = false;
	for(i=0; i<size.getH(); i++)
	{
		for(j=0; j<size.getW(); j++)
		{
			m = mapData[j + i*size.getW()];
			if(m == S)
			{
				startPosition = IntPoint(j, i);
				isThereStart = true;
			}
			if(m == G)
			{
				goalPosition = IntPoint(j, i);
				isThereGoal = true;
			}
			cells[j + i*size.getW()].setWeight(m);
			cells[j + i*size.getW()].setPosition(IntPoint(j, i));
			cells[j + i*size.getW()].setVisited(false);
		}
	}

	if(!isThereStart || !isThereGoal)
	{
		throw MapException("맵의 시작 또는 종료점이 없습니다.");
	}
}
Map::Map(const Map& map)
{
}
Map::~Map(void)
{
	if(cells != NULL) {
		delete [] cells;
	}
}
IntPoint& Map::getStartPosition()
{
	return startPosition;
}
IntPoint& Map::getGoalPosition()
{
	return goalPosition;
}
IntSize&  Map::getSize()
{
	return size;
}
Cell& Map::getCell(const IntPoint& pos)
{
	if(cells == NULL)
		throw MapException("맵데이터가 없습니다");
	if(pos.getX() >= size.getW())
		throw MapException("너비범위오류입니다");
	if(pos.getY() >= size.getH())
		throw MapException("높이범위오류입니다");
	return cells[pos.getX() + size.getW()*pos.getY()];
}
void Map::drawMap(void)
{
	int i, j, w, h, m;
	w = size.getW();
	h = size.getH();
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			m = cells[j + w*i].getWeight(); 
			if(m == X)
			{
				printf("X ");
			}
			if(m == W)
			{
				printf("W ");
			}
			if(m == S)
			{
				printf("S ");
			}
			if(m == G)
			{
				printf("G ");
			}
			if(m == R)
			{
				printf(". ");
			}
			if(m == P)
			{
				printf("* ");
			}
			
		}
		printf("\n");
	}
}
