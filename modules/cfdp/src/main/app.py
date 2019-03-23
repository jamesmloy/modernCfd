import sys

from PyQt5 import Qt

from .ModernCfdMainWindow import ModernCfdMainWindow


def main():
    app = Qt.QApplication([])
    app.setApplicationName("Modern CFD")
    window = ModernCfdMainWindow(app=app)
    window.show()
    sys.exit(app.exec_())
