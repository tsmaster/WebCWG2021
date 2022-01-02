from btutil import *

assignedIDs = []
        
def makeUniqueID(base):
    base = base.lower()
    base = base.replace(' ', '_')
    base = base.replace('(', '')
    base = base.replace(')', '')
    
    if not (base in assignedIDs):
        assignedIDs.append(base)
        return base
    i = 1
    while True:
        test = "{0}_{1:04d}".format(base,i)
        if not (test in assignedIDs):
            assignedIDs.append(test)
            return test
        else:
            i += 1

def reset():
    assignedIDs.clear()
            


class Node:
    def __init__(self, tag, attribs):
        self.tag = tag
        self.attribs = attribs
        if "name" in attribs:
            self.nameStr = "{0} ({1})".format(tag, attribs['name'])
        else:
            self.nameStr = tag

        self.idStr = makeUniqueID(self.nameStr)
        self.children = []

    def __str__(self):
        return self.nameStr

    def addToGraph(self, g):
        g.node(self.idStr)

    def addChildLinksToGraph(self, g):
        for c in self.children:
            g.edge(self.idStr, c.idStr)

    def getCppClassName(self):
        return "Node"

    def getCppNodeName(self):
        cppName = self.idStr
        #hash(self.idStr))
        return "node_{0}".format(self.idStr)

unknownTags = set()

def makeNode(tag, attribs, depth):
    printAtDepth(depth, "making node with tag {0} attribs {1}".format(tag, attribs))

    if (tag == "selector"):
        n = Selector(tag, attribs)
    elif (tag == "sequence"):
        n = Sequence(tag, attribs)
    elif (tag == "inverter"):
        n = Inverter(tag, attribs)
    elif (tag == "sensor_have_barrel"):
        n = HaveBarrelSensor(tag, attribs)

    elif (tag == "a_star_to_barrels"):
        n = AStarNode(tag, attribs, 'barrels')
    elif (tag == "a_star_to_goal"):
        n = AStarNode(tag, attribs, 'goals')
    elif (tag == "a_star_to_patrol_points"):
        n = AStarNode(tag, attribs, 'patrol')
    elif (tag == "follow_a_star"):
        n = FollowAStarPathNode(tag, attribs)
    elif (tag == "nav_to_barrel"):
        n = NavNode(tag, attribs, 'barrel')
    elif (tag == "nav_to_goal"):
        n = NavNode(tag, attribs, 'goal')
    elif (tag == "sort_los_to_barrels"):
        n = SortLosNode(tag, attribs, 'barrels')
    elif (tag == "sort_los_to_goals"):
        n = SortLosNode(tag, attribs, 'goals')
    else:
        unknownTags.add(tag)
        n = Node(tag, attribs)
    printAtDepth(depth, "made node", n)
    return n



class Selector(Node):
    def __str__(self):
        return "SEL " + self.nameStr

    def getCppClassName(self):
        return "SelectorNode"
    
class Sequence(Node):
    def __str__(self):
        return "SEQ " + self.nameStr

    def getCppClassName(self):
        return "SequenceNode"

class Inverter(Node):
    def __str__(self):
        return "INV " + self.nameStr

    def getCppClassName(self):
        return "InverterNode"

class Sensor(Node):
    pass
    
class HaveBarrelSensor(Sensor):
    def getCppClassName(self):
        return "BarrelSensorNode"

class AStarNode(Node):
    def __init__(self, tag, attribs, dest):
        super().__init__(tag, attribs)
        self.dest = dest
        
    def getCppClassName(self):
        return "AStarNode"


class FollowAStarPathNode(Node):
    def getCppClassName(self):
        return "FollowAStarPathNode"

class NavNode(Node):
    def __init__(self, tag, attribs, dest):
        super().__init__(tag, attribs)
        self.dest = dest

    def getCppClassName(self):
        return "NavNode"

        
class SortLosNode(Node):
    def __init__(self, tag, attribs, dest):
        super().__init__(tag, attribs)
        self.dest = dest

    def getCppClassName(self):
        return "SortLosNode"


