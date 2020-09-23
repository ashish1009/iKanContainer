#pragma once
#include <iostream>

namespace iKan {

    class Log
    {
    public:
        static void Trace(const char* format, ...)
        {
            va_list argptr;
            va_start(argptr, format);
            printf("[Debug Log]:    ");
            vprintf(format, argptr);
            printf("\n");
            va_end(argptr);
        }
    };
    
}

#ifdef IK_ENABLE_LOG

#define IK_TRACE(...)          ::iKan::Log::Trace(__VA_ARGS__)

#else

#define IK_TRACE(...)

#endif
