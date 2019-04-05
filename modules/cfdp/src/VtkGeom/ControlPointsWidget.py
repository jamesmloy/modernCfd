from PyQt5 import Qt

from ..geometry.NurbsUtils import calculateKnotCount

from ..common.MultipleListInput import MultipleListInput


class ControlPointsWidget(Qt.QWidget):

    class ControlPointBox(MultipleListInput):

        ptsLabel = "Points"
        wtsLabel = "Weights"
        kntsLabel = "Knots"

        def __init__(self, parent, isNurb, p, npts):
            titles = [self.ptsLabel, self.wtsLabel]
            boxCounts = [npts, npts]

            if isNurb:
                titles.append(self.kntsLabel)
                boxCounts.append(calculateKnotCount(npts, p))

            super().__init__(parent, boxCounts, titles)

        def updateKnotCount(self, cnt):
            nLists = len(self.listInputs)

            if nLists == 2:
                self.addList(cnt, self.kntsLabel)
            else:
                cur = self.listInputs[2].boxCount()

                delta = cnt - cur

                if delta > 0:
                    self.listInputs[2].addBoxes(delta)
                else:
                    self.listInputs[2].removeBoxes(-delta)

    def __init__(self, parent, isNurb, p, npts):
        super().__init__(parent=parent)

        self.isNurb = isNurb
        self.p = p
        self.npts = npts

        self.knotCnt = 0
        if isNurb:
            self.knotCnt = calculateKnotCount(npts, p)

        lo = Qt.QVBoxLayout()
        self.setLayout(lo)

        self.ptsInput = ControlPointsWidget.ControlPointBox(self,
                                                            isNurb,
                                                            p, npts)
        lo.addWidget(self.ptsInput)

        addPtButton = Qt.QPushButton(text="Add Point", parent=self)
        addPtButton.clicked.connect(self._addControlPoint)
        lo.addWidget(addPtButton)

        delPtButton = Qt.QPushButton(text="Remove Point", parent=self)
        delPtButton.clicked.connect(self._removeControlPoint)
        lo.addWidget(delPtButton)

    def addKnots(self, cnt):
        self.ptsInput.addList(cnt, "Knots")

    def removeKnots(self):
        self.ptsInput.removeLast()

    def changeNurbStatus(self, isNurb):
        # just ignore if we're already a nurb
        if isNurb == self.isNurb:
            return

        self.isNurb = isNurb
        if isNurb:
            self.addKnots(calculateKnotCount(self.npts, self.p))
        else:
            self.removeKnots()

    def newPolyOrder(self, newP):
        if newP < 0:
            raise RuntimeError("Cannot have negative polynomial order")

        # just ignore if we're not a NURB
        if not self.isNurb:
            return

        # just ignore if the order hasn't changed
        if newP == self.p:
            return

        self.p = newP
        self.knotCnt = calculateKnotCount(self.npts, self.p)
        self.ptsInput.updateKnotCount(self.knotCnt)

    def _addControlPoint(self):
        self.npts += 1
        if self.isNurb:
            self.knotCnt += 1
        self.ptsInput.addBox()

    def _removeControlPoint(self):
        if self.npts < 3:
            return

        self.npts -= 1
        if self.isNurb:
            self.knotCnt -= 1
        self.ptsInput.removeBox()
