from PyQt5 import Qt

from .ListInputWidget import ListInputWidget


class MultipleListInput(Qt.QWidget):

    def __init__(self, parent, boxCounts, titles):
        super().__init__(parent=parent)

        lo = Qt.QHBoxLayout()
        self.setLayout(lo)

        self.lo = lo

        self.listInputs = []

        for b, t in zip(boxCounts, titles):
            liw = ListInputWidget(self, b, t)
            self.listInputs.append(liw)
            lo.addWidget(liw)

    def removeLast(self):
        lastI = self.listInputs.pop()
        lastI.close()

    def addList(self, cnt, title):
        liw = ListInputWidget(self, cnt, title)
        self.listInputs.append(liw)
        self.lo.addWidget(liw)

    def addBox(self):
        for inp in self.listInputs:
            inp.addBoxes(1)

    def removeBox(self):
        for inp in self.listInputs:
            inp.removeBoxes(1)
