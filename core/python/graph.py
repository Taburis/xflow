
from graphLite import *

class graph (graphLite_base):

    def __init__(self):
        super(graph, self).__init__()

    def addChain(self, nlist):
        for i in range(0, len(nlist)):
            self.add_node(nlist[i]) 
            if i>0: self.link(i-1, i)
