#pragma once
/*
 * class Cell
 * 김성철
 *
 * 맵을 구성하는 Cell 을 나타낸다.
 * AI를 위한 다양한 멤버 변수가 존재한다.
 */
#include "Point.h"

struct Cell
{
	IntPoint position;
	int		 weight;	// 가중치
	bool	 closed;	// 이미 탐색이 끝난 노드인가?
	bool	 current;	// 현재 탐색되고 있는 노드인가?
	double	 distance;  // G = START 에서 현재점까지의 거리
	double	 heuristic; // H = 현재점에서 GOAL까지의 추정 거리, COST = G + H
	IntPoint parent;	//2D 그리드맵을 가정하므로 부모노드링크는 좌표로 나타낸다.
	Cell(void);
	Cell(const Cell& cell);
	void setInfo(const IntPoint &pos, int weight);
	void clear(void);
};
//셀의 추정치값을 비교하여 작은 값을 기준으로 정렬한다.
//해당 정렬을 위한 비교 연산자
bool operator<(const Cell& c1, const Cell& c2);

