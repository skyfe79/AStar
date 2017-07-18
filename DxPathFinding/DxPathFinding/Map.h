#pragma once
/*
 * class Map
 * 김성철
 *
 * 이 클래스는 Cell로 구성된 맵을 표현한다.
 * Map 의 drawMapStateIn2D() 는 콘솔상에 맵을 표시한다.
 * 이 클래스를 상속한 DxMap 은 DirectX를 사용하여 창에 맵을 그린다.
 * DxMap::drawMapStateIn2D() 함수가 맵을 그린다.
 */
#include "Point.h"
#include "Size.h"
#include "Cell.h"
#include <string>

#define START	-1		//시작점
#define GOAL	-2		//끝점
#define R0	  	0		//길(가중치0)
#define R1		1		//길(가중치1)
#define R2		2		//길(가중치2)
#define R3		3		//길(가중치3)
#define R4		4		//길(가중치4)
#define X		5		//갈 수 없는 곳
#define PATH	6		//경로

class MapException
{
public:
	std::string message;
	MapException(const std::string& msg) : message(msg)
	{}
};
class Map
{
protected:
	Cell *cells;
	IntPoint startPosition;
	IntPoint goalPosition;
	IntSize  size;
public:
	Map(void);
	Map(const int* mapData, IntSize size);
	Map(const char* filename);
	virtual ~Map(void);
	
	void buildMap(const int* mapData, IntSize size);
	IntPoint& getStartPosition();
	IntPoint& getGoalPosition();
	IntSize&  getSize();
	Cell& getCell(const IntPoint& pos);
	virtual void drawMapStateIn2D(void);
	bool loadFromFile(const char* map_filename);
	void clear(void);
};

#define TEXCOUNT 11	//맵을 그리는데 필요한 타일텍스춰 개수
struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct ID3DXSprite;
class CD3DFont;
class DxMap : public Map
{
private:
	IDirect3DDevice9* device;
	IDirect3DTexture9* textures[TEXCOUNT];
	void loadMapTexture();
	ID3DXSprite *sprite;
	IntPoint start;
	IntSize areaSize;
	CD3DFont* Text;
public:
	//현재 정보 출력을 위한 값
	int FKEY; //[1-3]; 휴리스틱메소드
	int DKEY; //[4,8]; 방향
	int AKEY; //[1,2]; 지능
public:
	DxMap();
	DxMap(IDirect3DDevice9* Device, const int* mapData, IntSize size);
	DxMap(IDirect3DDevice9* Device, const char* mapFileName);
	~DxMap();
	void drawSetting(ID3DXSprite* Sprite, IntPoint start, IntSize size);
	virtual void drawMapStateIn2D(void);
};
