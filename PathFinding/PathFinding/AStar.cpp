#include "AStar.h"
#include <cmath>
AStar::AStar(void) : PathSearchAI()
{
}

AStar::~AStar(void)
{
}

double getHeu(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return sqrt( double( (d.getX()*d.getX()) + (d.getY()*d.getY()) ) );
}
bool AStar::searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition)
{
	IntPoint cur;
	IntPoint near;
	double distance;
	Cell& start = ptrMap->getCell(startPosition);
	whereShouldIGo.push(start);
	while( !whereShouldIGo.empty() )
	{
		cur = whereShouldIGo.top().getPosition();
		whereShouldIGo.pop();
		Cell& cell = ptrMap->getCell(cur);
		if( !cell.IsVisited() ) //���� �湮�� ��尡 �ƴϸ� ó��, ���⼭ �湮�� �ش� ��尡 ����(�θ�)��尡 �Ǿ��� ���̴�
		{
			ptrMap->getCell(cur).setVisited(true);

			if(cell.getPosition() == goalPosition)
			{//��ǥ���� ã��, Ž�� ����
				//1. �÷��̾�� route �� �˷���
				//2. �ʿ� ǥ����
				
				Cell gg = ptrMap->getCell(goalPosition);
				route.push_front(goalPosition);
				while(gg.getPosition() != startPosition)
				{
					//printf("{%d, %d}\n", gg.getPosition().getX(), gg.getPosition().getY());
					if(gg.getPosition() != goalPosition)
					{
						ptrMap->getCell(gg.getPosition()).setWeight(P);
						route.push_front(gg.getPosition());
					}
					gg = ptrMap->getCell(gg.getParentPosition());
				}
				//printf("{%d, %d}\n", gg.getPosition().getX(), gg.getPosition().getY());
				//gg.setWeight(P);
				route.push_front(startPosition);
				return true; //��ã�� ����	
			}
			//�̿�Ž��(�̰��� �湮�� �ƴϴ�)
			for(int i=0; i<maxDir; i++)
			{
				near = cur + DIR[i];
				
				//��ȿ�� �˻�
				if(near.getX() < 0 || near.getX() >= ptrMap->getSize().getW())
					continue;
				if(near.getY() < 0 || near.getY() >= ptrMap->getSize().getH())
					continue;
				if(ptrMap->getCell(near).IsVisited()) //�̹� �湮�� ���̸� ���� �̿�����
					continue;
				if(ptrMap->getCell(near).getWeight() == X) //�� �� ���� ���̸�
					continue;
				distance = cell.getDistance() + ptrMap->getCell(near).getWeight() + DIST[i];
				

				if(ptrMap->getCell(near).getParentPosition() != IntPoint(-1, -1)) 
				{ //������ ������ ��
					if(distance < ptrMap->getCell(near).getDistance())
					{//���� ���� �ֱ��� �Ÿ��� �� ª�ٸ� ������Ʈ
						ptrMap->getCell(near).setDistance(distance); //�Ÿ� ����
						ptrMap->getCell(near).setParentPosition(cur); //�θ� ���� ����
						ptrMap->getCell(near).setHeuristic(distance + getHeu(near, goalPosition) );
						whereShouldIGo.push(ptrMap->getCell(near)); //�ֺ� ��带 �켱����ť�� �ִ´�
					}
				}
				else
				{ //ó�� ���Ǵ� �����
					ptrMap->getCell(near).setDistance(distance); //�Ÿ� ����
					ptrMap->getCell(near).setParentPosition(cur); //�θ� ���� ����
					ptrMap->getCell(near).setHeuristic(distance + getHeu(near, goalPosition) );
					Cell c = ptrMap->getCell(near);
					whereShouldIGo.push(c); //�ֺ� ��带 �켱����ť�� �ִ´�
				}
			}
		}
	}
	return false;
}