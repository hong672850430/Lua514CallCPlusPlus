#include <stdio.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/* the Lua interpreter */
lua_State* L;

void StackDump(lua_State* L, int index = 0)
{
	return;
	printf("====== The contents of the stack from top to bottom: ======Log index: %d\n", index);

	int stackSize = lua_gettop(L);
	for (int i = stackSize; i > 0; --i)
	{
		printf("%d [%d]\t", i, -1 - (stackSize - i));
		int t = lua_type(L, i);
		switch (t)
		{
		case LUA_TSTRING:	/* strings */
			printf("%s: \t%s\n", lua_typename(L, t), lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:	/* booleans */
			printf("%s: \t%d\n", lua_typename(L, t), lua_toboolean(L, i));
			break;
		case LUA_TNUMBER:	/* numbers */
			printf("%s: \t%.2f\n", lua_typename(L, t), lua_tonumber(L, i));
			break;
		default:	/* other values */
			// LUA_TNONE
			// LUA_TNIL
			// LUA_TLIGHTUSERDATA
			// LUA_TTABLE
			// LUA_TFUNCTION
			// LUA_TUSERDATA
			printf("%s\n", lua_typename(L, t));
			break;
		}
	}
	printf("stackSize: %d\n", stackSize);
}

int main(int argc, char *argv[])
{
	L = lua_open();
	luaL_openlibs(L);

	luaL_dofile(L, "Test.lua");

	lua_getglobal(L, "name");
	const char* strName = lua_tostring(L, -1);
	printf("name: %s\n", strName);

	StackDump(L, 1);

	lua_pop(L, 1);
	
	lua_pushstring(L, "my name is lua modify ");	
	lua_setfield(L, LUA_GLOBALSINDEX, "name");
	StackDump(L, 2);

	lua_getglobal(L, "name");
	StackDump(L, 3);
	printf("setglobal name: %s\n", lua_tostring(L, -1));

	lua_settop(L, 0);

	lua_getglobal(L, "nameTable");

	//lua_pushstring(L, "sex");
	//lua_gettable(L, -2);

	//lua_pushstring(L, "age");
	//lua_gettable(L, -3);

	lua_getfield(L, -1, "sex");
	lua_getfield(L, -2, "age");

	StackDump(L, 4);

	printf("age: %d\n", lua_tointeger(L, -1));
	printf("sex: %s\n", lua_tostring(L, -2));
	
	//lua_pushstring(L, "age");
	//lua_pushnumber(L, 19);
	//lua_settable(L, 1);

	lua_pushnumber(L, 19);
	lua_setfield(L, 1, "age");

	//lua_pushstring(L, "age");
	//lua_gettable(L, 1);	

	lua_getfield(L, 1, "age");

	StackDump(L, 5);
	
	printf("setglobal age: %d\n", (int)lua_tointeger(L, -1));


	lua_getglobal(L, "PrintLuaLog");
	lua_pcall(L, 0, 0, 0);
	StackDump(L, 6);

	lua_getglobal(L, "AddIncrease");
	lua_pcall(L, 0, 0, 0);

	lua_getglobal(L, "PrintLuaLog");
	lua_pcall(L, 0, 0, 0);

	lua_settop(L, 0);
	lua_getglobal(L, "iVar");
	printf("iVar: %d\n", lua_tointeger(L, -1));

	lua_pop(L, 1);

	lua_getglobal(L, "nameTable");
	lua_getfield(L, -1, "age");

	printf("age: %d\n", lua_tointeger(L, -1));

	StackDump(L, 7);


	lua_close(L);

	printf("Press enter to exit...");
	getchar();

	return 0;
}


