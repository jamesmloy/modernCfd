from PyQt5 import Qt


class CreateCurveWindow(Qt.QDialog):

    def __init__(self, parent):
        super().__init__(parent=parent)
        self.curveTypes = ["Bezier", "NURBS"]
        self.numPts = 3
        self.setupUi()
        self.show()

    def _curvesComboBox(self):
        b = Qt.QComboBox()

        for i in self.curveTypes:
            b.addItem(i)

        return b

    def _curveTypeBox(self):
        box = Qt.QGroupBox()
        lo = Qt.QHBoxLayout()
        lab = Qt.QLabel("Curve Type", self)
        lo.addWidget(lab)
        self.curveTypesSelector = self._curvesComboBox()
        lo.addWidget(self.curveTypesSelector)
        box.setLayout(lo)
        return box

    def _controlPointBox(self):
        box = Qt.QGroupBox()
        lo = Qt.QHBoxLayout()
        return box

    def setupUi(self):

        # main layout holding all the
        # group boxes
        mainLayout = Qt.QVBoxLayout()
        mainLayout.addWidget(self._curveTypeBox())
        mainLayout.addWidget(self._controlPointBox())

        self.setLayout(mainLayout)
