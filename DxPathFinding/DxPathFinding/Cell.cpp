#include "Cell.h"



Cell::Cell(void)
{
	clear();
}
Cell::Cell(const Cell& cell)
{
	*this = cell;
}
void Cell::setInfo(const IntPoint &pos, int weight)
{
	this->position = pos;
	this->weight = weight;
	clear();
}
void Cell::clear(void)
{
	closed = false;
	heuristic = 0;
	distance = 0;
	parent = IntPoint(-1, -1);
	current = false;
}

bool operator<(const Cell& c1, const Cell& c2)
{
	return !(c1.heuristic <= c2.heuristic);
}
