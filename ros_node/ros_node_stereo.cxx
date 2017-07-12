#include <iostream>
#include <math.h>

#include "utils.h"


void myFunction()
{
    PROFILER_START(Myfunction);
    float v = 0;
    for(int i = 0;i<100;i++){
      PROFILER_START(test);
      usleep (1000);
      PROFILER_END();
      v += cosf(static_cast<float>(rand()));

    }


    printf("v = %5.4f\n", v);
    PROFILER_END();
}

int main(int argc, const char * argv[]) {
    PROFILER_ENABLE;

    PROFILER_START(Main);

    std::cout << "Hello, World!\n";
    myFunction();
    myFunction();

    PROFILER_END();

    LogProfiler();

    PROFILER_DISABLE;

    return 0;
}
