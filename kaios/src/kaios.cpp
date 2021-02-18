#define LIB_NAME "KaiOS"
#define MODULE_NAME "kaios"

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

#include <emscripten/emscripten.h> // for EM_ASM

static int kaios_PlaySound(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);

    const char* filepath = luaL_checkstring(L, 1);

    EM_ASM({ defold.playAudioFromURL(Module.UTF8ToString($0)); }, filepath);

	return 0;
}

static int kaios_Exit(lua_State* L)
{
	DM_LUA_STACK_CHECK(L, 0);

    EM_ASM(window.close());

	return 0;
}

static const luaL_reg Module_methods[] =
{
    {"exit", kaios_Exit},
    {"play_sound", kaios_PlaySound},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

#endif // defined(DM_PLATFORM_HTML5)

dmExtension::Result AppInitializeKaiOSExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeKaiOSExtension(dmExtension::Params* params)
{
    #if defined(DM_PLATFORM_HTML5)
	LuaInit(params->m_L);
	#else
	printf("Extension %s is not supported\n", MODULE_NAME);
	#endif

    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeKaiOSExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeKaiOSExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(KaiOS, LIB_NAME, AppInitializeKaiOSExtension, AppFinalizeKaiOSExtension, InitializeKaiOSExtension, 0, 0, FinalizeKaiOSExtension)
