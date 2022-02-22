#include "interface.h"

int main() {
    srand(time(NULL));

    Universe universe(100,20,5);
    universe.update();

    return 0;
}
