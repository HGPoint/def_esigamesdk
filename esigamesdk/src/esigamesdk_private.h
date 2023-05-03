#pragma once

namespace dmEsiGameSDK {

enum BannerSize
{
    SIZE_BANNER =           0,
    SIZE_LEADER =           1,
    SIZE_MREC =             2,
};

enum BannerPosition
{
    POS_NONE =              0,
    POS_TOP_LEFT =          1,
    POS_TOP_CENTER =        2,
    POS_TOP_RIGHT =         3,
    POS_BOTTOM_LEFT =       4,
    POS_BOTTOM_CENTER =     5,
    POS_BOTTOM_RIGHT =      6,
    POS_CENTER =            7
};

void Initialize_Ext();
void Initialize();

void CheckOrder();
void LoadVideoAd();
void ShowVideo(const char* unitId);
void LoadInterstitialAd();
void ShowInterstitialAd();
void GetProducts(const char* product_ids);
void PayNow(const char* unitId);
bool InterstitialIsReady();
bool InterstitialImageIsReady();
bool loadBanner();
void showBanner(int bannerLocation);
bool hiddenBanner();

void onUserGuideStep(const char* step); 
void setUserLevel(int level);
void startLevel(const char* level);
void finishLevel(const char* level);
void failLevel(const char* level);
void startGameLevel(const char* level);
void finishGameLevel(const char* level);
void failGameLevel(const char* level);

//void showPolicyPage();

bool videoIsReady();
void getProduct(const char* product_id);
void onEnterGame();
void onEnterLaunchLoading();
void event_(const char* event_id);
void eventMap(const char* event_id, const char* event_data);
void getCloudConfig(const char* config_key, const char* default_value);

} //namespace dmEsiGameSDK
