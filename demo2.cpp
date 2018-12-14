#include "rsdl.h"

int main()
{
	window w(300, 300);

    w.fill_rect(10, 10, 20, 30, RGB(128, 128, 255));

    bool quit = false;
    while (!quit) {
        HANDLE(
            QUIT(quit = true);
        );
    }

	return 0;
}