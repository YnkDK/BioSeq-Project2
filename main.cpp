//
// Created by mys on 8/31/15.
//

#include "alignment.h"
#include "global_linear.h"

using namespace std;

int main(int argc, char** argv) {
    vector<Alignment *> algorithms = {
            new GlobalLinear()
    };

    return 0;
}