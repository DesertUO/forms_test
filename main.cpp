#include "program.h"

int main() {
    Program* p = new Program();
    p->init();
    p->run();

    delete p;

    return 0;
}
