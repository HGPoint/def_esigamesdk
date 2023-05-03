// esigamesdk.cpp
#define EXTENSION_NAME EsiGameSDK
#define LIB_NAME "EsiGameSDK"
#define MODULE_NAME "esigamesdk"

#include <dmsdk/sdk.h>
#define DM_PLATFORM_ANDROID
#if defined(DM_PLATFORM_ANDROID)

//#include "utils/LuaUtils.h"
#include "esigamesdk_private.h"
#include "esigamesdk_callback_private.h"

namespace dmEsiGameSDK {

static int Lua_Initialize(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    Initialize();
    return 0;
}

static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Reverse(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    char* str = (char*)luaL_checkstring(L, 1);

    int len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        const char a = str[i];
        const char b = str[len - i - 1];
        str[i] = b;
        str[len - i - 1] = a;
    }

    lua_pushstring(L, str);

    return 1;
}

static int Lua_CheckOrder(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    CheckOrder();
    return 0;
}

static int Lua_LoadVideoAd(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    LoadVideoAd();
    return 0;
}

static int Lua_ShowVideo(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for ShowVideo UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* unitId_lua = luaL_checkstring(L, 1);

    ShowVideo(unitId_lua);
    return 0;
}

static int Lua_LoadInterstitialAd(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    LoadInterstitialAd();
    return 0;
}

static int Lua_ShowInterstitialAd(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    ShowInterstitialAd();
    return 0;
}

static int Lua_GetProducts(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Lua_GetProducts product_ids variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* unitId_lua = luaL_checkstring(L, 1);

    GetProducts(unitId_lua);
    return 0;
}

static int Lua_PayNow(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for PayNow UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* unitId_lua = luaL_checkstring(L, 1);

    PayNow(unitId_lua);
    return 0;
}

static int Lua_InterstitialIsReady(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    lua_pushboolean(L, InterstitialIsReady());
    return 1;
}

static int Lua_InterstitialImageIsReady(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    lua_pushboolean(L, InterstitialImageIsReady());
    return 1;
}

static int Lua_videoIsReady(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    lua_pushboolean(L, videoIsReady());
    return 1;
}

static int Lua_loadBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    loadBanner();
    return 0;
}

template <void (*T)(int)>
static int Lua_INT(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    T(luaL_checkinteger(L, 1));
    return 0;
}

static int Lua_hiddenBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    hiddenBanner();
    return 0;
}

template <void (*T)(const char*)>
static int Lua_PCSTR(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for function UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* unitId_lua = luaL_checkstring(L, 1);

    T(unitId_lua);
    return 0;
}

template <void (*T)()>
static int Lua_VOID(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    T();
    return 0;
}
/*
static int Lua_showPolicyPage(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    showPolicyPage();
    return 0;
}
*/

static int Lua_getCloudConfig(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for getCloudConfig config_key variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    if (lua_type(L, 2) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for getCloudConfig default_value variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, msg);
        return 0;
    }
    getCloudConfig(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
    return 0;
}

static int Lua_eventMap(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for eventMap event_id variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    if (lua_type(L, 2) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for eventMap event_data variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
        luaL_error(L, msg);
        return 0;
    }
    eventMap(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"set_callback", Lua_SetCallback},
    //{"check_order", Lua_CheckOrder},
    {"load_video_ad", Lua_LoadVideoAd},
    {"show_video", Lua_ShowVideo},
    {"load_interstitial_ad", Lua_LoadInterstitialAd},
    {"show_interstitial_ad", Lua_ShowInterstitialAd},
    {"get_products", Lua_GetProducts},
    {"pay_now", Lua_PayNow},
    {"interstitial_is_ready", Lua_InterstitialIsReady},
    //{"interstitial_image_is_ready", Lua_InterstitialImageIsReady},
    //{"load_banner", Lua_loadBanner},
    {"show_banner", Lua_INT<showBanner>},
    {"hide_banner", Lua_hiddenBanner},

    {"on_user_guide_step", Lua_PCSTR<onUserGuideStep>},
    {"set_user_level", Lua_INT<setUserLevel>},
    {"start_level", Lua_PCSTR<startLevel>},
    {"finish_level", Lua_PCSTR<finishLevel>},
    {"fail_level", Lua_PCSTR<failLevel>},
    //{"start_game_level", Lua_PCSTR<startGameLevel>},
    //{"finish_game_level", Lua_PCSTR<finishGameLevel>},
    //{"fail_game_level", Lua_PCSTR<failGameLevel>},
//    {"show_policy_page", Lua_showPolicyPage},
 
    {"video_is_ready", Lua_videoIsReady},
    {"get_product", Lua_PCSTR<getProduct>},
    {"on_enter_game", Lua_VOID<onEnterGame>},
    {"on_enter_launch_loading", Lua_VOID<onEnterLaunchLoading>},
    {"event", Lua_PCSTR<event_>},
    {"eventMap", Lua_eventMap},
    {"get_cloud_config", Lua_getCloudConfig},

    //{"reverse", Reverse},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(MSG_PAY)
    SETCONSTANT(MSG_REWARDED)
    SETCONSTANT(MSG_INTERSTITIAL)
    SETCONSTANT(MSG_PRODUCT)
    SETCONSTANT(MSG_INITIALIZATION)
    SETCONSTANT(MSG_BANNER)

    SETCONSTANT(EVENT_SUCCESS)
    SETCONSTANT(EVENT_FAILURE)
    SETCONSTANT(EVENT_MISSORDER)
    SETCONSTANT(EVENT_LOADED)
    SETCONSTANT(EVENT_FAILED)
    SETCONSTANT(EVENT_FAILED)
    SETCONSTANT(EVENT_PLAY_START)
    SETCONSTANT(EVENT_PLAY_FAILED)
    SETCONSTANT(EVENT_VIDEO_CLOSED_REWARD)
    SETCONSTANT(EVENT_VIDEO_CLOSED_NOT_REWARD)
    SETCONSTANT(EVENT_PLAY_CLICKED)
    SETCONSTANT(EVENT_SHOW)
    SETCONSTANT(EVENT_CLOSE)
    SETCONSTANT(EVENT_ERROR)
    SETCONSTANT(EVENT_SHOWN)
    SETCONSTANT(EVENT_HIDDEN)
    SETCONSTANT(EVENT_SELECTION_GOOD_ERROR)
    SETCONSTANT(EVENT_COMPLETE)
    SETCONSTANT(EVENT_SIZE_UPDATE)
    SETCONSTANT(EVENT_PRODUCT)

#undef SETCONSTANT

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeMyExtension(dmExtension::Params* params)
{
    dmLogInfo("Try Register %s Extension...\n", MODULE_NAME);
    LuaInit(params->m_L);
    Initialize_Ext();
    InitializeCallback();
    dmLogInfo("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeMyExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateMyExtension(dmExtension::Params* params)
{
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

} //namespace dmEsiGameSDK

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmEsiGameSDK::AppInitializeMyExtension, dmEsiGameSDK::AppFinalizeMyExtension, dmEsiGameSDK::InitializeMyExtension, dmEsiGameSDK::UpdateMyExtension, 0, dmEsiGameSDK::FinalizeMyExtension)

#else

static dmExtension::Result InitializeEsiGameSDK(dmExtension::Params* params)
{
    dmLogInfo("Registered extension EsiGameSDK (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeEsiGameSDK(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeEsiGameSDK, 0, 0, FinalizeEsiGameSDK)

#endif // IOS/Android