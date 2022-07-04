#pragma once

#include <ncurses.h>

class Board {
  public:
    /// Constructors
    explicit Board(WINDOW *win);

    /// Getters
    int GetX() const { return this->xMax_ - 1; }
    int GetY() const { return this->yMax_ - 1; }
    int GetSize() const { return (this->xMax_ - 1) * (this->yMax_ - 1); }
    WINDOW *GetWin() const { return this->window_; }

    /// Operations
    /// @brief prints a chtype cha to the board window in the position (ver,hor)
    /// @param ver, vertical coordinate
    /// @param hor, horizontal coordinate
    /// @param cha, desired chtype to print
    void Print(const int &ver, const int &hor, const chtype &cha) const;

  private:
    WINDOW *window_;
    int yMax_, xMax_;
};
