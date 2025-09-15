import sys
from PyQt5.QtWidgets import (QApplication, QMainWindow, QLabel, 
                             QPushButton, QLineEdit, QVBoxLayout, 
                             QHBoxLayout, QWidget, QMessageBox)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        # 设置窗口标题和大小
        self.setWindowTitle('PyQt5 示例程序')
        self.setGeometry(300, 300, 400, 200)
        
        # 创建中央部件和布局
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout()
        central_widget.setLayout(layout)
        
        # 创建标签
        self.label = QLabel('请输入您的名字:')
        layout.addWidget(self.label)
        
        # 创建输入框
        self.name_input = QLineEdit()
        layout.addWidget(self.name_input)
        
        # 创建按钮
        self.button = QPushButton('打招呼')
        self.button.clicked.connect(self.greet)
        layout.addWidget(self.button)
        
        # 结果显示标签
        self.result_label = QLabel('')
        layout.addWidget(self.result_label)
    
    def greet(self):
        name = self.name_input.text().strip()
        if name:
            self.result_label.setText(f"你好, {name}!")
        else:
            QMessageBox.warning(self, "警告", "请输入您的名字")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())