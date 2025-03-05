#include <M5Unified.h>
#include <m5_module_fan.hpp>

M5ModuleFan moduleFan;
uint8_t deviceAddr = MODULE_FAN_BASE_ADDR;
uint8_t dutyCycle  = 80;
bool fan_status    = true;
M5Canvas canvas(&M5.Display);

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

void loop()
{
    int pwm_config_index  = moduleFan.getPWMFrequency();
    String pwm_config_str = "";

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

    M5.update();
    auto t = M5.Touch.getDetail();
    if (M5.BtnA.wasPressed()) {
        fan_status = !fan_status;
        if (fan_status) {
            moduleFan.setStatus(MODULE_FAN_ENABLE);
        } else {
            moduleFan.setStatus(MODULE_FAN_DISABLE);
        }
    }
    if (M5.BtnB.wasPressed()) {
        dutyCycle -= 10;
        if (dutyCycle < 0) {
            dutyCycle = 100;
        }
        moduleFan.setPWMDutyCycle(dutyCycle);
    }
    if (M5.BtnC.wasPressed()) {
        dutyCycle += 10;
        if (dutyCycle > 100) {
            dutyCycle = 0;
        }
        moduleFan.setPWMDutyCycle(dutyCycle);
    }
    delay(10);
}
