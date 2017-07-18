#include "d3dUtility.h"
#include "Map.h"
#include "d3dfont.h"

Map::Map(void)
{
	cells = NULL;
	size  = IntSize(0, 0);
	startPosition = IntPoint(0, 0);
	goalPosition = IntPoint(0, 0);
}
Map::Map(const int* mapData, IntSize size)
{
	if(!mapData)
		return ;
	
	cells = NULL;
	size  = IntSize(0, 0);
	startPosition = IntPoint(0, 0);
	goalPosition = IntPoint(0, 0);
	
	try
	{
		buildMap(mapData, size);
	}
	catch(MapException& e)
	{
		throw e;
	}
}
Map::Map(const char* filename)
{
	cells = NULL;
	size  = IntSize(0, 0);
	startPosition = IntPoint(0, 0);
	goalPosition = IntPoint(0, 0);

	if(!loadFromFile(filename))
	{
		MessageBox(0, "맵파일열기에 실패했습니다", "오류", MB_OK);
	}
}
Map::~Map(void)
{
	if(cells != NULL) {
		delete [] cells;
	}
}
void Map::buildMap(const int* mapData, IntSize size)
{
	if(cells != 0)
		delete [] cells;

	this->size = size;
	cells = new Cell[size.getW()*size.getH()];
	int i, j, m;
	bool isThereStart = false;
	bool isThereGoal  = false;
	for(i=0; i<size.getH(); i++)
	{
		for(j=0; j<size.getW(); j++)
		{
			m = mapData[j + i*size.getW()];
			if(m == START)
			{
				startPosition = IntPoint(j, i);
				isThereStart = true;
			}
			if(m == GOAL)
			{
				goalPosition = IntPoint(j, i);
				isThereGoal = true;
			}
			cells[j + i*size.getW()].setInfo(IntPoint(j, i), m);
		}
	}

	if(!isThereStart || !isThereGoal)
	{
		throw MapException("맵의 시작 또는 종료점이 없습니다.");
	}
}
void Map::clear(void)
{
	int i, j;
	for(i=0; i<size.getH(); i++)
	{
		for(j=0; j<size.getW(); j++)
		{
			cells[j + i*size.getW()].clear();
		}
	}
	
}

IntPoint& Map::getStartPosition()
{
	return startPosition;
}
IntPoint& Map::getGoalPosition()
{
	return goalPosition;
}
IntSize&  Map::getSize()
{
	return size;
}
Cell& Map::getCell(const IntPoint& pos)
{
	if(cells == NULL)
		throw MapException("맵데이터가 없습니다");
	if(pos.getX() >= size.getW())
		throw MapException("너비범위오류입니다");
	if(pos.getY() >= size.getH())
		throw MapException("높이범위오류입니다");
	return cells[pos.getX() + size.getW()*pos.getY()];
}
bool Map::loadFromFile(const char* map_filename)
{
	FILE* fp = fopen(map_filename, "rb");

	if(fp == 0)
		return false;

	int row = 0;
	int col = 0;
	fread(&row, sizeof(int), 1, fp);
	fread(&col, sizeof(int), 1, fp);
	if( row <= 0 && col <= 0)
	{
		fclose(fp);
		return false;
	}

	int *mapData = new int[row * col];
	fread(mapData, sizeof(int), row*col, fp);
	
	buildMap(mapData, IntSize(row, col));

	fclose(fp);
	return true;
}
void Map::drawMapStateIn2D(void)
{
	int i, j, w, h, m;
	w = size.getW();
	h = size.getH();
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			m = cells[j + w*i].weight;
			if(m == X)
			{
				printf("X ");
			}
			if(m == R4)
			{
				printf("W ");
			}
			if(m == START)
			{
				printf("S ");
			}
			if(m == GOAL)
			{
				printf("G ");
			}
			if(m == R0)
			{
				printf(". ");
			}
			if(m == PATH)
			{
				printf("* ");
			}
			
		}
		printf("\n");
	}
}

DxMap::DxMap() : Map()
{
	FKEY = 2; //[1-3]; 휴리스틱메소드
	DKEY = 8; //[4,8]; 방향
	AKEY = 1; //[1,2]; 지능
}
DxMap::DxMap(IDirect3DDevice9* Device, const int* mapData, IntSize size) : Map(mapData, size)
{
	this->device = Device;
	loadMapTexture();
	FKEY = 2; //[1-3]; 휴리스틱메소드
	DKEY = 8; //[4,8]; 방향
	AKEY = 1; //[1,2]; 지능
}
DxMap::DxMap(IDirect3DDevice9* Device, const char* mapFileName) : Map(mapFileName)
{
	this->device = Device;
	loadMapTexture();
	FKEY = 2; //[1-3]; 휴리스틱메소드
	DKEY = 8; //[4,8]; 방향
	AKEY = 1; //[1,2]; 지능
}
DxMap::~DxMap()
{
	for(int i=0; i<TEXCOUNT; i++)
	{
		d3d::Release<IDirect3DTexture9*>(textures[i]);
	}
	Text->InvalidateDeviceObjects();
	Text->DeleteDeviceObjects();
}

void DxMap::loadMapTexture()
{
	//타이맵텍스춰 만들기
	D3DXCreateTextureFromFile(
		device,
		"R0.bmp",
		&textures[0]);
	D3DXCreateTextureFromFile(
		device,
		"R1.bmp",
		&textures[1]);
	D3DXCreateTextureFromFile(
		device,
		"R2.bmp",
		&textures[2]);
	D3DXCreateTextureFromFile(
		device,
		"R3.bmp",
		&textures[3]);
	D3DXCreateTextureFromFile(
		device,
		"R4.bmp",
		&textures[4]);
	D3DXCreateTextureFromFile(
		device,
		"X.bmp",
		&textures[5]);
	D3DXCreateTextureFromFile(
		device,
		"PATH.png",
		&textures[6]);
	D3DXCreateTextureFromFile(
		device,
		"START.bmp",
		&textures[7]);
	D3DXCreateTextureFromFile(
		device,
		"GOAL.bmp",
		&textures[8]);
	D3DXCreateTextureFromFile(
		device,
		"SEARCHING.png",
		&textures[9]);
	D3DXCreateTextureFromFile(
		device,
		"SEARCHED.png",
		&textures[10]);

	//폰트설정
	Text = new CD3DFont(_T("Arial"), 10, D3DFONT_BOLD);
	Text->InitDeviceObjects(device);
	Text->RestoreDeviceObjects();
}


void DxMap::drawSetting(ID3DXSprite* Sprite, IntPoint start, IntSize size)
{
	this->sprite = Sprite;
	this->start = start;
	this->areaSize = size;
}

void DxMap::drawMapStateIn2D(void)
{
	D3DXVECTOR2 cellSize(0, 0);	// 셀크기
	D3DXVECTOR2 cellPos(0,0);	// 셀위치
	
	cellSize.x = (float)areaSize.getW() / (float)size.getW(); // 맵이그려질 너비 나누기 가로셀의 개수
	cellSize.y = (float)areaSize.getH() / (float)size.getH(); // 맵이그려질 높이 나누기 세로셀의 개수
	cellSize.x /= 32.0f; //스프라이트크기로 다시 나눈다. 비율이므로
	cellSize.y /= 32.0f; //스프라이트크기로 다시 나눈다. 비율이므로
	
	device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0) , 1.0f, 0);
	device->BeginScene();
	
	sprite->Begin();

	//맵그리기
	int y, x, w, m, texIndex;
	bool closed = false;
	bool current = false;
	w = size.getW();
	for(int y=0; y<size.getH(); y++)
	{
		for(int x=0; x<size.getW(); x++)
		{
			m = cells[x + w*y].weight; 
			if(m == START)
			{
				texIndex = 7;
			}
			else if(m == GOAL)
			{
				texIndex = 8;
			}
			else
			{
				texIndex = m;
			}
			
			cellPos.x = start.getX()+x*32.0f*cellSize.x;
			cellPos.y = start.getY()+y*32.0f*cellSize.y;
			sprite->Draw(textures[texIndex], NULL, &cellSize, 0, 0, &cellPos, D3DCOLOR_ARGB(255, 255, 255, 255 ));
		}
	}

	for(int y=0; y<size.getH(); y++)
	{
		for(int x=0; x<size.getW(); x++)
		{
			m = cells[x + w*y].weight; 
			closed  = cells[x + w*y].closed;
			current = cells[x + w*y].current;
			if(m == START)
			{
				texIndex = 7;
			}
			else if(m == GOAL)
			{
				texIndex = 8;
			}
			else
			{
				texIndex = m;
			}
			if(current)
			{
				texIndex = 9;
			}
			if(closed)
			{
				texIndex = 10;
			}
						
			cellPos.x = start.getX()+x*32.0f*cellSize.x;
			cellPos.y = start.getY()+y*32.0f*cellSize.y;
			sprite->Draw(textures[texIndex], NULL, &cellSize, 0, 0, &cellPos, D3DCOLOR_ARGB(255, 255, 255, 255 ));
		}
	}
	sprite->End();

	Text->DrawText(20, 20, D3DCOLOR_ARGB(255, 255, 255, 0), _T("1-9 : Change the map."));
	
	if(AKEY == 1)
	{
		switch(FKEY)
		{
		case 1:
			Text->DrawText(20, 40, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F1  : DIAGONAL"));
			Text->DrawText(20, 60, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F2  : MANHATTAN"));
			Text->DrawText(20, 80, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F3  : EUCLIDEAN"));
			break;
		case 2:
			Text->DrawText(20, 40, D3DCOLOR_ARGB(255, 128, 128, 128),   _T("F1  : DIAGONAL"));
			Text->DrawText(20, 60, D3DCOLOR_ARGB(255, 255, 255, 0), _T("F2  : MANHATTAN"));
			Text->DrawText(20, 80, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F3  : EUCLIDEAN"));
			break;
		case 3:
			Text->DrawText(20, 40, D3DCOLOR_ARGB(255, 128, 128, 128),   _T("F1  : DIAGONAL"));
			Text->DrawText(20, 60, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F2  : MANHATTAN"));
			Text->DrawText(20, 80, D3DCOLOR_ARGB(255, 255, 255, 0), _T("F3  : EUCLIDEAN"));
			break;
		default:
			Text->DrawText(20, 40, D3DCOLOR_ARGB(255, 128, 128, 128),   _T("F1  : DIAGONAL"));
			Text->DrawText(20, 60, D3DCOLOR_ARGB(255, 255, 255, 0), _T("F2  : MANHATTAN"));
			Text->DrawText(20, 80, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F3  : EUCLIDEAN"));
			break;
		}
	}
	else
	{
		Text->DrawText(20, 40, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F1  : DIAGONAL"));
		Text->DrawText(20, 60, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F2  : MANHATTAN"));
		Text->DrawText(20, 80, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F3  : EUCLIDEAN"));
	}


	switch(DKEY)
	{
	case 4:
		Text->DrawText(180, 20, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F5 : 4-Ways"));
		Text->DrawText(180, 40, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F6 : 8-Ways"));
		break;
	case 8:
		Text->DrawText(180, 20, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F5 : 4-Ways"));
		Text->DrawText(180, 40, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F6 : 8-Ways"));
		break;
	default:
		Text->DrawText(180, 20, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F5 : 4-Ways"));
		Text->DrawText(180, 40, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F6 : 8-Ways"));
		break;
	}
	switch(AKEY)
	{
	case 1:
		Text->DrawText(180, 60, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F7 : AStar"));
		Text->DrawText(180, 80, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F8 : DFS"));
		break;
	case 2:
		Text->DrawText(180, 60, D3DCOLOR_ARGB(255, 128, 128, 128), _T("F7 : AStar"));
		Text->DrawText(180, 80, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("F8 : DFS"));
		break;
	default:
		Text->DrawText(180, 60, D3DCOLOR_ARGB(255, 255, 255, 0), _T("F7 : AStar"));
		Text->DrawText(180, 80, D3DCOLOR_ARGB(255, 128, 128, 128),   _T("F8 : DFS"));
		break;
	}
	Text->DrawText(320, 20, D3DCOLOR_ARGB(255, 255, 255, 0),   _T("S : START"));
	device->EndScene();
	device->Present(0, 0, 0, 0);
}