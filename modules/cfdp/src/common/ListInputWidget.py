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

        self.nBoxes = nBoxes

    def boxCount(self):
        return self.nBoxes

    def addBoxes(self, cnt):
        self.nBoxes += cnt
        for i in range(cnt):
            b = Qt.QLineEdit()
            self.boxes.append(b)
            self.layout().addWidget(b)

    def removeBoxes(self, cnt):
        # make sure we don't go negative
        nRemove = cnt
        if cnt > self.nBoxes:
            nRemove = self.nBoxes

        self.nBoxes -= nRemove

        for i in range(nRemove):
            b = self.boxes.pop()
            b.close()
