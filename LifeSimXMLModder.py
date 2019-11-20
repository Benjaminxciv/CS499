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

print("=====LAND INFO=====")
land_width = int(input("What is the width of the grid? "))
land_height = int(input("What is the height of the grid? "))
print()

print("=====PLANT INFO=====")
p_count = int(input("How many plants do you want? "))
p_grow_rate = float(input("What is the growth rate for plants? "))
p_max_size = int(input("What is the maximum size for plants? "))
p_seed_cast_dist = int(input("What is the maximum cast distance for seeds? "))
p_max_seed = int(input("What is the maximum number of seeds? "))
p_seed_viability = float(input("What is the viability of seeds? "))

single_plants_info = []
for plant in range(0, p_count):
    location = input("What is the X and Y location of plant " + str(plant+1) + "? (X,Y) ")
    x_loc, y_loc = location.split(",")
    x_loc = int(x_loc)
    y_loc = int(y_loc)
    diameter = int(input("What is the diameter of the plant? "))
    single_plants_info.append(single_plant_xml(E, x_loc, y_loc, diameter))
print()

print("=====GRAZER INFO=====")
g_count = int(input("How many grazers do you want? "))
g_e_in = int(input("What is the energy input for grazers eating? "))
g_e_out = int(input("What is the energy output for grazer movement? "))
g_e_reprod = int(input("What is the energy minimum required for grazer reproduction? "))
g_main_speed = float(input("What is the maximum time for grazers can run? "))
g_max_speed = float(input("What is the maximum speed for grazers? "))

single_grazers_info = []
for grazer in range(0,g_count):
    location = input("What is the X and Y location of grazer " + str(grazer+1) + "? (X,Y) ")
    x_loc, y_loc = location.split(",")
    x_loc = int(x_loc)
    y_loc = int(y_loc)
    init_e = int(input("What is the initial energy of the grazer? "))
    single_grazers_info.append(single_grazer_xml(E, x_loc, y_loc, init_e))
print()

print("=====PREDATOR INFO=====")
p_count = int(input("How many predators do you want? "))
p_max_spd_hod = float(input("What is the maximum speed for HOD predators? "))
p_max_spd_hed = float(input("What is the maximum speed for HED predators? "))
p_max_spd_hor = float(input("What is the maximum speed for HOR predators? "))
p_main_speed = float(input("What is the maximum time predators can run? "))
p_e_out = int(input("What is the energy output for predator movement? "))
p_e_reprod = int(input("What is the energy minimum required for predator reproduction? "))
p_max_off = int(input("What is the maximum number of offspring a predator can produce? "))
p_gestation = float(input("What is the number of days that the predator gestation period lasts? "))
p_off_e = int(input("What is the initial energy of predator offspring? "))

single_predators_info = []
for predator in range(0,p_count):
    location = input("What is the X and Y location of predator " + str(predator+1) + "? (X,Y) ")
    x_loc, y_loc = location.split(",")
    x_loc = int(x_loc)
    y_loc = int(y_loc)
    init_e = int(input("What is the initial energy of the predator? "))
    genotype = input("What is the genotype for the predator? ")
    single_predators_info.append(single_predator_xml(E, x_loc, y_loc, init_e, genotype))
print()

print("=====OBSTACLE INFO=====")
o_count = int(input("How many obstacles do you want? "))
single_obstacles_info = []
for obstacle in range(0,o_count):
    location = input("What is the X and Y location of obstacle " + str(obstacle+1) + "? (X,Y) ")
    x_loc, y_loc = location.split(",")
    x_loc = int(x_loc)
    y_loc = int(y_loc)
    diameter = int(input("What is the diameter of the obstacle? "))
    height = int(input("What is the height of the obstacle? "))
    single_obstacles_info.append(single_obstacle_xml(E, x_loc, y_loc, diameter, height))

sim_xml = LIFE_SIMULATION(
    land_xml(E, land_width, land_height),
    plants_xml(E, p_count, p_grow_rate, p_max_size, p_seed_cast_dist, p_max_seed, p_seed_viability, single_plants_info),
    grazers_xml(E, g_count, g_e_in, g_e_out, g_e_reprod, g_main_speed, g_max_speed, single_grazers_info),
    predators_xml(E, p_count, p_max_spd_hod, p_max_spd_hed, p_max_spd_hor,
                    p_main_speed, p_e_out, p_e_reprod, p_max_off, p_gestation,
                    p_off_e, single_predators_info),
    obstacles_xml(E, o_count, single_obstacles_info)
)

xml_file_name = input("What is the name of the XML file you want to write out to? ")

with open(xml_file_name, 'wb') as txml:
    txml.write(lxml.etree.tostring(sim_xml, pretty_print=True))
