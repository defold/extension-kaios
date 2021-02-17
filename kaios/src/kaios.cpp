#define LIB_NAME "KaiOS"
#define MODULE_NAME "kaios"

#include <dmsdk/sdk.h>

static const luaL_reg Module_methods[] =
{
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeKaiOSExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeKaiOSExtension(dmExtension::Params* params)
{
    LuaInit(params->m_L);
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
