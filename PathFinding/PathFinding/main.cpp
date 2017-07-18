#include <stdio.h>
#include "Point.h"
#include "Size.h"
#include "Cell.h"
#include "Map.h"
#include "Player.h"
#include "PathSearchAI.h"
#include "AStar.h"


#define WIDTH	20
#define HEIGHT	10
char map[HEIGHT*WIDTH] = 
{
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, X, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, X, 0, 0, 0, W, 0, 0, 0,
	 0, S, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, X, 0, 0, 0, W, 0, G, 0,
	 0, 0, 0, 0, 0, 0, X, X, X, X, X, X, X, 0, 0, 0, W, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, X, 0, 0, 0, W, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, X, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, X, X, X, X, X, X, X, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/*
#define WIDTH	5
#define HEIGHT	5
char map[HEIGHT*WIDTH] = 
{
	 0, X, 0, 0, 0,
	 0, S, X, 0, 0,
	 0, 0, X, 0, 0,
	 X, X, X, 0, 0,
	 0, 0, 0, G, 0
};*/
int main()
{
	try
	{
		Map m(map, IntSize(WIDTH, HEIGHT));
		m.drawMap();
		
		{
			PathSearchAI* ai = new AStar();;
			Player p(ai, 8);	
			p.goesIntoTheMap(&m);
			if(p.searchPath())
			{
				printf("\n");
				m.drawMap();
			}
			delete ai;
		}
	}
	catch(MapException& e)
	{
		printf(e.message.c_str());
	}
	return 0;
}