#!/usr/bin/env python3

import sys
import vtk
from PyQt5 import QtCore, QtGui
from PyQt5 import Qt

from vtk.qt.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor


def makePoints():
    x = [[0, 0, 0], [1, 0, 0], [2, 0, 0], [0, 1, 0], [1, 1, 0], [2, 1, 0],
         [0, 0, 1], [1, 0, 1], [2, 0, 1], [0, 1, 1], [1, 1, 1], [2, 1, 1],
         [0, 1, 2], [1, 1, 2], [2, 1, 2], [0, 1, 3], [1, 1, 3], [2, 1, 3],
         [0, 1, 4], [1, 1, 4], [2, 1, 4], [0, 1, 5], [1, 1, 5], [2, 1, 5],
         [0, 1, 6], [1, 1, 6], [2, 1, 6]]

    # Here we have kept consistency with the Cxx example of the same name.
    # This means we will use slicing in ugrid.InsertNextCell to ensure
    # that the correct number of points are used.
    pts = [[0, 1, 4, 3, 6, 7, 10, 9], [1, 2, 5, 4, 7, 8, 11, 10],
           [6, 10, 9, 12, 0, 0, 0, 0], [8, 11, 10, 14, 0, 0, 0, 0],
           [16, 17, 14, 13, 12, 15, 0, 0], [18, 15, 19, 16, 20, 17, 0, 0],
           [22, 23, 20, 19, 0, 0, 0, 0], [21, 22, 18, 0, 0, 0, 0, 0],
           [22, 19, 18, 0, 0, 0, 0, 0], [23, 26, 0, 0, 0, 0, 0, 0],
           [21, 24, 0, 0, 0, 0, 0, 0], [25, 0, 0, 0, 0, 0, 0, 0]]

    points = vtk.vtkPoints()
    for i in range(0, len(x)):
        points.InsertPoint(i, x[i])

    return pts, points


def makeUgrid():

    pts, points = makePoints()

    ugrid = vtk.vtkUnstructuredGrid()
    ugrid.Allocate(100)
    ugrid.InsertNextCell(vtk.VTK_HEXAHEDRON, 8, pts[0])
    ugrid.InsertNextCell(vtk.VTK_HEXAHEDRON, 8, pts[1])
    ugrid.InsertNextCell(vtk.VTK_TETRA, 4, pts[2][:4])
    ugrid.InsertNextCell(vtk.VTK_TETRA, 4, pts[3][:4])
    ugrid.InsertNextCell(vtk.VTK_POLYGON, 6, pts[4][:6])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE_STRIP, 6, pts[5][:6])
    ugrid.InsertNextCell(vtk.VTK_QUAD, 4, pts[6][:4])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE, 3, pts[7][:3])
    ugrid.InsertNextCell(vtk.VTK_TRIANGLE, 3, pts[8][:3])
    ugrid.InsertNextCell(vtk.VTK_LINE, 2, pts[9][:2])
    ugrid.InsertNextCell(vtk.VTK_LINE, 2, pts[10][:2])
    ugrid.InsertNextCell(vtk.VTK_VERTEX, 1, pts[11][:1])

    ugrid.SetPoints(points)

    return ugrid


class MainWindow(Qt.QMainWindow):

    def __init__(self, parent=None):
        Qt.QMainWindow.__init__(self, parent)

        self.frame = Qt.QFrame()
        self.vl = Qt.QVBoxLayout()
        self.vtkWidget = QVTKRenderWindowInteractor(self.frame)
        self.vl.addWidget(self.vtkWidget)

        self.ren = vtk.vtkRenderer()
        self.vtkWidget.GetRenderWindow().AddRenderer(self.ren)
        self.iren = self.vtkWidget.GetRenderWindow().GetInteractor()

        ugrid = makeUgrid()

        # Create source
        source = vtk.vtkSphereSource()
        source.SetCenter(0, 0, 0)
        source.SetRadius(5.0)

        # Create a mapper
        mapper = vtk.vtkDataSetMapper()
        mapper.SetInputData(ugrid)

        # Create an actor
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        actor.GetProperty().EdgeVisibilityOn()

        self.ren.AddActor(actor)

        self.ren.ResetCamera()

        self.frame.setLayout(self.vl)
        self.setCentralWidget(self.frame)

        self.show()
        self.iren.Initialize()
        self.iren.Start()


if __name__ == "__main__":
    app = Qt.QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
