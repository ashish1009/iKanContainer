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

#define IK_TRACE(...)          ::iKan::Log::Trace(__VA_ARGS__)


#ifdef IK_ENABLE_BUFFER_LOG
    #define IK_BUFFER_TRACE(...)          ::iKan::Log::Trace(__VA_ARGS__)
#else
    #define IK_BUFFER_TRACE(...)
#endif

#ifdef IK_ENABLE_VECTOR_LOG
    #define IK_VECTOR_TRACE(...)          ::iKan::Log::Trace(__VA_ARGS__)
#else
    #define IK_VECTOR_TRACE(...)
#endif
