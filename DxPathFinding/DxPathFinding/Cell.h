#pragma once
/*
 * class Cell
 * �輺ö
 *
 * ���� �����ϴ� Cell �� ��Ÿ����.
 * AI�� ���� �پ��� ��� ������ �����Ѵ�.
 */
#include "Point.h"

struct Cell
{
	IntPoint position;
	int		 weight;	// ����ġ
	bool	 closed;	// �̹� Ž���� ���� ����ΰ�?
	bool	 current;	// ���� Ž���ǰ� �ִ� ����ΰ�?
	double	 distance;  // G = START ���� ������������ �Ÿ�
	double	 heuristic; // H = ���������� GOAL������ ���� �Ÿ�, COST = G + H
	IntPoint parent;	//2D �׸������ �����ϹǷ� �θ��帵ũ�� ��ǥ�� ��Ÿ����.
	Cell(void);
	Cell(const Cell& cell);
	void setInfo(const IntPoint &pos, int weight);
	void clear(void);
};
//���� ����ġ���� ���Ͽ� ���� ���� �������� �����Ѵ�.
//�ش� ������ ���� �� ������
bool operator<(const Cell& c1, const Cell& c2);

