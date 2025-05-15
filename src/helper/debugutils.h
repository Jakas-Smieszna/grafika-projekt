#if defined(DEBUG_BUILD) && !defined(NO_DEBUG_OUTPUT)
/// Wypisuje jedną linijke informacji do debugowania.
#define dbgprintf(format, ...) printf("[DEBUG] " format "\n", __VA_ARGS__)
/// Wypisuje jedną linijke informacji o błędzie.
#define eprintf(format, ...) fprintf(stderr, "[ERROR] " format "\n", __VA_ARGS__)
#else
#define dbgprintf(format, ...)
#define eprintf(format, ...)
#endif