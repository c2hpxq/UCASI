#include <algorithm>

#include "Widget.h"
#include "CustomizedSwap.h"

int main() {
    using std::swap;

    WidgetStuff::Widget a;
    WidgetStuff::Widget b;
    swap(a, b);

    return 0;

}