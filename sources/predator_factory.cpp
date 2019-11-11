/*
Name: predator_factory.cpp
Purpose: Abstract factory that houses genetics for predators. 
Last edit: 11-11-2019
Last editor: MG
*/

#include "predator_factory.h"

predator_factory::predator_factory()
{

}

predator_factory::~predator_factory()
{

}

/*
Name: punnett_square
Purpose: everytime it is called, it returns the gene of one parent. If they're the same gene, it just returns the first.
         If the genes are different, it has a 50/50 percent chance of which it returns. Follows Mendel's genetics.
Trace: Traces to Epic 3, Acceptance Criteria 3
Parameters: two characters of same genotype from one predator parent.
Returns: one character of same genotype from one predator parent to pass on to the child.
*/
char predator_factory::punnett_square(char gene_one, char gene_two)
{
    if (gene_one != gene_two)
    {
        srand(time(NULL));
        int i = rand() % 2 + 1;

        if ((i % 2) == 0)
        {
            cout<< "i= " << i;
            cout<< "if:  " << gene_one;
            return gene_one;
        }
        else 
        {
            cout<< "i== " <<i;
            cout<< "else:  " << gene_two;
            return gene_two;
        }
        
    }
    else
    {
        cout<< "last else:  " << gene_one;
        return gene_one;   
    }
}

/*
used to test punnett_squares 

int main()
{
    predator_factory* start = new predator_factory();
    char gene_one = 'a';
    char gene_two = 'A';
    start->punnett_square(gene_one, gene_two);
}*/