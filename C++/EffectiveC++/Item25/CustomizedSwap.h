#ifndef C9243B1F_FD75_461B_9290_1118E4ADE29B
#define C9243B1F_FD75_461B_9290_1118E4ADE29B

#include <iostream>

#include "Widget.h"

namespace WidgetStuff {
    void swap(Widget &a, Widget& b) {
        std::cout << "Using customized swap!" << std::endl;
        a.swap(b);
    }
}

#endif /* C9243B1F_FD75_461B_9290_1118E4ADE29B */
