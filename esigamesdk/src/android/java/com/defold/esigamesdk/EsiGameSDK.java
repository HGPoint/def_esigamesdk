package com.defold.esigamesdk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.esigame.common.YolooAdListener;
import com.esigame.common.YolooBridgeProductInfo;
import com.esigame.common.YolooGamingSDKBridge;
import com.esigame.common.YolooIapListener;
import com.esigame.common.YolooOrderInfo;
import com.yoloogames.adsdk.YolooAdError;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONObject;
import org.json.JSONException;
import org.json.JSONArray;

public class EsiGameSDK {

    private static final String TAG = "EsiGameSDK";

    private static final String MSG_KEY_EVENT = "event";

    private static final String MSG_KEY_GOODSID = "goodsId";
    private static final String MSG_KEY_ORDERID = "orderId";
    private static final String MSG_KEY_ITEM = "item";
    private static final String MSG_KEY_PAY_EXTAND = "payExtand";

    private static final String MSG_ERROR_CODE = "mCode";
    private static final String MSG_ERROR_MSG = "mErrMsg";

    private static final String MSG_INT_PARAM = "num";
    private static final String MSG_STR_PARAM = "str";

    private static final String MSG_KEY_X_POS = "x";
    private static final String MSG_KEY_Y_POS = "y";

    private static final int MSG_PAY = 1;
    private static final int MSG_REWARDED = 2;
    private static final int MSG_INTERSTITIAL = 3;
    private static final int MSG_PRODUCT = 4;
    private static final int MSG_INITIALIZATION = 5;
    private static final int MSG_BANNER = 6;

    private static final int EVENT_SUCCESS = 1;
    private static final int EVENT_FAILURE = 2;
    private static final int EVENT_MISSORDER = 3;

    private static final int EVENT_LOADED = 4;
    private static final int EVENT_FAILED = 5;
    private static final int EVENT_PLAY_START = 6;
    private static final int EVENT_PLAY_FAILED = 7;
    private static final int EVENT_VIDEO_CLOSED_REWARD = 8;
    private static final int EVENT_VIDEO_CLOSED_NOT_REWARD = 9;
    private static final int EVENT_PLAY_CLICKED = 10;
    private static final int EVENT_SHOW = 11;
    private static final int EVENT_CLOSE = 12;
    private static final int EVENT_ERROR = 13;
    private static final int EVENT_SHOWN = 14;
    private static final int EVENT_HIDDEN = 15;
    private static final int EVENT_SELECTION_GOOD_ERROR = 16;
    private static final int EVENT_COMPLETE = 17;
    private static final int EVENT_SIZE_UPDATE = 18;
    private static final int EVENT_PRODUCT = 19;

// UTILS START
    public static native void esigameAddToQueue(int msg, String json);

    // https://www.baeldung.com/java-json-escaping
    private String getJsonConversionErrorMessage(String messageText) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_ERROR_MSG, messageText);
            message = obj.toString();
        } catch (JSONException e) {
            message = "{ \"error\": \"Error while converting simple message to JSON.\" }";
        }
        return message;
    }

    private void sendSimpleMessage(int msg, int eventId) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, eventId);
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(msg, message);
    }

    private void sendOrderMessage(int msg, int eventId, YolooOrderInfo yolooOrderInfo) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, eventId);
            obj.put(MSG_KEY_ORDERID, yolooOrderInfo.getOrderId());
            obj.put(MSG_KEY_ITEM, yolooOrderInfo.getItem());
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(msg, message);
    }

    private void sendErrorMessage(int msg, int eventId, YolooAdError yolooAdError) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, eventId);
            obj.put(MSG_ERROR_CODE, yolooAdError.getCode());
            obj.put(MSG_ERROR_MSG, yolooAdError.getErrMsg());
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(msg, message);
    }

    private void sendProductMessage(int msg, int eventId, YolooBridgeProductInfo yolooProductInfo) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, eventId);
            obj.put(MSG_KEY_ITEM, yolooProductInfo.getItem());
            obj.put("price", yolooProductInfo.getPrice());
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(msg, message);
    }

    private void sendInfoMessage(int msg, int eventId, int i, String s) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, eventId);
            obj.put(MSG_INT_PARAM, i);
            if (s != null)
            {
                obj.put(MSG_STR_PARAM, s);
            }
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(msg, message);
    }

    private void sendBannerSizeChangedMessage(int sizeX, int sizeY) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put(MSG_KEY_EVENT, EVENT_SIZE_UPDATE);
            obj.put(MSG_KEY_X_POS, sizeX);
            obj.put(MSG_KEY_Y_POS, sizeY);
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        esigameAddToQueue(MSG_BANNER, message);
    }
// UTILS FINISH

    private final Activity mActivity;
    private YolooGamingSDKBridge yolooSdk;

    public EsiGameSDK(final Activity activity) {
        mActivity = activity;
    }

    public void initialize() {
        yolooSdk = YolooGamingSDKBridge.getInstance();

        YolooGamingSDKBridge.getInstance().initSDK(mActivity, "your appId", "your appKey");

        // Set listeners for advertising and in-app purchases
        yolooSdk.setAdListener(new YolooAdListener() {
            @Override
            public void onRewardedVideoAdLoaded() {
                Log.i(TAG,"onRewardedVideoAdLoaded");
                sendSimpleMessage(MSG_REWARDED, EVENT_LOADED);
            }

            @Override
            public void onRewardedVideoAdFailed(YolooAdError yolooAdError) {
                Log.i(TAG,"onRewardedVideoAdFailed" + yolooAdError);
                sendErrorMessage(MSG_REWARDED, EVENT_FAILED, yolooAdError);
            }

            @Override
            public void onRewardedVideoAdPlayStart(int i) {
                Log.i(TAG,"onRewardedVideoAdPlayStart" + i);
                sendInfoMessage(MSG_REWARDED, EVENT_PLAY_START, i, null);
            }

            @Override
            public void onRewardedVideoAdPlayFailed(YolooAdError yolooAdError) {
                Log.i(TAG,"onRewardedVideoAdPlayFailed" + yolooAdError);
                sendErrorMessage(MSG_REWARDED, EVENT_PLAY_FAILED, yolooAdError);
            }

            @Override
            public void onRewardedVideoAdClosed(boolean b) {
                Log.i(TAG,"onRewardedVideoAdClosed" + b);
                if (b) {
                    sendSimpleMessage(MSG_REWARDED, EVENT_VIDEO_CLOSED_REWARD);
                }
                else
                {
                    sendSimpleMessage(MSG_REWARDED, EVENT_VIDEO_CLOSED_NOT_REWARD);
                }
            }

            @Override
            public void onRewardedVideoAdPlayClicked() {
                Log.i(TAG,"onRewardedVideoAdPlayClicked");
                sendSimpleMessage(MSG_REWARDED, EVENT_PLAY_CLICKED);
            }

            @Override
            public void onInterstitialAdLoaded() {
                Log.i(TAG,"onInterstitialAdLoaded");
                sendSimpleMessage(MSG_INTERSTITIAL, EVENT_LOADED);
            }

            @Override
            public void onInterstitialAdLoadFail(YolooAdError yolooAdError) {
                Log.i(TAG,"onInterstitialAdLoadFail" + yolooAdError);
                sendErrorMessage(MSG_INTERSTITIAL, EVENT_FAILED, yolooAdError);
            }

            @Override
            public void onInterstitialAdClicked() {
                Log.i(TAG,"onInterstitialAdClicked");
                sendSimpleMessage(MSG_INTERSTITIAL, EVENT_PLAY_CLICKED);
            }

            @Override
            public void onInterstitialAdShow() {
                Log.i(TAG,"onInterstitialAdShow");
                sendSimpleMessage(MSG_INTERSTITIAL, EVENT_SHOW);
            }

            @Override
            public void onInterstitialAdClose() {
                Log.i(TAG,"onInterstitialAdClose");
                sendSimpleMessage(MSG_INTERSTITIAL, EVENT_CLOSE);
            }

            @Override
            public void onInterstitialAdVideoError(YolooAdError yolooAdError) {
                Log.i(TAG,"onInterstitialAdVideoError" + yolooAdError);
                sendErrorMessage(MSG_INTERSTITIAL, EVENT_ERROR, yolooAdError);
            }

            @Override
            public void onBannerShown() {
                Log.i(TAG,"onBannerShown");
                // TODO
                //int adViewWidth = mActivity.getSystemService("window").getDefaultDisplay().getCurrentWindowMetrics().getBounds().width();
                //int adViewHeight = (int)((float)adViewWidth / 5.0F) - 1;
                //sendBannerSizeChangedMessage(adViewWidth, adViewHeight);
            }

            @Override
            public void onBannerHidden() {
                Log.i(TAG, "onBannerHidden");
                sendSimpleMessage(MSG_BANNER, EVENT_HIDDEN);
            }
            // Implement methods for handling ad-related events
        });

        yolooSdk.setIapListener(new YolooIapListener() {
            @Override
            public void productsIsLoaded(List<YolooBridgeProductInfo> list) {
            }

            @Override
            public void paySuccess(YolooOrderInfo yolooOrderInfo) {
                Log.i(TAG, "paySuccess: ");
                sendOrderMessage(MSG_PAY, EVENT_SUCCESS, yolooOrderInfo);
            }

            @Override
            public void payFailure(int i, String s) {
                Log.i(TAG, "payFailure: ");
                sendInfoMessage(MSG_PAY, EVENT_FAILURE, i, s);
            }

            @Override
            public void payMissorder(YolooOrderInfo yolooOrderInfo) {
                Log.i(TAG, "payMissorder: ");
                sendOrderMessage(MSG_PAY, EVENT_MISSORDER, yolooOrderInfo);
            }
            // Implement methods for handling in-app purchase events
        });


        sendSimpleMessage(MSG_INITIALIZATION, EVENT_COMPLETE);
    }

    public void loadVideoAd() {
        yolooSdk.loadVideoAd();
    }

    public void showVideo(final String placement) { 
        yolooSdk.showVideo(placement);
    }

    public boolean videoIsReady() {
        return yolooSdk.videoIsReady();
    }

    public void loadInterstitialAd() {
        yolooSdk.loadInterstitialAd();
    }

    public void showInterstitialAd() {
        yolooSdk.showInterstitialAd();
    }

    public boolean interstitialIsReady() {
        return yolooSdk.interstitialIsReady();
    }

    public void showBanner(int bannerLocation) {
        yolooSdk.showBanner(bannerLocation); // Replace bannerLocation with the desired banner position
    }

    public void hiddenBanner() {
        yolooSdk.hiddenBanner();
    }

    public void getProduct(String product_id) {
        YolooBridgeProductInfo product = yolooSdk.getProduct(product_id);
        sendProductMessage(MSG_PAY, EVENT_PRODUCT, product);
    }

    public void getProducts(String product_ids) {
        //ToDo: find new way to pass products
        try {
            JSONArray arr = new JSONArray(product_ids);
            JSONArray a = new JSONArray();
            for (int i = 0; i < arr.length(); i++) {
                sendProductMessage(MSG_PAY, EVENT_PRODUCT, yolooSdk.getProduct(arr.getString(i)));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        sendSimpleMessage(MSG_PRODUCT, EVENT_SUCCESS);
    }

    public void payNow(String product_id) {
        yolooSdk.payNow(product_id);
    }

    public void onEnterGame() {
        yolooSdk.onEnterGame();
    }

    public void onEnterLaunchLoading() {
        yolooSdk.onEnterLaunchLoading();
    }

    public void onUserGuideStep(String step) {
        yolooSdk.onUserGuideStep(step);
    }

    public void setUserLevel(int level) {
        yolooSdk.setUserLevel(level);
    }

    public void startLevel(String level) {
        yolooSdk.startLevel(level);
    }
    
    public void finishLevel(String level) {
        yolooSdk.finishLevel(level);
    }

    public void failLevel(String level) {
        yolooSdk.failLevel(level);
    }

    public void event(String event_id) {
        yolooSdk.event(event_id);
    }

    public void eventMap(String event_id, String event_data) {
        yolooSdk.eventMap(event_id, event_data);
    }

    public void getCloudConfig(String config_key, String default_value) {
        String configValue = yolooSdk.getCloudConfig(config_key, default_value);
    }
}