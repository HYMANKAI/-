## 这是一个一个简单的测温门禁

![](https://github.com/HYMANKAI/Access-control-system/blob/main/Overall%20picture.jpg)

这个工程使用Arduino Mega 2560作为主控，也可以使用Arduino UNO或者Arduino NANO  
采用了一个非接触式的测温探头(型号为 MLX90614 可采用IIC或UART通讯 )用于检测被测者的额温  
一个电动舵机模拟闸门  
12832(0.91英寸)OLED用来显示已通过的人数  
超声波模块HY-SRF05用于检测是否有人员靠近  
同时具有两个LED和一个按键（未在面包板上安装）  
默认串口打印当前温度和超声波的值。亦可扩展一个TTS语言合成模块，以实现语音提示，物质条件不足，留待以后扩展。若有其他开发者有相关模块，欢迎来完善本工程    

当没有人靠近闸门时，闸门关闭；当有人靠近闸门且体温低于38°C时，闸门开启，绿色LED亮起，同时OELD人员计数增加，若检测到行人温度异常，则闸门不会开启，且红色指示灯会亮起，仅当管理者按下PASS按键后红灯熄灭剩，余行人方可继续通过  

IIC PIN  
On an arduino UNO/arduino NANO:       A4(SDA), A5(SCL)  
On an arduino MEGA 2560: 20(SDA), 21(SCL)  

HY-SEF5  
SRF_IN   2  
SRF_OUT  3  

Digital PIN  
LED_R 5  
LED_G 4  
KEY   6  

UART0  
TX 1  
RX 2  

为最大限度节省引脚和空余出串口，这里采用了IIC总线同时挂载OOED和MLX90614  
具体演示视频见目录demo.mp4，源代码参考Source code.ino  
代码中使用的部分库  
```c
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <i2cmaster.h>
#include <Servo.h>
```
请于Arduino IDE的库管理器中检索安装  
有问题请在Issues中提出，我会尽快解决

---
### --BY HANYING
