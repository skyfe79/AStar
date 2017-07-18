#pragma once
/*
 * class Player
 * �輺ö
 *
 * �� Ŭ������ AI�� �̿��Ͽ� ���� Ž���ϴ� �÷��̾ ��Ÿ����.
 * Ž���� route ����� ����� ��ǥ�� �����ȴ�.
 */
#include "Map.h"
#include "PathSearchAI.h"
#include "Point.h"
#include <list>
class Player
{
private:
	Map*	ptrMap;
	PathSearchAI* ptrPathSearchAI;
	int		maxDir;
	std::list<IntPoint> route;
public:
	Player(void);
	Player(PathSearchAI* ai, int maxDir = 4);
	Player(const Player& player);
	~Player(void);
	void goesIntoTheMap(Map* m);
	bool searchPath(void);
	int  getMaxDir();
	void setMaxDir(int maxDir);
	void setAi(PathSearchAI* Ai);
};

