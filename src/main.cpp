#include <M5Unified.h>
#include <m5_module_fan.hpp>

M5ModuleFan moduleFan;
void setup()
{
    M5.begin();
    Serial.begin(115200);
    while (!moduleFan.begin(&Wire1, MODULE_FAN_BASE_ADDR, 12, 11, 400000)) {
        Serial.printf("Module FAN Init faile\r\n");
    }
    uint8_t dutyCycle  = 10;
    moduleFan.setPWMDutyCycle(dutyCycle);
    moduleFan.setPWMFrequency(PWM_1KHZ);
    moduleFan.setStatus(MODULE_FAN_ENABLE);
}

void loop()
{
    Serial.printf("\r\n");
    Serial.printf(" {\r\n");
    Serial.printf("    Work Status      : %d\r\n", moduleFan.getStatus());
    Serial.printf("    PWM  Frequency   : %d\r\n", moduleFan.getPWMFrequency());
    Serial.printf("    PWM  Duty Cycle  : %d\r\n", moduleFan.getPWMDutyCycle());
    Serial.printf("    RPM              : %d\r\n", moduleFan.getRPM());
    Serial.printf("    Signal Frequency : %d\r\n", moduleFan.getSignalFrequency());
    Serial.printf("    Firmware Version : %d\r\n", moduleFan.getFirmwareVersion());
    Serial.printf("         I2C Addrres : 0x%02X\r\n", moduleFan.getI2CAddress());
    Serial.printf("                             }\r\n");
    delay(500);
}