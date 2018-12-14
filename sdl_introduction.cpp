#include "rsdl.h"

int main()
{
	window w(450, 900);

    w.draw_bmp(10, 10, 20, 30, RGB(128, 128, 255));

    bool quit = false;
    while (!quit) {
        HANDLE(
            QUIT(quit = true);
        );
    }

	return 0;
}
