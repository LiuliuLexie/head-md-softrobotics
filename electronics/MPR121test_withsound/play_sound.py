import serial
from playsound import playsound

# 替换成你的 Arduino 串口号，例如 "COM3"（Windows）或 "/dev/ttyUSB0"（Mac/Linux）
serial_port = "/dev/tty.usbserial-A5069RR4"  # 根据你的设备调整 # search in terminal ls /dev/tty.*
baud_rate = 9600  # 波特率 

# 定义引脚和声音文件的映射
pin_to_sound = {
    0: "sound0.mp3",
    1: "do.mp3",
    2: "re.mp3",
    3: "mi.mp3",
    4: "fa.mp3",
    5: "sound5.mp3",
    6: "sound6.mp3",
    7: "sound7.mp3",
    8: "sound8.mp3",
    9: "sound9.mp3",
    10: "sound10.mp3",
    11: "scream.mp3",
}

# 初始化串口连接
try:
    ser = serial.Serial(serial_port, baud_rate)
    print(f"connected to {serial_port}")
except Exception as e:
    print(f"can't connect to {serial_port}：{e}")
    exit()

try:
    while True:
        if ser.in_waiting > 0:  # 检查是否有数据
            line = ser.readline().decode("utf-8").strip()  # 读取数据
            print(f"receive: {line}")

            # 处理触摸事件
            if line.startswith("TOUCH"):
                pin = int(line.split(" ")[1])  # 获取触摸的引脚号
                if pin in pin_to_sound:
                    sound_file = pin_to_sound[pin]
                    print(f"play: {sound_file}")
                    playsound(sound_file)  # 播放声音
except KeyboardInterrupt:
    print("程序已停止")
finally:
    ser.close()
