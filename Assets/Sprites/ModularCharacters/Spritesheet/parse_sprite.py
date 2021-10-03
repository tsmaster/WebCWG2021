import xml.etree.ElementTree as et

#tree = et.parse('sheet_shirts.xml')
#tree = et.parse('sheet_face.xml')
tree = et.parse('sheet_hair.xml')

root = tree.getroot()
print(root)

for child in root:
    print("    {%d, %d, %d, %d}, // %s" % (
        int(child.attrib['x']),
        int(child.attrib['y']),
        int(child.attrib['width']),
        int(child.attrib['height']),
        child.attrib['name']))
