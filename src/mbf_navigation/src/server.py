import time

from PyQt5.QtWidgets import QApplication, QMessageBox
from PyQt5 import uic
import socket


class Stats:
    def __init__(self):
        self.serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        host = '127.0.0.1'
        port = 8888
        self.serversocket.bind((host, port))
        self.serversocket.listen(5)
        self.clientSocket, self.addr = self.serversocket.accept()
        self.string = ''
        self.ui = uic.loadUi('./ui/map.ui')
        self.ui.setWindowTitle('Server')
        self.ui.APoint.clicked.connect(self.handleAPoint)
        self.ui.BPoint.clicked.connect(self.handleBPoint)
        self.ui.CPoint.clicked.connect(self.handleCPoint)
        self.ui.Send.clicked.connect(self.sendMsg)
        self.ui.Close.clicked.connect(self.closeSocket)
        self.ui.Reconnect.clicked.connect(self.reconnect)
        self.ui.WorkDone.clicked.connect(self.WorkDone)

    def sendMsg(self):
        self.string = self.ui.Path.displayText()
        self.clientSocket.send(self.string.encode())
        # self.clientSocket.close()
        # self.clientSocket, self.addr = self.serversocket.accept()
        self.string = ''

    def closeSocket(self):
        self.clientSocket.send('0'.encode())
        time.sleep(1)
        self.clientSocket.close()

    def handleAPoint(self):
        self.string = self.string + 'A->'
        self.ui.Path.setText(self.string)

    def handleBPoint(self):
        self.string = self.string + 'B->'
        self.ui.Path.setText(self.string)

    def handleCPoint(self):
        self.string = self.string + 'C->'
        self.ui.Path.setText(self.string)

    def WorkDone(self):
        self.clientSocket.send('1'.encode())

    def reconnect(self):
        self.serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        host = '127.0.0.1'
        port = 8886
        self.serversocket.bind((host, port))
        self.serversocket.listen(5)
        self.clientSocket, self.addr = self.serversocket.accept()


if __name__ == '__main__':
    app = QApplication([])
    stats = Stats()
    stats.ui.show()
    app.exec_()
    stats.closeSocket()
