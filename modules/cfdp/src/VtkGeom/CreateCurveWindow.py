from PyQt5 import Qt

from .ControlPointsWidget import ControlPointsWidget

from ..geometry.NurbsUtils import calculateKnotCount


class CreateCurveWindow(Qt.QDialog):

    def __init__(self, parent):
        super().__init__(parent=parent)
        self.curveTypes = ["Bezier", "NURBS"]
        self.numPts = 3
        self.setupUi()
        self.show()

    def _adjustAllSizes(self):
        self.curveInfoBox.adjustSize()
        self.curveData.adjustSize()
        self.adjustSize()

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
        isNurb = i == 1
        self.curveData.changeNurbStatus(isNurb)

        if i == 0:
            self.curveInfoBox.layout().removeWidget(self.polyLabel)
            self.curveInfoBox.layout().removeWidget(self.polyOrderBox)
            self.polyOrderBox.close()
            self.polyLabel.close()
        elif i == 1:
            self.curveInfoBox.layout().addWidget(self.polyLabel)
            self.curveInfoBox.layout().addWidget(self.polyOrderBox)
            self.polyOrderBox.show()
            self.polyLabel.show()

        self.curveData.show()
        self.curveInfoBox.show()
        self._adjustAllSizes()

    def _curvesComboBox(self):
        b = Qt.QComboBox()
        for i in self.curveTypes:
            b.addItem(i)

        b.currentIndexChanged.connect(self._curveTypeChanged)
        self._curveInfo = b
        return b

    def _polyOrderChanged(self, newP):
        # ignore empty boxes
        if len(newP) == 0:
            return

        p = int(newP)

        # make sure it's always greater than 0
        p = max(0, p)
        self.curveData.newPolyOrder(p)
        self._adjustAllSizes()

    def _curveTypeBox(self):
        box = Qt.QGroupBox(title="Curve Info")
        self.curveInfoBox = box
        lo = Qt.QHBoxLayout()
        lab = Qt.QLabel("Curve Type", self)
        lo.addWidget(lab)
        self.curveTypesSelector = self._curvesComboBox()
        lo.addWidget(self.curveTypesSelector)

        self.polyLabel = Qt.QLabel("Polynomial Order:")
        self.polyOrderBox = Qt.QLineEdit("3")
        orderVal = Qt.QIntValidator()
        orderVal.setBottom(0)
        self.polyOrderBox.setValidator(orderVal)
        self.polyOrderBox.textChanged.connect(self._polyOrderChanged)

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
