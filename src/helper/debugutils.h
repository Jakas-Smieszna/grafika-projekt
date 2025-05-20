#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#if defined(DEBUG_BUILD) && !defined(NO_DEBUG_OUTPUT)

/// Wypisuje jedną linijke informacji do debugowania.
#define dbgprintf(format, ...) printf("[DEBUG] " format "\n", __VA_ARGS__)
/// Wypisuje jedną linijke informacji o błędzie.
#define eprintf(format, ...) fprintf(stderr, "[ERROR] " format "\n", __VA_ARGS__)
/// Wypisuje jedną linijke ostrzeżenia.
#define wrnprintf(format, ...) fprintf(stderr, "[WARN] " format "\n", __VA_ARGS__)

#else // nie ma tego w release

#define dbgprintf(format, ...)
#define eprintf(format, ...)
#define wrnprintf(format, ...)

#endif // defined(DEBUG_BUILD) && !defined(NO_DEBUG_OUTPUT)

#endif // DEBUGUTILS_H