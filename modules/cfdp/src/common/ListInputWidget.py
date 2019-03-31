from PyQt5 import Qt


class ListInputWidget(Qt.QGroupBox):

    def __init__(self, parent, nBoxes, title=None):
        if title is None:
            super().__init__(parent=parent)
        else:
            super().__init__(title=title, parent=parent)

        lo = Qt.QVBoxLayout()

        self.boxes = []
        for i in range(nBoxes):
            box = Qt.QLineEdit()
            self.boxes.append(box)
            lo.addWidget(box)

        self.setLayout(lo)

    def addBoxes(self, cnt):
        for i in range(cnt):
            b = Qt.QLineEdit()
            self.boxes.append(b)
            self.layout().addWidget(b)

    def removeBoxes(self, cnt):
        for i in range(cnt):
            b = self.boxes.pop()
            b.close()
