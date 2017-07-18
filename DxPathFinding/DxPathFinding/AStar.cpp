#include "AStar.h"
#include <cmath>

double Euclidean(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return sqrt( double( (d.getX()*d.getX()) + (d.getY()*d.getY()) ) ); //유클리드
}

double Manhattan(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return (abs(d.getX()) + abs(d.getY())); //맨하탄
}

double Diagonal(IntPoint& p1, IntPoint& p2)
{
	IntPoint d = p1 - p2;
	return max(abs(d.getX()), abs(d.getY())); //다이아고날
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
		cell.current = true; //화면에 현재 서칭되고 있는 노드를 표시하기 위한 플래그

		if( !cell.closed ) //방문할 수 있는 즉 Open List 노드이면 처리
		{
			ptrMap->drawMapStateIn2D();
			ptrMap->getCell(cur).closed = true; // Close List 노드로 설정, 즉 다시 방문 할 수 없다

			if(cell.position == goalPosition)
			{//목표지점 찾음, 탐색 종료
				//1. 플레이어에게 route 를 알려줌
				//2. 맵에 표시함
				
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
				return true; //길찾기 성공	
			}
			//이웃탐색(오픈리스트)
			for(int i=0; i<maxDir; i++)
			{
				ptrMap->drawMapStateIn2D();
				near = cur + DIR[i];
				
				//유효성 검사
				if(near.getX() < 0 || near.getX() >= ptrMap->getSize().getW())
					continue;
				if(near.getY() < 0 || near.getY() >= ptrMap->getSize().getH())
					continue;
				if(ptrMap->getCell(near).closed) //CloseList노드이면 이미 방문한 것이므로 다음 이웃으로
					continue;
				if(ptrMap->getCell(near).weight == X) //갈 수 없는 곳이면
					continue;

				//g 계산
				distance = cell.distance + DIST[i];
				
				if(ptrMap->getCell(near).parent != IntPoint(-1, -1)) 
				{ //이전에 다른 클로즈 노드를 부모로 설정한 셀이라면
					if(distance < ptrMap->getCell(near).distance)
					{//위 계산된 distance가 더 짧으면 이 near의 부모를 getCell(cur)로 업데이트
						
						ptrMap->getCell(near).distance = distance; //거리 변경
						ptrMap->getCell(near).parent = cur; //부모를 새로 변경
						//COST = g + h
						ptrMap->getCell(near).heuristic = distance + ptrMap->getCell(near).weight + getHeu(near, goalPosition);
						whereShouldIGo.push(ptrMap->getCell(near)); //주변 노드를 우선순위큐에 넣는다
					}
				}
				else
				{ //처음 계산되는 노드라면

					ptrMap->getCell(near).distance = distance; //거리 변경
					ptrMap->getCell(near).parent = cur; //부모를 새로 변경
					//COST = g + h
					ptrMap->getCell(near).heuristic = distance +ptrMap->getCell(near).weight  +  getHeu(near, goalPosition);
					Cell c = ptrMap->getCell(near);
					whereShouldIGo.push(c); //주변 노드를 우선순위큐에 넣는다
				}
			}
		}
		cell.current = false;
		
	}
	return false;
}