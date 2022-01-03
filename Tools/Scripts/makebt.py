import xml.etree.ElementTree as ET

# etree examples at https://docs.python.org/3/library/xml.etree.elementtree.html

import graphviz

# graphviz examples at https://graphviz.readthedocs.io/en/stable/examples.html


from btutil import *
import nodes


def dumpTreeToCtor(tree, outfile, isRoot=False):
    if (isRoot):
        outfile.write("  m_root = std::unique_ptr<{0}>(new {0});\n".format(tree.getCppClassName()))
        nodeCppName = "m_root"
    else:
        nodeCppName = tree.getCppNodeName()
        argString = tree.getArgumentString()
        if argString is None:
            outfile.write("  auto {1} = std::unique_ptr<{0}>(new {0});\n".format(
                tree.getCppClassName(),
                nodeCppName))
        else:
            outfile.write("  auto {1} = std::unique_ptr<{0}>(new {0}({2}));\n".format(
                tree.getCppClassName(),
                nodeCppName,
                argString))
            
    for c in tree.children:
        cName = dumpTreeToCtor(c, outfile, False)
        outfile.write("  {0}->add(std::move({1}));\n".format(nodeCppName, cName))
    return nodeCppName

def writeBTtoCpp(tree, outfile, classname, headername):
    outfile.write("// Behavior Tree Implementation\n\n")

    outfile.write("\n#include <memory>\n\n")
    
    outfile.write('#include "bt_node.h"\n')
    outfile.write('#include "btutil.h"\n')
    outfile.write('#include "{0}"\n'.format(headername))

    outfile.write("\n")

    outfile.write("class CarsWithGuns;\n")
    outfile.write("class Bdg_Car;\n")
    outfile.write("class ArenaGameMode;\n")

    outfile.write("\n")
    
    outfile.write("{0}::{0}() {{\n".format(classname))
    dumpTreeToCtor(tree, outfile, True)
    outfile.write("}\n\n")

    outfile.write("\n")
    outfile.write("\n")

    outfile.write("BtResult {0}::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) {{\n".format(classname))
    outfile.write("  return m_root->tick(game, mode, car, dt);\n")
    outfile.write("}\n\n")


def writeBTtoCppHeader(tree, outfile, classname):

    preProLabel = "GEN_"+classname.upper()

    outfile.write("#ifndef {0}\n".format(preProLabel))
    outfile.write("#define {0}\n".format(preProLabel))
    outfile.write("\n")
    outfile.write("// Behavior Tree Declaration\n\n")

    outfile.write('#include <memory>\n')    
    outfile.write("\n")
    outfile.write('#include "bt_node.h"\n')
    outfile.write('#include "btutil.h"\n\n')

    outfile.write("class CarsWithGuns;\n")
    outfile.write("class Bdg_Car;\n")

    outfile.write("\n")
    
    outfile.write("class {0} {{\n".format(classname))
    outfile.write("  public:\n")
    outfile.write("    {0}();\n".format(classname))
    outfile.write("    BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt);\n".format(classname))
    outfile.write("  private:\n")
    outfile.write("    std::unique_ptr<{0}> m_root;\n".format(tree.getCppClassName()))
    outfile.write("};\n\n")
    outfile.write("#endif // {0}\n".format(preProLabel))



treeRecipes = [
    ("../../AI/barrel.xml", "Barrel", "barrel_bt.gv", "gen_barrel.cpp", "gen_barrel.h", "BarrelAI"),
    ("../../AI/barrel_simple.xml", "BarrelSimple", "barrel_simple_bt.gv", "gen_barrelSimple.cpp", "gen_barrelSimple.h", "BarrelSimpleAI"),
    ]

for recipe in treeRecipes:
    nodes.reset()
    
    fn = recipe[0]
    
    tree = ET.parse(fn)
    
    root = tree.getroot()
    
    #print("root")
    #print(root)

    graphName = recipe[1]
    graphFileName = recipe[2]
    
    g = graphviz.Graph(graphName, filename=graphFileName)
    
    def traverseTree(node, depth=0):
        nameStr = node.tag
        if "name" in node.attrib:
            nameStr = "{0} ({1})".format(node.tag, node.attrib['name'])
    
        nodeObj = nodes.makeNode(node.tag, node.attrib, depth)
        
        printAtDepth(depth, nodeObj)
        nodeObj.addToGraph(g)
    
        for child in node:
            childObj = traverseTree(child, depth + 1)
            childObj.parent = nodeObj
            nodeObj.children.append(childObj)
    
        nodeObj.addChildLinksToGraph(g)
        return nodeObj
    
    rootObj = traverseTree(root)
    
    #g.view()

    cppFileName = recipe[3]
    hFileName = recipe[4]
    cppClassName = recipe[5]
    
    with open(cppFileName, "wt") as outfile:
        writeBTtoCpp(rootObj, outfile, cppClassName, hFileName)
    
    with open(hFileName, "wt") as outfile:
        writeBTtoCppHeader(rootObj, outfile, cppClassName)
    
    for u in sorted(nodes.unknownTags):
        print("Unknown tag:", u)
