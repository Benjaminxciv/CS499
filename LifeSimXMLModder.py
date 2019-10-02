'''from lxml import etree

tree = etree.parse('LifeSimulation01.xml')
root = tree.getroot()

for elem in root.iter('*'):
    if elem.text is not None and elem.text.strip() != '':
        elem.text = elem.text.strip()
        print(elem.tag)
        print(elem.text)'''

import lxml.etree
import lxml.builder    

E = lxml.builder.ElementMaker()
LIFE_SIMULATION = E.LIFE_SIMULATION

def land_xml(E, x_size, y_size):
    LAND_BOUNDS = E.LAND_BOUNDS
    WIDTH = E.WIDTH
    HEIGHT = E.HEIGHT
    LAND = LAND_BOUNDS(
        WIDTH('\n        ' + str(x_size), '\n    '),
        HEIGHT('\n        ' + str(y_size),'\n    ')
    )
    return LAND

def plants_xml(E, count, grow_rate, size, seed_cast, seed_num, seed_via, individual_plants):
    PLANTS = E.PLANTS
    INITIAL_PLANT_COUNT = E.INITIAL_PLANT_COUNT
    GROWTH_RATE = E.GROWTH_RATE
    MAX_SIZE = E.MAX_SIZE
    MAX_SEED_CAST_DISTANCE = E.MAX_SEED_CAST_DISTANCE
    MAX_SEED_NUMBER = E.MAX_SEED_NUMBER
    SEED_VIABILITY = E.SEED_VIABILITY
    PLANTS_INFO = PLANTS(
        INITIAL_PLANT_COUNT('\n        ' + str(count), '\n    '),
        GROWTH_RATE('\n        ' + str(grow_rate), '\n    '),
        MAX_SIZE('\n        ' + str(size), '\n    '),
        MAX_SEED_CAST_DISTANCE('\n        ' + str(seed_cast), '\n    '),
        MAX_SEED_NUMBER('\n        ' + str(seed_num), '\n    '),
        SEED_VIABILITY('\n        ' + str(seed_via), '\n    '),
    )
    for plant in individual_plants:
        PLANTS_INFO.insert(len(PLANTS_INFO), plant)
    return PLANTS_INFO

def single_plant_xml(E, x_loc, y_loc, diameter):
    PLANT = E.PLANT
    X_POS = E.X_POS
    Y_POS = E.Y_POS
    P_DIAMETER = E.P_DIAMETER
    PLANT_INFO = PLANT(
        X_POS('\n        ' + str(x_loc), '\n      '),
        Y_POS('\n        ' + str(y_loc), '\n      '),
        P_DIAMETER('\n        ' + str(diameter), '\n      ')
    )
    return PLANT_INFO

def grazers_xml(E, count, energy_in, energy_out, energy_reprod, main_speed, max_speed,
                individual_grazers):
    GRAZERS = E.GRAZERS
    INITIAL_GRAZER_COUNT = E.INITIAL_GRAZER_COUNT
    ENERGY_INPUT = E.G_ENERGY_INPUT
    ENERGY_OUTPUT = E.G_ENERGY_OUTPUT
    ENERGY_REPRODUCE = E.G_ENERGY_TO_REPRODUCE
    MAINTAIN_SPEED = E.G_MAINTAIN_SPEED
    MAXIMUM_SPEED = E.G_MAX_SPEED
    GRAZERS_INFO = GRAZERS(
        INITIAL_GRAZER_COUNT('\n        ' + str(count), '\n    '),
        ENERGY_INPUT('\n        ' + str(energy_in), '\n    '),
        ENERGY_OUTPUT('\n        ' + str(energy_out), '\n    '),
        ENERGY_REPRODUCE('\n        ' + str(energy_reprod), '\n    '),
        MAINTAIN_SPEED('\n        ' + str(main_speed), '\n    '),
        MAXIMUM_SPEED('\n        ' + str(max_speed), '\n    '),
    )
    for grazer in individual_grazers:
        GRAZERS_INFO.insert(len(GRAZERS_INFO), grazer)
    return GRAZERS_INFO

def single_grazer_xml(E, x_loc, y_loc, init_energy):
    GRAZER = E.GRAZER
    X_POS = E.X_POS
    Y_POS = E.Y_POS
    ENERGY_LEVEL = E.G_ENERGY_LEVEL
    GRAZER_INFO = GRAZER(
        X_POS('\n        ' + str(x_loc), '\n      '),
        Y_POS('\n        ' + str(y_loc), '\n      '),
        ENERGY_LEVEL('\n        ' + str(init_energy), '\n      ')
    )
    return GRAZER_INFO

def predators_xml(E, count, max_speed_hod, max_speed_hed, max_speed_hor, main_speed, energy_out,
                  energy_reprod, max_off, gestation, off_energy, individual_predators):
    PREDATORS = E.PREDATORS
    INITIAL_PREDATORS_COUNT = E.INITIAL_PREDATORS_COUNT
    MAXIMUM_SPEED_HOD = E.MAX_SPEED_HOD
    MAXIMUM_SPEED_HED = E.MAX_SPEED_HED
    MAXIMUM_SPEED_HOR = E.MAX_SPEED_HOR
    MAINTAIN_SPEED = E.P_MAINTAIN_SPEED
    ENERGY_OUTPUT = E.P_ENERGY_OUTPUT
    ENERGY_REPRODUCE = E.P_ENERGY_TO_REPRODUCE
    MAXIMUM_OFFSPRING = E.MAX_OFFSPRING
    GESTATION_PERIOD = E.P_GESTATION
    OFFSPRING_ENERGY = E.P_OFFSPRING_ENERGY
    PREDATORS_INFO = PREDATORS(
        INITIAL_PREDATORS_COUNT('\n        ' + str(count), '\n    '),
        MAXIMUM_SPEED_HOD('\n        ' + str(max_speed_hod), '\n    '),
        MAXIMUM_SPEED_HED('\n        ' + str(max_speed_hed), '\n    '),
        MAXIMUM_SPEED_HOR('\n        ' + str(max_speed_hor), '\n    '),
        MAINTAIN_SPEED('\n        ' + str(main_speed), '\n    '),
        ENERGY_OUTPUT('\n        ' + str(energy_out), '\n    '),
        ENERGY_REPRODUCE('\n        ' + str(energy_reprod), '\n    '),
        MAXIMUM_OFFSPRING('\n        ' + str(max_off), '\n    '),
        GESTATION_PERIOD('\n        ' + str(gestation), '\n    '),
        OFFSPRING_ENERGY('\n        ' + str(off_energy), '\n    '),
    )
    for predator in individual_predators:
        PREDATORS_INFO.insert(len(PREDATORS_INFO), predator)
    return PREDATORS_INFO

def single_predator_xml(E, x_loc, y_loc, init_energy, genotype):
    PREDATOR = E.PREDATOR
    X_POS = E.X_POS
    Y_POS = E.Y_POS
    ENERGY_LEVEL = E.P_ENERGY_LEVEL
    PRED_GENOTYPE = E.GENOTYPE
    PREDATOR_INFO = PREDATOR(
        X_POS('\n        ' + str(x_loc), '\n      '),
        Y_POS('\n        ' + str(y_loc), '\n      '),
        ENERGY_LEVEL('\n        ' + str(init_energy), '\n      '),
        PRED_GENOTYPE('\n        ' + str(genotype), '\n      ')
    )
    return PREDATOR_INFO

def obstacles_xml(E, count, individual_obstacles):
    OBSTACLES = E.OBSTACLES
    INITIAL_OBSTACLE_COUNT = E.INITIAL_OBSTACLE_COUNT
    OBSTACLES_INFO = OBSTACLES(
        INITIAL_OBSTACLE_COUNT('\n        ' + str(count), '\n    ')
    )
    for obstacle in individual_obstacles:
        OBSTACLES_INFO.insert(len(OBSTACLES_INFO), obstacle)
    return OBSTACLES_INFO

def single_obstacle_xml(E, x_loc, y_loc, diameter, height):
    OBSTACLE = E.OBSTACLE
    X_POS = E.X_POS
    Y_POS = E.Y_POS
    OBS_DIAMETER = E.O_DIAMETER
    OBS_HEIGHT = E.O_HEIGHT
    OBSTACLE_INFO = OBSTACLE(
        X_POS('\n        ' + str(x_loc), '\n      '),
        Y_POS('\n        ' + str(y_loc), '\n      '),
        OBS_DIAMETER('\n        ' + str(diameter), '\n      '),
        OBS_HEIGHT('\n        ' + str(height), '\n      ')
    )
    return OBSTACLE_INFO

single_plants_info = []
for plant in range(0, 1):
    single_plants_info.append(single_plant_xml(E, 50, 125, 25))

single_grazers_info = []
for grazer in range(0,1):
    single_grazers_info.append(single_grazer_xml(E, 50, 125, 25))

single_predators_info = []
for predator in range(0,1):
    single_predators_info.append(single_predator_xml(E, 275, 125, 450, 'AA SS FF'))

single_obstacles_info = []
for obstacle in range(0,1):
    single_obstacles_info.append(single_obstacle_xml(E, 100, 50, 50, 15))

sim_xml = LIFE_SIMULATION(
    land_xml(E, 1000, 750),
    plants_xml(E, 25, 0.1, 100, 250, 10, 0.50, single_plants_info),
    grazers_xml(E, 15, 5, 1, 100, 3.0, 20.0, single_grazers_info),
    predators_xml(E, 5, 20.0, 18.0, 15.0, 4.0, 10, 500, 3, 5.0, 100, single_predators_info),
    obstacles_xml(E, 15, single_obstacles_info)
)
    
with open('test.xml', 'wb') as txml:
    txml.write(lxml.etree.tostring(sim_xml, pretty_print=True))
