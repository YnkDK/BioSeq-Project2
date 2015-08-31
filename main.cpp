/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** main.cpp
** TODO: How to run this?
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/
#include "alignment.h"
#include "global_linear.h"

using namespace std;

int main(int argc, char** argv) {
    vector<Alignment *> algorithms = {
            new GlobalLinear()
    };

    return 0;
}