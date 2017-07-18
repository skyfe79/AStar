#include "Cell.h"


Cell::Cell(void)
{
	weight = 0;
	visited = false;
	heuristic = 0;
	distance = 0;
	parent = IntPoint(-1, -1);
}
Cell::Cell(const IntPoint &pos, int weight, bool visited)
{
	this->position = pos;
	this->weight = weight;
	this->visited = visited;
	heuristic = 0;
	distance = 0;
	parent = IntPoint(-1, -1);
}
Cell::Cell(const Cell& cell)
{
	position = cell.position;
	weight = cell.weight;
	visited = cell.visited;
	heuristic = cell.heuristic;
	distance = cell.distance;
	parent = cell.parent;
}
bool Cell::IsVisited()
{
	return visited;
}
void Cell::setVisited(bool v)
{
	visited = v;
}
int  Cell::getWeight()
{
	return weight;
}
void Cell::setWeight(int w)
{
	weight = w;
}
IntPoint Cell::getPosition()
{
	return position;
}
void Cell::setPosition(const IntPoint& pos)
{
	position = pos;
}
IntPoint Cell::getParentPosition()
{
	return parent;
}
void Cell::setParentPosition(const IntPoint& pos)
{
	parent = pos;
}
double& Cell::getHeuristic()
{
	return heuristic;
}
const double& Cell::getHeuristic() const
{
	return heuristic;
}
void Cell::setHeuristic(double h)
{
	heuristic = h;
}
double& Cell::getDistance()
{
	return distance;
}
const double& Cell::getDistance() const
{
	return distance;
}
void Cell::setDistance(double d)
{
	distance = d;
}
Cell::~Cell(void)
{
}

bool operator<(const Cell& c1, const Cell& c2)
{
	return !(c1.getHeuristic() <= c2.getHeuristic());
}
