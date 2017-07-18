#include "DFS.h"

DFS::DFS(void) : PathSearchAI()
{
}

DFS::~DFS(void)
{
}

bool DFS::searchPath(Map* ptrMap, int maxDir, std::list<IntPoint>& route, IntPoint& startPosition, IntPoint& goalPosition)
{
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
		cell.current = true;

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
				distance = cell.distance + DIST[i];
				
				if(ptrMap->getCell(near).parent != IntPoint(-1, -1)) 
				{ //������ �ٸ� Ŭ���� ��带 �θ�� ������ ���̶��
					if(distance < ptrMap->getCell(near).distance)
					{//���� ���� �ֱ��� �Ÿ��� �� ª�� Ŭ���� ��带 �θ�� ������Ʈ
						
						ptrMap->getCell(near).distance = distance; //�Ÿ� ����
						ptrMap->getCell(near).parent = cur; //�θ� ���� ����
						ptrMap->getCell(near).heuristic = distance; //�Ÿ��켱Ž���� �޸���ƽ�� �� ���������� ��������� �Ÿ��̴�.
						whereShouldIGo.push(ptrMap->getCell(near)); //�ֺ� ��带 �켱����ť�� �ִ´�
					}
				}
				else
				{ //ó�� ���Ǵ� �����

					ptrMap->getCell(near).distance = distance; //�Ÿ� ����
					ptrMap->getCell(near).parent = cur; //�θ� ���� ����
					ptrMap->getCell(near).heuristic = distance; //�Ÿ��켱Ž���� �޸���ƽ�� �� ���������� ��������� �Ÿ��̴�.
					Cell c = ptrMap->getCell(near);
					whereShouldIGo.push(c); //�ֺ� ��带 �켱����ť�� �ִ´�
				}
			}
		}
		cell.current = false;
		
	}
	return false;
}