#include "Player.h"

Player::~Player(void)
{
}

Player::Player()
{
	ptrMap = NULL;
	ptrPathSearchAI = NULL;
	maxDir = 4;
	route.clear();
}

Player::Player(PathSearchAI* ai, int maxDir)
{
	ptrMap = NULL;
	ptrPathSearchAI = ai;
	this->maxDir = maxDir;
}

Player::Player(const Player& player)
{
	ptrMap = player.ptrMap;
	ptrPathSearchAI = player.ptrPathSearchAI;
	maxDir = player.maxDir;
}

void Player::goesIntoTheMap(Map *m)
{
	ptrMap = m;
	route.clear();
	ptrPathSearchAI->clear();
}

bool Player::searchPath()
{
	if(ptrPathSearchAI == NULL)
		return false;
	if(ptrMap == NULL)
		return false;
	if(route.size() != 0)
	{
		ptrMap->drawMapStateIn2D();
		return true;
	}
	return ptrPathSearchAI->searchPath(ptrMap, this->maxDir, this->route, ptrMap->getStartPosition(), ptrMap->getGoalPosition());
}

int Player::getMaxDir()
{
	return maxDir;
}

void Player::setMaxDir(int maxDir)
{
	this->maxDir = maxDir;
}
void Player::setAi(PathSearchAI* Ai)
{
	this->ptrPathSearchAI = Ai;
}