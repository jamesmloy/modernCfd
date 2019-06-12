from PyQt5 import Qt

from ..common.DisableAfterComplete import DisableAfterComplete


class ModernCfdMainWindow(Qt.QMainWindow):

    defaultW = 0.75
    defaultH = 0.75

    myTitle = "Modern CFD"

    def __init__(self, app, parent=None):
        Qt.QMainWindow.__init__(self, parent)

        self.app = app

        self.setWindowTitle(self.myTitle)

        ssize = app.primaryScreen().size()
        self.setDefaultSize(ssize)

        self.menus = self.setMenus()

    def setDefaultSize(self, ssize):
        w = ssize.width() * self.defaultW
        h = ssize.height() * self.defaultH
        self.setMinimumSize(Qt.QSize(w, h))

    def addGeomRenderer(self):
        from ..VtkGeom.GeometryRenderer import makeGeomRenderFrame
        f = makeGeomRenderFrame(self)

        self.setCentralWidget(f)

    def setMenus(self):
        menus = {}
        menus['File'] = self.menuBar().addMenu('File')

        geomRendererWindowAction = Qt.QAction('Start Geometry Window', self)
        geomRendererWindowAction.triggered \
            .connect(DisableAfterComplete(self.addGeomRenderer,
                                          geomRendererWindowAction))

        quitAction = Qt.QAction('Quit', self)
        quitAction.triggered.connect(self.app.quit)

        menus['File'].addAction(geomRendererWindowAction)
        menus['File'].addAction(quitAction)

        return menus
