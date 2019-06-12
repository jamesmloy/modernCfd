

class ParentedCallback:

    def __init__(self, p, f):
        self.p = p
        self.f = f

    def __call__(self):
        self.f(self.p)
