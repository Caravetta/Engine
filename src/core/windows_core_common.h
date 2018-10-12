#ifdef CORE_EXPORT
  #ifdef __GNUC__
    #define CORE_API __attribute__ ((dllexport))
  #else
    #define CORE_API __declspec(dllexport)
  #endif
#else
  #ifdef __GNUC__
    #define CORE_API __attribute__ ((dllimport))
  #else
    #define CORE_API __declspec(dllimport) 
  #endif
#endif
