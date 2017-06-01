// C++调用Lua
#include <iostream>
#include <string.h>
using namespace std;

//	加载Lua53.lib
#pragma comment(lib, "..\\lib\\Lua53.lib")

extern "C"
{
#include "Lua/lua.h"
#include "Lua/lauxlib.h"
#include "Lua/lualib.h"
};


lua_State* L;

static int Lua2C_Add( lua_State* L )
{
	//	返回栈中元素的个数
	int nCount = lua_gettop( L );
	int nNum = 0;
	for ( int nIdx = 1; nIdx <= nCount; nIdx++ )
	{
		if ( !lua_isnumber( L, nIdx ) )
		{
			lua_pushstring( L, " Error" );
			lua_error( L );
		}
		nNum += (int)lua_tonumber( L, nIdx ); 
	}
	lua_pushnumber( L, nNum );
	return 1;
}

void main( )
{
	int nSum = 0;
	
	L = luaL_newstate( );
	luaopen_base( L );
	luaL_openlibs( L );
	//	注册接口
	lua_register( L, "Lua2C_Add", Lua2C_Add);
	//	加载lua文件
	int nRet = luaL_loadfile(L, "..\\code\\Lua2C.lua");
	if ( nRet )
	{
		cout << " load file error " << endl;
		return ;
	}

	//	运行lua文件
	nRet = lua_pcall( L, 0, 0, 0);
	if ( nRet )
	{
		cout << "pcall error." << endl;
		return;
	}

	lua_getglobal( L, "sum" );
	cout << " sum = " << lua_tonumber( L, -1) << endl;

	lua_pop( L, 1);
	lua_close( L );

	system("pause");
	return;
}