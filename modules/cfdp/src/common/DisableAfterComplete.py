

class DisableAfterComplete:

    def __init__(self, hostFun, action):
        self.hostFun = hostFun
        self.action = action

    def __call__(self):
        self.hostFun()
        self.action.setEnabled(False)
