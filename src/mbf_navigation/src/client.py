#!/usr/bin/python3

# 导入 socket、sys 模块
import socket
import sys
import time


def handleData(data):
    data = data.split('->')
    for i in data:
        print(i)


def WorkDone():
    pass


if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 获取本地主机名
    host = '127.0.0.1'

    # 设置端口号
    port = 8888
    s.connect((host, port))
    # 连接服务，指定主机和端口
    while True:
        # 等待接收服务端的消息
        received = s.recv(1024).decode()
        if received == '0':
            break
        if received == '1':
            WorkDone()
        # 打印读取的信息
        elif received != '':
            handleData(received)
    s.close()

    # 接收小于 1024 字节的数据
