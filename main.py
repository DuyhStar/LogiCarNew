import sensor, image, time
from pyb import UART, LED

# 如果要保证颜色追踪效果的话， 需要对环境的严格控制. 晚上光源的冷暖色等，都会对颜色追踪造成很大的影响

# 颜色阈值的设定可以在 工具(Tools) -> 机器视觉(Machine Vision) -> 阈值编辑器(Threshold Editor) 中调试
red_threshold   = (49, 78, 22, 65, -34, 18) # 红色阈值
green_threshold = (32, 94, -74, -22, -6, 25) # 绿色阈值
blue_threshold  = (57, 73, -7, 39, -73, -11) # 蓝色阈值

# 颜色代码是find_blobs返回的blob对象中的一个成分， 用于标识，该色块是由在哪个阈值下选择的
red_color_code   = 1 # 红色的颜色代码
green_color_code = 2 # 绿色的颜色代码
blue_color_code  = 4 # 蓝色的颜色代码

uart_receive_char = 0
order = [1, 2, 3]

red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)

sensor.reset()                      # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 选择像素模式 RGB565.
sensor.set_framesize(sensor.QVGA)   # use QQVGA for speed.
sensor.skip_frames(10)              # Let new settings take affect.
sensor.set_auto_whitebal(False)     #关闭白平衡。白平衡是默认开启的，在颜色识别中，需要关闭白平衡。

clock = time.clock() # Tracks FPS.

# 初始化串口，用来和单片机进行通信
uart = UART(3, 9600)
uart.init(9600, bits=8, parity=None, stop=1)

# 比较两个色块大小的函数
def compareBlob(blob1, blob2):
    # 选择pixels作为指标. Other: blob.area()
    tmp = blob1.pixels() - blob2.pixels()
    if tmp == 0:
        return 0;
    elif tmp > 0:
        return 1;
    else:
        return -1;

# 标记色块位置
def tab_blob(img, blob):
    x          = blob[0]
    y          = blob[1]
    width      = blob[2]
    height     = blob[3]
    center_x   = blob[5]
    center_y   = blob[6]

    img.draw_rectangle([x, y, width, height]) #用矩形标记
    img.draw_cross(center_x, center_y)        #在中心画十字形标记

def judge_order(order):
    s = [0,0,0,0,0,0]
    s[0] = order == [1,2,3]
    s[1] = order == [1,3,2]
    s[2] = order == [2,1,3]
    s[3] = order == [2,3,1]
    s[4] = order == [3,2,1]
    s[5] = order == [3,1,2]

    if s[0] or  s[1] or s[2] or s[3] or s[4] or s[5]:
        return 1
    else:
        return 0

# 红绿蓝三种颜色识别,找出最大的
def color_detect():
    red_led.off()
    while(True):
        blue_led.off()
        green_led.off()
        img = sensor.snapshot() # 拍照，返回图像

        # 颜色阈值约束(color_threshold,数组格式),像素阈值pixel_threshold,色块面积大小阈值(area_threshold)
        blobs = img.find_blobs([red_threshold, green_threshold, blue_threshold], area_threshold=1000)

        #如果找到了目标颜色
        if blobs:
            red   = []
            green = []
            blue  = []

            #迭代找到的目标颜色区域,并分别提取出红绿蓝
            for blob in blobs:
                color_code = blob[8]
                if color_code == red_color_code:
                    red.append(blob)
                elif color_code == green_color_code:
                    green.append(blob)
                elif color_code == blue_color_code:
                    blue.append(blob)
                else:
                    pass

            max_red_blob   = blobs[0]
            max_green_blob = blobs[0]
            max_blue_blob  = blobs[0]
            # 找出最大的红色色块
            if red:
                max_red_blob = red[0]
                for red_blob in red:
                    if compareBlob(max_red_blob, red_blob) == -1:
                        max_red_blob = red_blob
            # 找出最大的绿色色块
            if green:
                max_green_blob = green[0]
                for green_blob in green:
                    if compareBlob(max_green_blob, green_blob) == -1:
                        max_green_blob = green_blob
            # 找出最大的蓝色色块
            if blue:
                max_blue_blob = blue[0]
                for blue_blob in blue:
                    if compareBlob(max_blue_blob, blue_blob) == -1:
                        max_blue_blob = blue_blob

            # 如果找到了红绿蓝三种颜色
            if max_red_blob and max_green_blob and max_blue_blob:
                blob_rgb = [max_red_blob, max_green_blob, max_blue_blob]

                # 按照 x 坐标值大小进行排序
                if blob_rgb[0][0] > blob_rgb[1][0]:
                    temp        = blob_rgb[0]
                    blob_rgb[0] = blob_rgb[1]
                    blob_rgb[1] = temp
                if blob_rgb[0][0] > blob_rgb[2][0]:
                    temp        = blob_rgb[0]
                    blob_rgb[0] = blob_rgb[2]
                    blob_rgb[2] = temp
                if blob_rgb[1][0] > blob_rgb[2][0]:
                    temp        = blob_rgb[1]
                    blob_rgb[1] = blob_rgb[2]
                    blob_rgb[2] = temp
                # 将物块摆放顺序转换为数字
                for i in [0,1,2]:
                    if blob_rgb[i][8] == red_color_code:
                        order[i] = 1
                    elif blob_rgb[i][8] == green_color_code:
                        order[i] = 2
                    elif blob_rgb[i][8] == blue_color_code:
                        order[i] = 3
                    else:
                        pass
                if judge_order(order):
                    green_led.on()
                    blue_led.on()
                    uart.writechar(order[0])
                    uart.writechar(order[1])
                    uart.writechar(order[2])
                    print(order)
                # 标记色块
                tab_blob(img, max_red_blob)
                tab_blob(img, max_green_blob)
                tab_blob(img, max_blue_blob)


while(True):
    red_led.on()
    color_detect()
