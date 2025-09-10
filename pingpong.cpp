#include <iostream>
#include <conio.h>   // for _kbhit() and _getch()
#include <windows.h> // for Sleep()
using namespace std;

const int width = 40;
const int height = 20;

int ballX, ballY;         // Ball position
int ballDirX = 1, ballDirY = 1;
int paddle1Y, paddle2Y;   // Paddles position
int score1 = 0, score2 = 0;

void setup() {
    ballX = width / 2;
    ballY = height / 2;
    paddle1Y = height / 2;
    paddle2Y = height / 2;
}

void draw() {
    system("cls");  // Clear screen

    // Top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int y = 0; y < height; y++) {
        cout << "#"; // left wall
        for (int x = 0; x < width; x++) {
            if (x == ballX && y == ballY) cout << "O"; // Ball
            else if (x == 1 && y >= paddle1Y - 2 && y <= paddle1Y + 2) cout << "|"; // Left paddle
            else if (x == width - 2 && y >= paddle2Y - 2 && y <= paddle2Y + 2) cout << "|"; // Right paddle
            else cout << " ";
        }
        cout << "#\n"; // right wall
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: Player1 = " << score1 << "  Player2 = " << score2 << endl;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'w' && paddle1Y > 2) paddle1Y--;       // Move left paddle up
        if (ch == 's' && paddle1Y < height - 3) paddle1Y++; // Move left paddle down
        if (ch == 'i' && paddle2Y > 2) paddle2Y--;       // Move right paddle up
        if (ch == 'k' && paddle2Y < height - 3) paddle2Y++; // Move right paddle down
    }
}

void logic() {
    ballX += ballDirX;
    ballY += ballDirY;

    // Ball collision with top and bottom walls
    if (ballY <= 0 || ballY >= height - 1) ballDirY *= -1;

    // Ball collision with paddles
    if (ballX == 2 && ballY >= paddle1Y - 2 && ballY <= paddle1Y + 2) ballDirX = 1;
    if (ballX == width - 3 && ballY >= paddle2Y - 2 && ballY <= paddle2Y + 2) ballDirX = -1;

    // Ball out of bounds
    if (ballX <= 0) {
        score2++;
        setup();
    }
    if (ballX >= width - 1) {
        score1++;
        setup();
    }
}

int main() {
    setup();
    while (true) {
        draw();
        input();
        logic();
        Sleep(50); // Control speed
    }
    return 0;
}

