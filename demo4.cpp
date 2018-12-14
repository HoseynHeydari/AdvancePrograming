#include "rsdl.h"

int main()
{
    window w(300, 300);

    for (double x = 0; x < 300; x += 0.1) {
        // y = 0.1x^2
        w.draw_point(x, 300 - 0.1*x*x, BLACK);
        // y = 2x + 3
        w.draw_point(x, 300 - (2*x + 3), RED);
    }

    bool quit = false;
    while (!quit) {
        HANDLE(
            QUIT(quit = true);
        );
    }

    return 0;
}
