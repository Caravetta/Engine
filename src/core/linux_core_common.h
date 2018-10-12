#ifndef CORE_API
#if __GNUC__ >= 4
    #define CORE_API __attribute__ ((visibility ("default")))
#else
    #define CORE_API
#endif
#endif
