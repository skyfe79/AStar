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
		if( !cell.IsVisited() ) //아직 방문한 노드가 아니면 처리, 여기서 방문은 해당 노드가 현재(부모)노드가 되었을 때이다
		{
			ptrMap->getCell(cur).setVisited(true);

			if(cell.getPosition() == goalPosition)
			{//목표지점 찾음, 탐색 종료
				//1. 플레이어에게 route 를 알려줌
				//2. 맵에 표시함
				
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
				return true; //길찾기 성공	
			}
			//이웃탐색(이것은 방문이 아니다)
			for(int i=0; i<maxDir; i++)
			{
				near = cur + DIR[i];
				
				//유효성 검사
				if(near.getX() < 0 || near.getX() >= ptrMap->getSize().getW())
					continue;
				if(near.getY() < 0 || near.getY() >= ptrMap->getSize().getH())
					continue;
				if(ptrMap->getCell(near).IsVisited()) //이미 방문한 것이면 다음 이웃으로
					continue;
				if(ptrMap->getCell(near).getWeight() == X) //갈 수 없는 곳이면
					continue;
				distance = cell.getDistance() + ptrMap->getCell(near).getWeight() + DIST[i];
				

				if(ptrMap->getCell(near).getParentPosition() != IntPoint(-1, -1)) 
				{ //이전에 설정된 셀
					if(distance < ptrMap->getCell(near).getDistance())
					{//위에 계산된 최근의 거리가 더 짧다면 업데이트
						ptrMap->getCell(near).setDistance(distance); //거리 변경
						ptrMap->getCell(near).setParentPosition(cur); //부모를 새로 변경
						ptrMap->getCell(near).setHeuristic(distance + getHeu(near, goalPosition) );
						whereShouldIGo.push(ptrMap->getCell(near)); //주변 노드를 우선순위큐에 넣는다
					}
				}
				else
				{ //처음 계산되는 노드라면
					ptrMap->getCell(near).setDistance(distance); //거리 변경
					ptrMap->getCell(near).setParentPosition(cur); //부모를 새로 변경
					ptrMap->getCell(near).setHeuristic(distance + getHeu(near, goalPosition) );
					Cell c = ptrMap->getCell(near);
					whereShouldIGo.push(c); //주변 노드를 우선순위큐에 넣는다
				}
			}
		}
	}
	return false;
}