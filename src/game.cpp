#include "game.hpp"
#include "random.hpp"

#define f first
#define s second

void Game::readInput() {
    int userInputKey = wgetch(this->grid.getWin());

    switch (userInputKey) {
        case QUIT: this->gameOver = true; break;
        case ACTION: this->jumped = true; break;
    }
}

void Game::print() const {
    const matrix M = this->gate.getPipes();
    const pair<int, int> B = this->gate.getBird();

    // Clear screen (probably stupid)
    werase(this->grid.getWin());
    box(this->grid.getWin(), 0, 0);

    // Print pipes
    for (const auto &pipe : M) {
        for (uint i = 1; i <= pipe.size(); ++i) {
            const pair<int, bool> P = pipe[i];
            if (P.s) {
                this->grid.print(i, P.f, PIPE);
            }
        }
    }

    // Print bird
    this->grid.print(B.f, B.s, BIRD);

    wrefresh(this->grid.getWin());
}

void Game::update() {
    const int CEIL = 5;

    if (Random::rng(0, CEIL) == 0) {
        this->gate.spawnPipe();
    }

    if (this->jumped) {
        this->gate.jump();
        this->jumped = false; // Reset movement
    }

    bool success = this->gate.move();

    if (!success) {
        this->gameOver = true;
    }
}

void Game::quit() {
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);

    const string MESSAGE = "GAME OVER";
    const int X = MESSAGE.size() + 2;

    WINDOW *quitWin = newwin(3, X, (yMax - 3) / 2, (xMax - X) / 2);

    nocbreak(); // Disables half-delay mode
    box(quitWin, 0, 0);
    mvwprintw(quitWin, 1, 1, "%s", MESSAGE.c_str());
    wgetch(quitWin);
    delwin(quitWin);
}
