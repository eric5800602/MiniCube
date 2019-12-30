
import serial
from serial import Serial
from time import sleep
import time
import sys
import py222
import solver
import numpy as np
 
COM_PORT = 'COM4'  # 請自行修改序列埠名稱
BAUD_RATES = 9615
ser = serial.Serial(COM_PORT, BAUD_RATES,bytesize=8, timeout=2)
try:
    # 接收用戶的輸入值並轉成小寫
    while True:
        choice = input('輸入"help"給予解魔方提示 輸入"e"退出本程式\n').lower()
        #5 白 4 綠 3 青 2 澄 1 藍 0 紅
        if choice == 'help':
            print('傳送解析指令')
            ser.write('os'.encode())
            while 1:
                if(ser.in_waiting):
                    mcu_feedback = ser.readline().decode()  # 接收回應訊息並解碼
                    s = mcu_feedback.split(' ')
                    s.remove('')
                    print(s)
                    arr = np.array([s[18],s[17],s[19],s[16],s[13],s[12],s[14],s[15],s[1],s[0],s[2],s[3],s[20],s[23],s[21],s[22],s[5],s[4],s[6],s[7],s[9],s[8],s[10],s[11]])
                    arr = arr.astype(int)
                    solver.solveCube(arr)
                    break
        elif choice == 'e':
            ser.close()
            print('再見！')
            sys.exit()
        else:
            print('指令錯誤…')

            
except KeyboardInterrupt:
    ser.close()
    print('再見！')