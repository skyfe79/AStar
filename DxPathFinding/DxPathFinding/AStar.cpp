#include "AStar.h"
#include <cmath>

double Euclidean(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return sqrt( double( (d.getX()*d.getX()) + (d.getY()*d.getY()) ) ); //��Ŭ����
}

double Manhattan(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return (abs(d.getX()) + abs(d.getY())); //����ź
}

double Diagonal(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return max(abs(d.getX()), abs(d.getY())); //���̾ư�
}

AStar::AStar(HEURISTIC_METHOD h) : PathSearchAI()
{
	hm = h;
}

AStar::~AStar(void)
{
}
void AStar::setHeuristicMethod(HEURISTIC_METHOD h)
{
	hm = h;
}
bool AStar::searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition)
{
	double (*getHeu)(IntPoint& p1, IntPoint& p2);
	switch(hm)
	{
	case DIAGONAL:
		getHeu = Diagonal;
		break;
	case MANHATTAN:
		getHeu = Manhattan;
		break;
	case EUCLIDEAN:
		getHeu = Euclidean;
		break;
	default:
		getHeu = Manhattan;
		break;
	}

	IntPoint cur;
	IntPoint near;
	double distance;
	Cell& start = ptrMap->getCell(startPosition);
	whereShouldIGo.push(start);
	while( !whereShouldIGo.empty() )
	{
		ptrMap->drawMapStateIn2D();
		cur = whereShouldIGo.top().position;
		whereShouldIGo.pop();
		Cell& cell = ptrMap->getCell(cur);
		cell.current = true; //ȭ�鿡 ���� ��Ī�ǰ� �ִ� ��带 ǥ���ϱ� ���� �÷���

		if( !cell.closed ) //�湮�� �� �ִ� �� Open List ����̸� ó��
		{
			ptrMap->drawMapStateIn2D();
			ptrMap->getCell(cur).closed = true; // Close List ���� ����, �� �ٽ� �湮 �� �� ����

			if(cell.position == goalPosition)
			{//��ǥ���� ã��, Ž�� ����
				//1. �÷��̾�� route �� �˷���
				//2. �ʿ� ǥ����
				
				Cell gg = ptrMap->getCell(goalPosition);
				route.push_front(goalPosition);
				while(gg.position != startPosition)
				{
					if(gg.position != goalPosition)
					{
						ptrMap->getCell(gg.position).weight = PATH;
						route.push_front(gg.position);
					}
					gg = ptrMap->getCell(gg.parent);
				}
				route.push_front(startPosition);
				return true; //��ã�� ����	
			}
			//�̿�Ž��(���¸���Ʈ)
			for(int i=0; i<maxDir; i++)
			{
				ptrMap->drawMapStateIn2D();
				near = cur + DIR[i];
				
				//��ȿ�� �˻�
				if(near.getX() < 0 || near.getX() >= ptrMap->getSize().getW())
					continue;
				if(near.getY() < 0 || near.getY() >= ptrMap->getSize().getH())
					continue;
				if(ptrMap->getCell(near).closed) //CloseList����̸� �̹� �湮�� ���̹Ƿ� ���� �̿�����
					continue;
				if(ptrMap->getCell(near).weight == X) //�� �� ���� ���̸�
					continue;

				//g ���
				distance = cell.distance + DIST[i];
				
				if(ptrMap->getCell(near).parent != IntPoint(-1, -1)) 
				{ //������ �ٸ� Ŭ���� ��带 �θ�� ������ ���̶��
					if(distance < ptrMap->getCell(near).distance)
					{//�� ���� distance�� �� ª���� �� near�� �θ� getCell(cur)�� ������Ʈ
						
						ptrMap->getCell(near).distance = distance; //�Ÿ� ����
						ptrMap->getCell(near).parent = cur; //�θ� ���� ����
						//COST = g + h
						ptrMap->getCell(near).heuristic = distance + ptrMap->getCell(near).weight + getHeu(near, goalPosition);
						whereShouldIGo.push(ptrMap->getCell(near)); //�ֺ� ��带 �켱����ť�� �ִ´�
					}
				}
				else
				{ //ó�� ���Ǵ� �����

					ptrMap->getCell(near).distance = distance; //�Ÿ� ����
					ptrMap->getCell(near).parent = cur; //�θ� ���� ����
					//COST = g + h
					ptrMap->getCell(near).heuristic = distance +ptrMap->getCell(near).weight  +  getHeu(near, goalPosition);
					Cell c = ptrMap->getCell(near);
					whereShouldIGo.push(c); //�ֺ� ��带 �켱����ť�� �ִ´�
				}
			}
		}
		cell.current = false;
		
	}
	return false;
}