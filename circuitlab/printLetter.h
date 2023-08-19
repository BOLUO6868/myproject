#pragma once
#pragma once
#include"Tools.h"
#include"Gate.h"
#include"Line.h"
#include"test.h"
#include"Interface.h"
#include"SaveAndRead.h"
#include"globals.h"
#include"freeDesign.h"
#include"mainMenu.h"



void print_A(int x, int y) {
    setColorAttr(107);
    setpos(x + 3, y);
    cout << " ";
    setpos(x + 1, y + 1);
    cout << "  ";
    setpos(x + 4, y + 1);
    cout << "  ";

    setpos(x, y + 2);
    cout << "  ";
    setpos(x + 5, y + 2);
    cout << "  ";

    setpos(x, y + 3);
    cout << "       ";
    setpos(x, y + 4);
    cout << "  ";
    setpos(x + 5, y + 4);
    cout << "  ";

}


void print_C(int x, int y) {
    setColorAttr(107);
    setpos(x, y);
    cout << "      ";
    for (int i = 0; i < 3; i++) {
        setpos(x, y + i + 1);
        cout << "  ";
    }

    setpos(x, y + 4);
    cout << "      ";
}

void print_I(int x, int y) {
    setColorAttr(107);
    setpos(x + 1, y);
    cout << "    ";
    for (int i = 0; i < 3; i++) {
        setpos(x + 2, y + 1 + i);
        cout << "  ";
    }

    setpos(x + 1, y + 4);
    cout << "    ";
}


void print_R(int x, int y) {
    setColorAttr(107);
    setpos(x, y);
    cout << "      ";
    setpos(x, y + 1);
    cout << "  ";
    setpos(x + 4, y + 1);
    cout << "  ";
    setpos(x, y + 2);
    cout << "      ";
    setpos(x, y + 3);
    cout << "  ";
    setpos(x + 3, y + 3);
    cout << "  ";

    setpos(x, y + 4);
    cout << "  ";
    setpos(x + 4, y + 4);
    cout << "  ";
}


void print_T(int x, int y) {
    setpos(x, y);
    cout << "      ";
    for (int i = 1; i <= 4; i++) {
        setpos(x + 2, y + i);
        cout << "  ";
    }
}


void print_L(int x, int y) {

    for (int i = y; i <= y + 4; i++) {
        setpos(x, i);
        setColorAttr(107);
        cout << "  ";
    }
    for (int i = x + 2; i <= x + 5; i++) {
        setpos(i, y + 4);
        setColorAttr(107);
        cout << " ";
    }
}


void print_U(int x, int y) {
    setColorAttr(107);
    for (int i = 0; i < 4; i++) {
        setpos(x, y + i);
        cout << "  ";
        setpos(x + 4, y + i);
        cout << "  ";
    }
    setpos(x, y + 4);
    cout << "      ";

}


void print_B(int x, int y) {
    setColorAttr(107);
    setpos(x, y);
    cout << "     ";
    setpos(x, y + 1);
    cout << "  ";
    setpos(x + 3, y + 1);
    cout << "  ";
    setpos(x, y + 2);
    cout << "      ";

    setpos(x, y + 3);
    cout << "  ";
    setpos(x + 4, y + 3);
    cout << "  ";

    setpos(x, y + 4);
    cout << "      ";
}

