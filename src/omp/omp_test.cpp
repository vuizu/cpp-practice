#include "macros_omp_format.h"
#include <iostream>
#include <omp.h>

int main(int argc, char* argv[]) {
#ifdef OMP_USAGE

    #pragma omp parallel num_threads(4)
    {
        std::cout << "hello" << std::endl;
    }

#endif
}