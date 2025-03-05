/**
 * @file main.cpp
 * @brief M5Stack用ファンモジュール制御プログラム
 * @details M5Stackを使用してファンモジュールの回転速度や動作状態を制御・表示するプログラムです
 * @author M5Stack
 * @date 2025/03/05
 */

#include <M5Unified.h>
#include <m5_module_fan.hpp>

/// @brief ファンモジュールのインスタンス
M5ModuleFan moduleFan;
/// @brief ファンモジュールのI2Cアドレス
uint8_t deviceAddr = MODULE_FAN_BASE_ADDR;
/// @brief ファンのデューティサイクル（0-100%）
uint8_t dutyCycle  = 80;
/// @brief ファンの動作状態（true: 動作中、false: 停止中）
bool fan_status    = true;
/// @brief 表示用キャンバス
M5Canvas canvas(&M5.Display);

/**
 * @brief 初期化処理を行う関数
 * @details M5Stackの初期化、シリアル通信の設定、ディスプレイの設定、ファンモジュールの初期化を行います
 */
void setup()
{
    M5.begin();
    Serial.begin(115200);
    canvas.createSprite(320, 240);
    canvas.setFont(&fonts::lgfxJapanGothic_24);
    canvas.setTextDatum(top_center);
    canvas.setTextColor(WHITE);

    while (!moduleFan.begin(&Wire1, deviceAddr, 12, 11, 400000)) {
        Serial.printf("Module FAN Init faile\r\n");
        canvas.drawString("Module FAN Init faile", 160, 120);
        canvas.pushSprite(0, 0);
        delay(1000);
    }

    // Set the fan to rotate at 80% duty cycle
    moduleFan.setPWMDutyCycle(dutyCycle);
    moduleFan.setPWMFrequency(PWM_1KHZ);
    moduleFan.setStatus(MODULE_FAN_ENABLE);
}

/**
 * @brief メインループ処理を行う関数
 * @details ファンの状態を表示し、ボタン入力に応じてファンの動作を制御します
 * - ボタンA: ファンのON/OFF切り替え
 * - ボタンB: デューティサイクルを10%ずつ減少
 * - ボタンC: デューティサイクルを10%ずつ増加
 */
void loop()
{
    /// @brief 現在のPWM周波数設定インデックス
    int pwm_config_index  = moduleFan.getPWMFrequency();
    /// @brief PWM周波数の文字列表現
    String pwm_config_str = "";

    // PWM周波数インデックスを文字列に変換
    switch (pwm_config_index) {
        case PWM_1KHZ:
            pwm_config_str = "1KHz";
            break;
        case PWM_12KHZ:
            pwm_config_str = "12KHz";
            break;
        case PWM_24KHZ:
            pwm_config_str = "24KHz";
            break;
        case PWM_48KHZ:
            pwm_config_str = "48KHz";
            break;
    }
    canvas.setCursor(0, 10);
    canvas.clear();
    canvas.printf("Work Status    :%s\r\n", moduleFan.getStatus() == MODULE_FAN_ENABLE ? "RUNNING" : "STOP");
    canvas.printf("PWM  Frequency :%s\r\n", pwm_config_str.c_str());
    canvas.printf("PWM  Duty Cycle:%d%%\r\n", moduleFan.getPWMDutyCycle());
    canvas.printf("RPM            :%drpm\r\n", moduleFan.getRPM());
    canvas.pushSprite(0, 0);

    // ボタン状態の更新
    M5.update();
    auto t = M5.Touch.getDetail();
    // ボタンAが押された場合：ファンのON/OFF切り替え
    if (M5.BtnA.wasPressed()) {
        fan_status = !fan_status;
        if (fan_status) {
            moduleFan.setStatus(MODULE_FAN_ENABLE);
        } else {
            moduleFan.setStatus(MODULE_FAN_DISABLE);
        }
    }
    // ボタンBが押された場合：デューティサイクルを10%ずつ減少
    if (M5.BtnB.wasPressed()) {
        dutyCycle -= 10;
        if (dutyCycle < 0) {
            dutyCycle = 100;
        }
        moduleFan.setPWMDutyCycle(dutyCycle);
    }
    // ボタンCが押された場合：デューティサイクルを10%ずつ増加
    if (M5.BtnC.wasPressed()) {
        dutyCycle += 10;
        if (dutyCycle > 100) {
            dutyCycle = 0;
        }
        moduleFan.setPWMDutyCycle(dutyCycle);
    }
    delay(10);
}
