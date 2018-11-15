
import copy

class nodeLite_base (object):
    """
    a node is an abtract object placeholder in dataflow. 
    """
    def __init__(self):
        node_id = -1

    def check_if_callable(self):
        callabe_op = getatrr(self, "eval_func", None)
        return callabel(callable_op)  

    def run_eval_func(self):
        if(self.check_if_callable) : self.eval_func()

#class sparseMatrix (object):
#    """
#    a sparse matrix ojbect
#    """
#    def __init__(self):
#        holder_ = []

class graphLite_base (object):
    """
    a graph is actually represented by a sparse matrix: called map_ to represent the connection between sets of nodes
    """
    def __init__(self):
        self.id_ = 0 # always be the id of the next node 
        self.map_ = []
        self.mapper_= {}
        self.node_id_list = {}

    def move_id_forward(self):
        #id_ always be the ID for the next node

        if self.id_ in self.node_id_list.values() : 
            self.id_ = self.id_+1
            self.move_id_forward()

    def add_node(self, node, key = ''):
        #default setting is useing the id to be the key
        if key == '': key = self.id_
        if key in self.mapper_:
            print("Error: node key already exists!")
        else:
            self.mapper_[key]  = node
            self.node_id_list[key] = self.id_
            self.add_column({})
            self.move_id_forward()

    def get_node_id(self, key):
        return self.node_id_list[key]

    def remove_node(self, key):
        self.release_node(key)
        self.id_ = self.get_node_id(key)
        self.empty_column(key)
        self.node_id_list.pop(key)
        self.mapper_.pop(key)

    def release_node(self, key):
        for key2 in self.map_[self.get_node_id(key)].keys():
            self.cut_link(key, key2)

    def empty_column(self, key):
        self.map_[self.get_node_id(key)]={}

    def add_column(self, column):
        #if self.id_ <len(self.map_) : self.map_[self.id_] = column
        self.map_.append(column)
        self.move_id_forward()

    def link(self, key1, key2, weight = 1):
        self.map_[self.get_node_id(key1)][key2]= weight 
        self.map_[self.get_node_id(key2)][key1]= -weight

    def cut_link(self, key1, key2): 
        self.map_[self.get_node_id(key1)].pop(key2, None)
        self.map_[self.get_node_id(key2)].pop(key1, None)

    def get_link_weight(self, key1, key2):
        return self.map_[self.get_node_id(key1)][key2]

    def get_head_node(self):
        # assume there's only one head node exists, and return the key
        for ky in self.node_id_list.keys():
            if self.is_head(ky): 
                return ky
        return False #no head node exists, means a loop has found: a-> b -> c -> a

    def is_head(self, ky):
        #isolaated node is a head
        for key in self.map_[self.get_node_id(ky)].keys():
            if self.get_link_weight(ky, key)<0 : 
                return False
        return True

    def is_end(self, ky):
        for key in self.map_[self.get_node_id(ky)].keys():
            if self.get_link_weight(ky,key) >0 : 
                return False
        return True

    def key2node_list(self, klist):
        nlist = []
        for key in klist:
            if key == 'EOP': continue
            nlist.append(self.mapper_[key])
        return nlist
#
    def forward(self):
        ptr = self.get_head_node()
        fchain = []
        map0 = copy.deepcopy(self.map_)
        self.forward_propagate(ptr, fchain)
        self.map_ = map0
        #print(self.map_)
        return fchain

    def forward_propagate(self, ptr, fchain):
        if self.is_head(ptr):
            fchain.append(ptr)
            for key in self.map_[self.get_node_id(ptr)].keys():
                if self.get_link_weight(ptr,key)>0 : 
                    self.cut_link(ptr, key)
                    self.forward_propagate(key, fchain)
        else : 
            # the EOP means the end of the sub-path, which means it reach the end of the sub-path, or reach to a node that has other input path haven't been past. In the jobs, it means that the place need pause to waiting the other path finish so that the node are ready to be evaluated.
            fchain.append('EOP')
            return
