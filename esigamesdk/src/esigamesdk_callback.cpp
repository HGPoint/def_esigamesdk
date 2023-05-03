#if defined(DM_PLATFORM_ANDROID)

#include "esigamesdk_callback_private.h"
#include <stdlib.h>

namespace dmEsiGameSDK {

//static dmScript::LuaCallbackInfo* m_luaCallback = 0x0;
static dmArray<dmScript::LuaCallbackInfo*> m_luaCallbacks;
static dmArray<CallbackData> m_callbacksQueue;
static dmMutex::HMutex m_mutex;

static void DestroyCallback()
{
    for (uint32_t i = 0; i < m_luaCallbacks.Size(); i++)
        dmScript::DestroyCallback(m_luaCallbacks[i]);
    m_luaCallbacks.SetCapacity(0);
    m_luaCallbacks.SetSize(0);
}

static void InvokeCallback(MessageId type, const char*json)
{
    for (uint32_t i = 0; i < m_luaCallbacks.Size(); i++) {

        if (!dmScript::IsCallbackValid(m_luaCallbacks[i]))
        {
            dmLogError("EsiGameSDK callback is invalid. Set new callback via `esigamesdk.set_callback()` funciton.");
            return;
        }

        lua_State* L = dmScript::GetCallbackLuaContext(m_luaCallbacks[i]);
        int top = lua_gettop(L);

        if (!dmScript::SetupCallback(m_luaCallbacks[i]))
        {
            return;
        }

        lua_pushnumber(L, type);
        dmScript::JsonToLua(L, json, strlen(json));

        int number_of_arguments = 3;

        int ret = dmScript::PCall(L, number_of_arguments, 0);
        (void)ret;
        dmScript::TeardownCallback(m_luaCallbacks[i]);

        assert(top == lua_gettop(L));
    }
}

void InitializeCallback()
{
    m_mutex = dmMutex::New();
}

void FinalizeCallback()
{
    dmMutex::Delete(m_mutex);
    DestroyCallback();
}

void SetLuaCallback(lua_State* L, int pos)
{
    int type = lua_type(L, pos);
    if (type == LUA_TNONE || type == LUA_TNIL)
    {
        //DestroyCallback();
    }
    else
    {
        if (m_luaCallbacks.Full())
            m_luaCallbacks.OffsetCapacity(1);

        m_luaCallbacks.Push(dmScript::CreateCallback(L, pos));
    }
}

void AddToQueueCallback(MessageId type, const char*json)
{
    CallbackData data;
    data.msg = type;
    data.json = json ? strdup(json) : NULL;

    DM_MUTEX_SCOPED_LOCK(m_mutex);
    if(m_callbacksQueue.Full())
    {
        m_callbacksQueue.OffsetCapacity(2);
    }
    m_callbacksQueue.Push(data);
}

void UpdateCallback()
{
    if (m_callbacksQueue.Empty())
    {
        return;
    }

    dmArray<CallbackData> tmp;
    {
        DM_MUTEX_SCOPED_LOCK(m_mutex);
        tmp.Swap(m_callbacksQueue);
    }

    for(uint32_t i = 0; i != tmp.Size(); ++i)
    {
        CallbackData* data = &tmp[i];
        InvokeCallback(data->msg, data->json);
        if(data->json)
        {
            free(data->json);
            data->json = 0;
        }
    }
}

} //namespace dmEsiGameSDK

#endif
