import xml.etree.ElementTree as ET

# etree examples at https://docs.python.org/3/library/xml.etree.elementtree.html

import graphviz

# graphviz examples at https://graphviz.readthedocs.io/en/stable/examples.html


from btutil import *
import nodes


def dumpTreeToCtor(tree, outfile, isRoot=False):
    if (isRoot):
        outfile.write("  m_root = {0}();\n".format(tree.getCppClassName()))
        nodeCppName = "m_root"
    else:
        nodeCppName = tree.getCppNodeName()
        outfile.write("  {0} {1};\n".format(tree.getCppClassName(),
                                            nodeCppName))
    for c in tree.children:
        cName = dumpTreeToCtor(c, outfile, False)
        outfile.write("  {0}.add({1});\n".format(nodeCppName, cName))
    return nodeCppName

def writeBTtoCpp(tree, outfile, classname, headername):
    outfile.write("// Behavior Tree Implementation\n\n")

    outfile.write('#include "{0}"\n'.format(headername))
    outfile.write("\n")
    outfile.write("{0}::{0}() {{\n".format(classname))
    dumpTreeToCtor(tree, outfile, True)
    outfile.write("}\n\n")

    outfile.write("\n")
    outfile.write("\n")

    outfile.write("BtResult {0}::tick(float dt) {{\n".format(classname))
    outfile.write("  return m_root.tick(dt);\n")
    outfile.write("}\n\n")


def writeBTtoCppHeader(tree, outfile, classname):
    outfile.write("// Behavior Tree Declaration\n\n")

    outfile.write('#include "btutil.h"\n\n')
    outfile.write("class {0} {{\n".format(classname))
    outfile.write("  public:\n")
    outfile.write("    {0}();\n".format(classname))
    outfile.write("    BtResult tick(float dt);\n".format(classname))
    outfile.write("  private:\n")
    outfile.write("    {0} m_root;\n".format(tree.getCppClassName()))
    outfile.write("};\n\n")



treeRecipes = [
    ("../../AI/barrel.xml", "Barrel", "barrel_bt.gv", "barrel.cpp", "barrel.h", "BarrelAI"),
    ("../../AI/barrel_simple.xml", "BarrelSimple", "barrel_simple_bt.gv", "barrelSimple.cpp", "barrelSimple.h", "BarrelSimpleAI"),
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
