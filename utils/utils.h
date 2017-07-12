
void profiler_print( const char *szText )
{
	printf("Profiler:%s", szText);
}
#define USE_PROFILER 1
#define LIB_PROFILER_IMPLEMENTATION
#define LIB_PROFILER_PRINTF profiler_print
#include "libProfiler.h"
