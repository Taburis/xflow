

from graph import *

class flowServer(nodeLite_base, node_maker) :
    '''
    the node used to accept the graphs and run the forward path
    '''
    def __init__(self, name):
        self.name_ = name
        self.graph_ = None
    def schedule(self, graph):
        self.graph_ = graph
        keylist = self.graph_.forward()
        self.path_ = self.graph_.key2node_list(keylist)

    def eval_func(self):
        print (self.path_)
        for node in self.path_:
            node.run_eval_func()

class node_test (nodeLite_base):
    def __init__(self, name):
        self.name_ = name
    def eval_func(self):
        print (self.name_)


