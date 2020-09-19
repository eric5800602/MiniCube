# RUBIK's MINI CUBE with PIC18F4520

* https://www.youtube.com/watch?v=kPHCREx986o

## Requirements

* **硬體:**
    * RGB Led *24
    * LCD 面板 *1
    * 5K 可變電阻 *6
    * 按鈕 *3
    * PIC18F4520 *2
    * PICKIT 3 or 4
    * 電阻(for led) * 18
    * 焊接技能
    * 很多焊線
* **軟體:**
    * MPLAB
    * python(for uart)

## LED 接線概念圖

![](https://i.imgur.com/l6meMGP.png)
* 本專案只用到2*2*2的cube
* 紅色與咖啡色為LED上的VDD
* 藍色為LED上的RGB
* 若以2*2*2做計算，共用到8(VDD)+4*3(RGB) = 20 pins 來控制CUBE的顏色，用視覺暫留之方式達到此效果

## 使用方式

將`LCD.X`藉由Mplab燒錄進控制LCD的Pic18，將`cube.X`藉由Mplab燒錄進控制Cube的Pic18。

**接線必須完整**

若想藉由uart進行解魔方，先將`myserial.py` 中的COM Port更改並執行，就會自動讀取Cube之內容並告知使用者解法。

## 遇到的問題
**1. PIC18 PIN腳限制：**

若是每一個RGB led都接4個pin腳，總計需要4*24 = 96個pin腳來完成。但若結合視覺暫留之方式，就可將所需pin腳減至24個，其中架構就需要多加考慮。

**2. LED品質不一：**

LED有時RGB亮度不一造成顏色差異，所以就又要拆起來重新進行焊接，若要確保品質就只能買較貴的LED。

**3. LCD與PIC18互動：**

在別人的專案都一直看到lcd.h的這個標頭檔，但卻一直在mplab中找不到，所以就去網路上參考別人lcd.h的寫法。

**4. 記憶體與PIC運行速度限制：**

由於知道PIC有速度及記憶體上的限制，所以在撰寫c時運用比較省memory的作法，雖然不確定有無差異。
