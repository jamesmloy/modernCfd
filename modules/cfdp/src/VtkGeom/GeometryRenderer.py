import vtk
from PyQt5 import Qt

from vtk.qt.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor

from ..common.ParentedCallback import ParentedCallback
from .CreateCurveWindow import CreateCurveWindow


class MyInteractor(vtk.vtkInteractorStyleTrackballCamera):

    def OnMouseWheelForward(self):
        super().OnMouseWheelBackward()

    def OnMouseWheelBackward(self):
        super().OnMouseWheelForward()


def makeCreateCurveTools(w):
    cctw = CreateCurveWindow(parent=w)
    cctw.show()


def makeGeomRenderFrame(w):

    tb = w.addToolBar("Geometry Palette")
    curveCreateAction = Qt.QAction("Create Curve", tb)
    tb.addAction(curveCreateAction)

    curveCreateAction.triggered \
        .connect(ParentedCallback(w, makeCreateCurveTools))

    frame = Qt.QFrame()
    vl = Qt.QVBoxLayout()
    vtkWidget = QVTKRenderWindowInteractor(frame)
    vl.addWidget(vtkWidget)

    ren = vtk.vtkRenderer()
    vtkWidget.GetRenderWindow().AddRenderer(ren)

    colors = vtk.vtkNamedColors()

    ren.SetBackground(colors.GetColor3d("White"))

    iren = vtkWidget.GetRenderWindow().GetInteractor()
    iren.SetInteractorStyle(MyInteractor())

    axes = vtk.vtkAxesActor()
    ren.AddActor(axes)
    ren.ResetCamera()

    frame.setLayout(vl)

    iren.Initialize()
    return frame
