#pragma once
#include "Point.h"

class Cell
{
private:
	IntPoint position;
	int		 weight;
	bool	 visited;
	double	 distance;
	double	 heuristic; 
	IntPoint parent;	//2D 그리드맵을 가정하므로 부모노드링크는 좌표로 나타낸다.
public:
	Cell(void);
	Cell(const IntPoint& pos, int weight, bool visited=false);
	Cell(const Cell& cell);
	~Cell(void);
	bool IsVisited();
	void setVisited(bool v);
	int  getWeight();
	void setWeight(int w);
	IntPoint getPosition();
	void setPosition(const IntPoint& pos);
	IntPoint getParentPosition();
	void setParentPosition(const IntPoint& pos);
	double& getHeuristic();
	const double& getHeuristic() const;
	void setHeuristic(double h);
	double& getDistance();
	const double& getDistance() const;
	void setDistance(double d);
	
	friend bool operator<(const Cell& c1, const Cell& c2);
};

