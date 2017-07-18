#include "d3dUtility.h"
#include "Map.h"
#include "Player.h"
#include "AStar.h"
#include "DFS.h"
const int Width = 800;
const int Height = 800;
IDirect3DDevice9* Device = 0; 
ID3DXSprite* Sprite = 0;
DxMap* DemoMap = 0;
Player* DemoPlayer = 0;
PathSearchAI* astar = 0;
PathSearchAI* dfs = 0;
std::string map_filename = "map01.map";
bool Setup()
{
	//스프라이트
	D3DXCreateSprite(Device, &Sprite);

	//직교설정
	//2D-Sprite만 사용
	//View 행렬은 항상 단일행렬
	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );
	Device->SetTransform( D3DTS_VIEW, &matView );

	//직교
	D3DXMATRIX matProj;
	D3DXMatrixOrthoLH( &matProj, (float)Width, (float)Height, 0.0f, 1.0f );
	Device->SetTransform( D3DTS_PROJECTION, &matProj );
	
	try
	{
		DemoMap = new DxMap(Device, map_filename.c_str());
		DemoMap->drawSetting(Sprite, IntPoint(0, 100), IntSize(Width, Height-100));
		astar = new AStar();
		dfs   = new DFS();
		DemoPlayer = new Player(astar, 8);	
	}
	catch(MapException& e)
	{
		MessageBox(0, e.message.c_str(), "오류", MB_OK);
		return false;
	}
	
	return true;
}

void Cleanup()
{
	d3d::Release<ID3DXSprite*>(Sprite);
	d3d::Delete<DxMap*>(DemoMap);
	d3d::Delete<Player*>(DemoPlayer);
	d3d::Delete<PathSearchAI*>(astar);
	d3d::Delete<PathSearchAI*>(dfs);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		DemoMap->drawMapStateIn2D();
		if( ::GetAsyncKeyState('S') & 0x8000f )
		{
			DemoMap->loadFromFile(map_filename.c_str());
			DemoPlayer->goesIntoTheMap(DemoMap);
			if(!DemoPlayer->searchPath())
			{
				::MessageBox(0, "경로가 없습니다.", "알림", MB_OK);
			}
		}
		if( ::GetAsyncKeyState(VK_F1) & 0x8000f && DemoMap->AKEY == 1)
		{
			((AStar *)astar)->setHeuristicMethod(DIAGONAL);
			DemoMap->FKEY = 1;
		}
		if( ::GetAsyncKeyState(VK_F2) & 0x8000f && DemoMap->AKEY == 1)
		{
			((AStar *)astar)->setHeuristicMethod(MANHATTAN);
			DemoMap->FKEY = 2;
		}
		if( ::GetAsyncKeyState(VK_F3) & 0x8000f && DemoMap->AKEY == 1)
		{
			((AStar *)astar)->setHeuristicMethod(EUCLIDEAN);
			DemoMap->FKEY = 3;
		}
		if( ::GetAsyncKeyState(VK_F5) & 0x8000f )
		{
			DemoPlayer->setMaxDir(4);
			DemoMap->DKEY = 4;
		}
		if( ::GetAsyncKeyState(VK_F6) & 0x8000f )
		{
			DemoPlayer->setMaxDir(8);
			DemoMap->DKEY = 8;
		}

		if( ::GetAsyncKeyState(VK_F7) & 0x8000f )
		{
			DemoPlayer->setAi(astar);
			DemoMap->AKEY = 1;
		}
		if( ::GetAsyncKeyState(VK_F8) & 0x8000f )
		{
			DemoPlayer->setAi(dfs);
			DemoMap->AKEY = 2;
		}


		if( ::GetAsyncKeyState('1') & 0x8000f )
		{
			DemoMap->loadFromFile("map01.map");
			map_filename = "map01.map";
		}
		if( ::GetAsyncKeyState('2') & 0x8000f )
		{
			DemoMap->loadFromFile("map02.map");
			map_filename = "map02.map";
		}
		if( ::GetAsyncKeyState('3') & 0x8000f )
		{
			DemoMap->loadFromFile("map03.map");
			map_filename = "map03.map";
		}
		if( ::GetAsyncKeyState('4') & 0x8000f )
		{
			DemoMap->loadFromFile("map04.map");
			map_filename = "map04.map";
		}
		if( ::GetAsyncKeyState('5') & 0x8000f )
		{
			DemoMap->loadFromFile("map05.map");
			map_filename = "map05.map";
		}
		if( ::GetAsyncKeyState('6') & 0x8000f )
		{
			DemoMap->loadFromFile("map06.map");
			map_filename = "map06.map";
		}
		if( ::GetAsyncKeyState('7') & 0x8000f )
		{
			DemoMap->loadFromFile("map07.map");
			map_filename = "map07.map";
		}
		if( ::GetAsyncKeyState('8') & 0x8000f )
		{
			DemoMap->loadFromFile("map08.map");
			map_filename = "map08.map";
		}
		if( ::GetAsyncKeyState('9') & 0x8000f )
		{
			DemoMap->loadFromFile("map09.map");
			map_filename = "map09.map";
		}
	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		800, 800, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}