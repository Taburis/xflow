
import errno
import os

_runfactory_path ='/Users/tabris/programs/xflow/core/run/' 

class cppProducer(object):
    """ cosuming the nodeChain to produce the main function for executable"""

    def __init__(self, name, cfg):
        self.config = cfg
        self.chain = cfg.sequence
        try: os.remove(_runfactory_path+name+".C")
        except OSError: pass
        self.cppfile = open(_runfactory_path+name+".C", "w")
        self.interfaceList = []
        self.funcCallList = []
        self.nodeTypeList = []

    def get_interface_list(self, seq):
        for mod in seq:
            if mod._type() not in self.nodeTypeList:
                self.nodeTypeList.append(mod._type())
                self.interfaceList.append(mod._src()+mod._type()+".h")
        return self.interfaceList
        
    def addInterface(self):
        self.get_interface_list(self.chain)
        for src_ in self.interfaceList:
            if not os.path.isfile(src_):
                raise IOError(errno.ENOENT, 'Not found c++ object file: ', src_)
            #raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), src_)
            self.cppfile.write("#include \""+src_+"\"\n")

    def placeMain(self):
        self.cppfile.write("\n int main(){\n")

