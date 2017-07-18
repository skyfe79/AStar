#pragma once
/*
 * class Map
 * �輺ö
 *
 * �� Ŭ������ Cell�� ������ ���� ǥ���Ѵ�.
 * Map �� drawMapStateIn2D() �� �ֻܼ� ���� ǥ���Ѵ�.
 * �� Ŭ������ ����� DxMap �� DirectX�� ����Ͽ� â�� ���� �׸���.
 * DxMap::drawMapStateIn2D() �Լ��� ���� �׸���.
 */
#include "Point.h"
#include "Size.h"
#include "Cell.h"
#include <string>

#define START	-1		//������
#define GOAL	-2		//����
#define R0	  	0		//��(����ġ0)
#define R1		1		//��(����ġ1)
#define R2		2		//��(����ġ2)
#define R3		3		//��(����ġ3)
#define R4		4		//��(����ġ4)
#define X		5		//�� �� ���� ��
#define PATH	6		//���

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

#define TEXCOUNT 11	//���� �׸��µ� �ʿ��� Ÿ���ؽ��� ����
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
	//���� ���� ����� ���� ��
	int FKEY; //[1-3]; �޸���ƽ�޼ҵ�
	int DKEY; //[4,8]; ����
	int AKEY; //[1,2]; ����
public:
	DxMap();
	DxMap(IDirect3DDevice9* Device, const int* mapData, IntSize size);
	DxMap(IDirect3DDevice9* Device, const char* mapFileName);
	~DxMap();
	void drawSetting(ID3DXSprite* Sprite, IntPoint start, IntSize size);
	virtual void drawMapStateIn2D(void);
};
