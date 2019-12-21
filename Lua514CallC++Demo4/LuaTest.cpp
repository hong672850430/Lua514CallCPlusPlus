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

int main(int argc, char *argv[])
{
	/* initialize Lua */
	L = lua_open();

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* run the script */
	luaL_dofile(L, "Test.lua");

	/* reset stack top*/
	lua_settop(L, 0);

	/* put "name" to stack */
	lua_getglobal(L, "name");

	StackDump(L, 1);

	/* isstring return not 0 is success */
	int isStr = lua_isstring(L, -1);
	if (isStr == 0)
	{
		printf("stack top is not string\n");
	}
	else
	{
		printf("stack top is string\n");
	}

	/* get stack top value*/
	const char* strName = lua_tostring(L, -1);

	/* call the add function */
	printf("name: %s\n", strName);

	/* put nameTable to stack top*/
	lua_getglobal(L, "nameTable");

	StackDump(L, 2);

	/* put sex to stack top*/
	lua_pushstring(L, "sex");
	/* set sex value*/
	lua_gettable(L, -2);

	lua_pushstring(L, "age");
	lua_gettable(L, -3);

	StackDump(L, 3);

	/* get statck -1 -2 vlaue*/
	int iAge = (int)lua_tointeger(L, -1);
	const char* strSex = lua_tostring(L, -2);
	
	printf("age: %d\n", iAge);
	printf("sex: %s\n", strSex);

	StackDump(L, 4);


	/* cleanup Lua */
	lua_close(L);


	/* pause */
	printf("Press enter to exit...");
	getchar();

	return 0;
}


