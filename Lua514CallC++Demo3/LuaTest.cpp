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


static int Average(lua_State *L)
{
	/* get number of arguments */
	int n = lua_gettop(L);
	double sum = 0;

	StackDump(L, 1);
	/* loop through each argument */
	for (int i = 1; i <= n; ++i)
	{
		sum += lua_tonumber(L, i);
	}

	/* push the average */
	lua_pushnumber(L, sum / n);

	/* push the sum */
	lua_pushnumber(L, sum);

	StackDump(L, 2);
	/* return the number of results */
	return 2;
}


int main(int argc, char *argv[])
{
	/* initialize Lua */
	L = lua_open();

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* register our function */
	lua_register(L, "average", Average);
	//lua_pushcfunction(L, Average);
	//lua_setglobal(L, "average");

	StackDump(L, 3);

	/* run the script */
	luaL_dofile(L, "Test.lua");

	StackDump(L, 4);

	/* cleanup Lua */
	lua_close(L);

	/* pause */
	printf("Press enter to exit...");
	getchar();

	return 0;
}


