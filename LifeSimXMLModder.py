import xml.etree.ElementTree as ET
root = ET.parse('LifeSimulation01.xml').getroot()
for type_tag in root.findall('LAND_BOUNDS/WIDTH'):
    value = type_tag.get('')
    print(value)
    print(type_tag)
