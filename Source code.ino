#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <i2cmaster.h>
#include <Servo.h>

Servo myservo;  // 定义Servo对象来控制

#define LED_R 5
#define LED_G 4
#define KEY   6
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define SRF_IN   2
#define SRF_OUT  3
unsigned int number=0;
#define uint16_t unsigned int
#define iic_add  0xa4
typedef struct
{
    float e;
    float to;
    float ta;
    float toir;
} gyir;
unsigned char Re_buf;
unsigned char sign=0;
gyir my_ir;
uint16_t delay_t=0;
byte color=0,rgb_data[3]={0};

void setup() 
{
  myservo.attach(7);
  Serial.begin(115200);
  pinMode(SRF_IN,INPUT);
  pinMode(SRF_OUT,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(KEY,INPUT);
  digitalWrite(LED_G,HIGH);
  digitalWrite(LED_R,HIGH);
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  byte td=0;
  i2c_init();
  iic_read(0x02,&td,1);
  switch(td)
  {
     case 0:delay_t=1010;break;
     case 1:delay_t=510;break;
     case 2:delay_t=210;break;
     case 3:delay_t=110;break;
   }
   delay(1); 
   iic_write(0x07,95);
   delay(1); 
   iic_write(0x06,95);
   delay(delay_t); 
   myservo.write(0);
}

void loop() 
{
  int FLAG = 1;
  float distance = Get_distance(5);
  float temperature = Get_temperature();
  OLED_SHOW(number);
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.print("  temperature: ");
  Serial.println(temperature);
  if(temperature >38)
  {
      while(FLAG)
      {
          if(digitalRead(KEY)==HIGH)
          {
            FLAG = 0;
          }         
          myservo.write(0);              
          digitalWrite(LED_R,LOW);
      }
      digitalWrite(LED_R,HIGH);
      FLAG = 1;
  }
  if((temperature>30)and (temperature<38) and (distance<30))
  {
      myservo.write(90);
      digitalWrite(LED_G,LOW);
      delay(2000);
      myservo.write(0);
      digitalWrite(LED_G,HIGH);
      number++;
  }
  else
  {
    myservo.write(0);
  }                 
}
float Get_temperature()
{
 unsigned char data[16]={0};
 if(!sign)
 {
   iic_read(0x07,data,7);
   my_ir.to=(data[1]<<8)|data[2];
 }
 delay(delay_t);
 return  my_ir.to/100;
}
float Get_distance(int times)
{
  float temp_val=0,temp=0;
  int t;
  for(t=0;t<times;t++)
  {
    digitalWrite(SRF_OUT, LOW);
    delayMicroseconds(2);
    digitalWrite(SRF_OUT, HIGH);
    delayMicroseconds(10);
    digitalWrite(SRF_OUT, LOW); 
    temp = (pulseIn(SRF_IN, HIGH)/58);
    delay(20);
    if(temp<0)
    {
      temp = 0;
      times = times-1;
    }
    temp_val = temp_val+temp;
  }
  return temp_val/times;
}
void OLED_SHOW(int temp1)
{
  char buffer[30];
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.println("The number is ");
  display.setTextSize(2);
  display.setCursor(20, 16);
  sprintf(buffer,"%04d", temp1);
  display.println(buffer);
  display.display();
}
void iic_read(unsigned char add,unsigned char *data,unsigned char len)
{
  i2c_start_wait(iic_add);
  i2c_write(add);
  i2c_start_wait(iic_add+1);
  while(len-1)
  {
   *data++=i2c_readAck();
   len--;
   }
   *data=i2c_readNak();
   i2c_stop();
}
void iic_write( char add,unsigned char data)
{
  i2c_start_wait(iic_add);
  i2c_write(add);
  i2c_write(data);
  i2c_stop();
}
