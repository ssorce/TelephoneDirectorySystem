#include <iostream>
#include <string>
#include <stdio.h>

#ifndef DEBUG_H
#define DEBUG_H
#define RUN 1 // Toggle DEBUG MODE
#define DEBUG(...)                                                                           \
    if ((int)RUN)                                                                            \
        cout << "\nDEBUG INFO:\nLINE: " << __LINE__ << "\nFILE: " << __FILE__ << "\nINPUT: " \
             << __VA_ARGS__ << "\nEND OF DEBUG INFO\n\n";

#endif // !DEBUG_H