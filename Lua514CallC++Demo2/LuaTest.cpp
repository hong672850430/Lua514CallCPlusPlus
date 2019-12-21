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


int LuaAdd(int x,int y)
{
	int sum;

	/* the function name */
	lua_getglobal(L, "add");
	StackDump(L, 1);
	/* the first argument */
	lua_pushnumber(L, x);

	/* the second argument */
	lua_pushnumber(L, y);

	/* print stack contents */
	StackDump(L ,2);

	/* call the function with 2 arguments, return 1 result */
	lua_call(L, 2, 1);

	/* print stack contents */
	StackDump(L, 3);

	/* get the result */
	sum = (int)lua_tointeger(L, -1);

	lua_pop(L, 1);

	/* print stack contents */
	StackDump(L, 4);

	return sum;
}

int main(int argc, char *argv[])
{
	int sum;

	/* initialize Lua */
	L = lua_open();

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* run the script */
	luaL_dofile(L, "Test.lua");

	/* call the add function */
	sum = LuaAdd(2014, 15);

	/* call the add function */
	printf("The sum is: %d\n", sum);

	/* cleanup Lua */
	lua_close(L);

	/* pause */
	printf("Press enter to exit...");
	getchar();

	return 0;
}


