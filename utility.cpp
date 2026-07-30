#include <iostream>


void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left
}

void moveCursorToTop() {
    std::cout << "\033[H"; // Move cursor to top-left only
}

void clearBelowLine(int line) {
    // Move cursor to specified line (line starts from 1)
    std::cout << "\033[" << line << ";1H";
    // Clear everything from cursor to end of screen
    std::cout << "\033[J";
}

void clearToLine(int line) {
    // Move cursor to specified line (line starts from 1) at the first column
    std::cout << "\033[" << line << ";1H";
    // Clear everything from the beginning of the screen down to the current cursor position
    std::cout << "\033[1J";
}
