from PyQt5 import Qt

from ..common.ListInputWidget import ListInputWidget

from ..geometry.NurbsUtils import calculateKnotCount


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


class ControlPointsWidget(Qt.QWidget):

    class ControlPointBox(MultipleListInput):
        def __init__(self, parent, isNurb, p, npts):

            titles = ["Points", "Weights"]
            boxCounts = [npts, npts]

            if isNurb:
                titles.append("Knots")
                boxCounts.append(calculateKnotCount(npts, p))

            super().__init__(parent, boxCounts, titles)

    def __init__(self, parent, isNurb, p, npts):
        super().__init__(parent=parent)

        lo = Qt.QVBoxLayout()
        self.setLayout(lo)

        self.ptsInput = ControlPointsWidget.ControlPointBox(self,
                                                            isNurb,
                                                            p, npts)
        lo.addWidget(self.ptsInput)

        addPtButton = Qt.QPushButton(text="Add Point", parent=self)
        addPtButton.clicked.connect(self.ptsInput.addBox)
        lo.addWidget(addPtButton)

        delPtButton = Qt.QPushButton(text="Remove Point", parent=self)
        delPtButton.clicked.connect(self.ptsInput.removeBox)
        lo.addWidget(delPtButton)

    def addKnots(self, cnt):
        self.ptsInput.addList(cnt, "Knots")

    def removeKnots(self):
        self.ptsInput.removeLast()


class CreateCurveWindow(Qt.QDialog):

    def __init__(self, parent):
        super().__init__(parent=parent)
        self.curveTypes = ["Bezier", "NURBS"]
        self.numPts = 3
        self.setupUi()
        self.show()

    def getCurveTypeIndex(self):
        return self._curveInfo.currentIndex()

    def getPolyOrder(self):
        ct = self.getCurveTypeIndex()

        if ct == 0:
            return self.numPts
        else:
            return int(self.polyOrderBox.text())

    def calculateKnotCount(self):
        ct = self.getCurveTypeIndex()

        if ct == 0:
            raise RuntimeError("There are no knots in Bezier curves")
        else:
            p = self.getPolyOrder()
            return calculateKnotCount(self.numPts, p)

    def _curveTypeChanged(self, i):
        if i == 0:
            self.curveData.removeKnots()
            self.curveInfoBox.layout().removeWidget(self.polyLabel)
            self.curveInfoBox.layout().removeWidget(self.polyOrderBox)
            self.polyOrderBox.close()
            self.polyLabel.close()
        elif i == 1:
            self.curveData.addKnots(self.calculateKnotCount())
            self.curveInfoBox.layout().addWidget(self.polyLabel)
            self.curveInfoBox.layout().addWidget(self.polyOrderBox)
            self.polyOrderBox.show()
            self.polyLabel.show()

        self.curveData.show()
        self.curveInfoBox.show()

    def _curvesComboBox(self):
        b = Qt.QComboBox()
        for i in self.curveTypes:
            b.addItem(i)

        b.currentIndexChanged.connect(self._curveTypeChanged)
        self._curveInfo = b
        return b

    def _curveTypeBox(self):
        box = Qt.QGroupBox(title="Curve Info")
        self.curveInfoBox = box
        lo = Qt.QHBoxLayout()
        lab = Qt.QLabel("Curve Type", self)
        lo.addWidget(lab)
        self.curveTypesSelector = self._curvesComboBox()
        lo.addWidget(self.curveTypesSelector)

        # m = n + p + 1
        # m + 1 knots, n + 1 points, p degree

        self.polyLabel = Qt.QLabel("Polynomial Order:")
        self.polyOrderBox = Qt.QLineEdit("3")
        orderVal = Qt.QIntValidator()
        orderVal.setBottom(0)
        self.polyOrderBox.setValidator(orderVal)

        if self.getCurveTypeIndex() == 1:
            lo.addWidget(self.polyLabel)
            lo.addWidget(self.polyOrderBox)

        box.setLayout(lo)
        return box

    def _controlPointBox(self):
        isNurb = self.getCurveTypeIndex() == 1
        npts = self.numPts
        p = self.getPolyOrder()

        box = ControlPointsWidget(self, isNurb, p, npts)
        self.curveData = box
        return box

    def setupUi(self):

        # main layout holding all the
        # group boxes
        mainLayout = Qt.QVBoxLayout()
        mainLayout.addWidget(self._curveTypeBox())
        mainLayout.addWidget(self._controlPointBox())

        self.setLayout(mainLayout)
