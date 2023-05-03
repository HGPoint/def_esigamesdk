#pragma once

#include "esigamesdk_private.h"
#include <dmsdk/sdk.h>

namespace dmEsiGameSDK {

enum MessageId
{
    MSG_PAY = 1,
    MSG_REWARDED = 2,
    MSG_INTERSTITIAL = 3,
    MSG_PRODUCT = 4,
    MSG_INITIALIZATION = 5,
    MSG_BANNER = 6,
};

enum MessageEvent
{
     EVENT_SUCCESS = 1,
     EVENT_FAILURE = 2,
     EVENT_MISSORDER = 3,
     EVENT_LOADED = 4,
     EVENT_FAILED = 5,
     EVENT_PLAY_START = 6,
     EVENT_PLAY_FAILED = 7,
     EVENT_VIDEO_CLOSED_REWARD = 8,
     EVENT_VIDEO_CLOSED_NOT_REWARD = 9,
     EVENT_PLAY_CLICKED = 10,
     EVENT_SHOW = 11,
     EVENT_CLOSE = 12,
     EVENT_ERROR = 13,
     EVENT_SHOWN = 14,
     EVENT_HIDDEN = 15,
     EVENT_SELECTION_GOOD_ERROR = 16,
     EVENT_COMPLETE = 17,
     EVENT_SIZE_UPDATE = 18,
     EVENT_PRODUCT = 19,
};

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char*json);

} //namespace dmEsiGameSDK
