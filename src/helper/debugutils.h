
#if defined(DEBUG_BUILD) && !defined(NO_DEBUG_OUTPUT)
#define dprintf(format, ...) printf( "[" __TIME__ "] [DEBUG] " format, __VA_ARGS__)
#define eprintf(format, ...) fprintf(stderr, "[" __TIME__ "] [ERROR] " format, __VA_ARGS__)
#else
#define dprintf(format, ...)
#define eprintf(format, ...)
#endif