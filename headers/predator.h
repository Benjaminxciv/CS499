/*
Name: predator.h
Purpose: Header file for predators.
Last edit: 12-3-19
Last editor: MG
*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include <map>
#include "mammal.h"

class predator : public mammal
{
    private:
        std::string genotype;
        double max_speed_hod;
        double max_speed_hed;
        double max_speed_hor;
        int max_offspring;
        double gestation_period;
        int offspring_energy_level;
        time_container current_time;
        int move_count;
        void eat(point);

        bool a_homo_dom;
        bool a_het_dom;
        bool a_homo_rec;

        bool s_homo_dom;
        bool s_het_dom;
        bool s_homo_rec;

        bool f_homo_dom;
        bool f_het_dom;
        bool f_homo_rec;

        void aggression_food_check(point, point&, point&);
        bool eat_grazer();
        vector<time_container> babies;
        map<int, time_container> children;

        bool is_baby;
        bool is_pregnant;
        
    public:
        predator(point, std::string, int, int, int, double, double, double, double, double, int, double, int, bool baby = false);
        ~predator();
        std::string get_type();
        int print_self();
        int get_max_offspring();
        std::string get_genotype();
        void act();
        static int success_generator();
        bool get_s_homo_dom();
        bool get_s_het_dom();
        bool get_s_homo_rec();
};

#endif