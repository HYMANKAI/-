## 这是一个一个简单的测温门禁

![](https://github.com/HYMANKAI/Access-control-system/blob/main/Overall%20picture.jpg)

这个工程使用Arduino Mega 2560作为主控，也可以使用Arduino UNO或者Arduino NANO  
采用了一个非接触式的测温探头(型号为 MLX90614 可采用IIC或UART通讯 )用于检测被测者的额温  
一个电动舵机模拟闸门  
12832(0.91英寸)OLED用来显示已通过的人数  
超声波模块HY-SRF05用于检测是否有人员靠近  
同时具有两个LED和一个按键（未在面包板上安装）  

为最大限度节省引脚和空余出串口，这里采用了IIC总线同时挂载OOED和MLX90614  
具体演示视频见目录demo.mp4，源代码参考Source code.ino  
代码中使用的部分库  
、、、c
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <i2cmaster.h>
#include <Servo.h>
、、、



---
### --BY HANYING
