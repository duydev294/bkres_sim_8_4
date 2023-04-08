#include <Arduino.h>
#include <IRremote.h>
#include "common.h"

#define led_pin 11
#define RECV_PIN 9
IRrecv irrecv(RECV_PIN);
decode_results results;

volatile int led_brightness = 255;    // Mức sáng ban đầu là 0
bool led_on = false;        // Trạng thái ban đầu là tắt
bool led_blink = false;     // Trạng thái ban đầu là không nhấp nháy
bool led_fade = false;      // Trạng thái ban đầu là không sáng dần tắt dần
bool led_up = false;        // Trạng thái ban đầu là không tăng độ sáng
bool led_down = false;      // Trạng thái ban đầu là không giảm độ sáng

unsigned long previousMillis = 0;
const long interval = 40;
volatile int brightness = 255; // Giá trị độ sáng hiện tại của LED
int fadeAmount = 5; // Giá trị tăng hoặc giảm độ sáng
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led_pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) { // Nếu nhận được tín hiệu hồng ngoại
    Serial.println(results.value); // In ra giá trị tín hiệu hồng ngoại dưới dạng HEX
    irrecv.decode(&results);
    irrecv.resume(); // Tiếp tục chờ đợi tín hiệu mới
    switch ( results.value)
  {

  case /* constant-expression */one: 
    /* code */
    Serial.println("Turn on!");
    led_on = true;
    led_blink = false;
    led_fade = false;
    led_up = false;
    led_down = false;
    break;
  case two:
    Serial.println("Blink");
    led_on = false;
    led_blink = true;
    led_fade = false;
    led_up = false;
    led_down = false;
    break;
  case three:
    Serial.println("Breathe!");
    led_on = false;
    led_blink = false;
    led_fade = true;
    led_up = false;
    led_down = false;
    break;
  case UP:
    Serial.println("Light UP");
    led_up = true;
    led_down = false;
    break;
  case DOWN:
    Serial.println("Light DOWN");
    led_down = true;
    led_up= false;
    break;
  case OK:
    Serial.println("Turn off");
    led_on = false;
    led_blink = false;
    led_fade = false;
    led_up = false;
    led_down = false;
    break;
  }
  
  }
  if(led_up){
      led_brightness += 5;
    if (led_brightness > 255) {
      led_brightness = 255;
    }
    
    Serial.print("Bright:");
    Serial.println(led_brightness);
    led_up = false;
  }
   if(led_down){
     led_brightness -= 5;
    if (led_brightness < 0) {
    led_brightness = 0;
    }
    Serial.print("Bright:");
    Serial.println(led_brightness);
    led_down = false;
  }
  if (led_on) {
    analogWrite(led_pin, led_brightness);
  } else if (led_blink) {
    digitalWrite(led_pin, (millis() / 500) % 2);    // Nhấp nháy theo chu kỳ 0.5s
  } else if (led_fade ) {
  //    unsigned long currentMillis = millis(); // Lấy thời điểm hiện tại

  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis; // Cập nhật thời điểm trước đó

  //   brightness += fadeAmount; // Tăng hoặc giảm độ sáng

  //   if (brightness <= 0 || brightness >= 255) {
  //     fadeAmount = -fadeAmount; // Đảo chiều tăng hoặc giảm độ sáng
  //   }

  //   analogWrite(led_pin, brightness); // Ghi giá trị độ sáng lên đèn LED
  analogWrite(led_pin, map(sin(millis() / 2000.0 * PI), -1, 1, 0, 255));
  } 
  else {
    analogWrite(led_pin, 0);
  }
  
  
}

