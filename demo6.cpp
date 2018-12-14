#include <iostream>
#include "rsdl.h"
using namespace std;

int main()
{
    const int SIZE = 30;
    const int WIDTH = 300;
    const int HEIGHT = 300;

    window w(WIDTH, HEIGHT);
    w.fill_rect(0, 0, WIDTH, HEIGHT, WHITE);

    int rows = HEIGHT / SIZE;
    int cols = WIDTH / SIZE;
    
    bool table[rows][cols];

    // initialize the table
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            table[i][j] = 0;

    // draw the grid
    for (int i = 0; i < rows; i++)
        w.draw_line(0, i * SIZE, WIDTH, i * SIZE, BLACK);
    for (int j = 0; j < cols; j++)
        w.draw_line(j * SIZE, 0, j * SIZE, HEIGHT, BLACK);

    bool quit = false;
    while (!quit) {
        HANDLE(
            QUIT(quit = true);
            LCLICK( {
                cout << "Mouse clicked at: (" << mouse_x << "," << mouse_y << ")\n";
                int i = mouse_y / SIZE;
                int j = mouse_x / SIZE;
                table[i][j] = !table[i][j];
                w.fill_rect(j * SIZE, i * SIZE, SIZE, SIZE, table[i][j] ? MAGENTA : WHITE);
                w.draw_rect(j * SIZE, i * SIZE, SIZE+1, SIZE+1, BLACK);
            });
            KEY_PRESS(c, {
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        table[i][j] = 0;
                w.fill_rect(0, 0, WIDTH, HEIGHT, WHITE);
                // draw the grid
                for (int i = 0; i < rows; i++)
                    w.draw_line(0, i * SIZE, WIDTH, i * SIZE, BLACK);
                for (int j = 0; j < cols; j++)
                    w.draw_line(j * SIZE, 0, j * SIZE, HEIGHT, BLACK);
            });
            KEY_PRESS(q, quit = true);
        );
    }

    return 0;
}