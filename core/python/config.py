
import sys

#a light version of cmssw for doing analysis workflow

_env_path = '/Users/tabris/programs/xflow/core/'

class nodeBase(object):
    """ base for all the node
        name is convention for user to read and may not be unique
        node_type is the name of cpp object the node corresponding to.
        e.g: if b = a.clone() then the name for a, b may not the same but the node_type has to be the same
    """
    node_type = ''
    name = ''
    def __init__(self, name_):
        name=name_
        self.src =''
    
    def name_(self): return self.name

    def _type(self):
        return self.node_type
    def set_type(self, type_): 
        self.node_type=type_

    def _src(self): return self.src

class nodeChain(list):
    """
    the class to chain the nodes to a sequence 
    """
    def __init__(self, *arg, **args):
        super(nodeChain, self).__init__(arg)

    def append(self, x):
        super(nodeChain, self).append(x)

    def get_node_type_list(self):
        typeChain = []
        for i in self:
            if i._type() not in typeChain: 
                typeChain.append(i._type())
        return typeChain


    def get_run_order_node_list(self):
    # this function return the list only for user reading
        orderChain = list()
        for i in self: orderChain.append(i.name)
        return orderChain


class rootFileIO(nodeBase):
    def __init__(self, name):
        super(rootFileIO, self).__init__(name)
        super(rootFileIO, self).set_type('rootFileIO')
        #just put the path to the folder contain the obj.h
        self.src = _env_path+"src/"
    def _placeImpl(self, proc):
        proc._placeFileIO(self)


class config(object):
    """
    config object to specify the workflow
    """
    def __init__(self, name_):
        self.name = name_
        self.sequence = None

    def load(self, moduleName):
        moduleName = moduleName.replace("/",".")
        module = __import__(moduleName)

    def _place(self, mod, ptype):
        ptype[mod.name] = mod

    def schedule_ (self):return self.__schedule

    def name_(self):return self.name


class rootEDMConfig(config):
    def __init__(self, name):
        super(rootEDMConfig, self).__init__(name)
        # one placeAttr function should be added for each process attribute added here
        # each process attribut corresponds to a cpp objectBase will be used 
        self.__fileIO = {}
        self.__filter = {}
        self.__analyer= {}

    def _placeFileIO(self, mod):
        self._place(mod, self.__fileIO)



