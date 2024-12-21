#include <Arduino.h>
#include <blink.h>

unsigned long blink_rate = 500;
void blink_it()
{
    irrecv.resume();
    pinMode(LED,OUTPUT);
    while (irrecv.isIdle())
    {

        if (irrecv.decode(&results))
        {
            irrecv.resume();
            if (results.value == SONY_TV_PAUSE) {
                digitalWrite(LED,LOW);
                return;
            } else if(results.value == SONY_TV_VOL_PLUS && blink_rate > 100) {
                blink_rate -=50;
            } else if(results.value == SONY_TV_VOL_MINUS)
            {
                blink_rate += 500;
            } else if(results.value == SONY_TV_BEGIN) {
                blink_rate = 500;
            }
        }
        delay(blink_rate);
        digitalWrite(LED,HIGH);
        delay(blink_rate);
        digitalWrite(LED, LOW);
    }
}
