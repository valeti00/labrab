#include <iostream>
#include "Game.h"
#include<fstream>
#include<string>
#include <cstdlib>
#include <ctime>

using namespace std;

Game initGame(char userChar) {
    srand(time(0));
    Game templ;
    for (int i = 0; i <= 2; i++)
    {
        for (int k = 0; k <= 2; k++)
            templ.bord[i][k] = ' ';
    }
    templ.isUserTurn = rand() % 2;
    templ.userChar = userChar;
    if (templ.userChar == '0') templ.botChar = 'X';
    else templ.botChar = '0';
    templ.status = PLAY;
    return templ;
}

void updateDisplay(const Game game) {
    system("cls");
    cout << endl;
    cout << "    a" << "    b" << "    c" << endl;
    cout << "-----------------\n 1  | "
        << game.bord[0][0] << " | " << game.bord[0][1] << " | " << game.bord[0][2] << " |\n"
        << "-----------------\n 2  | "
        << game.bord[1][0] << " | " << game.bord[1][1] << " | " << game.bord[1][2] << " |\n"
        << "-----------------\n 3  | "
        << game.bord[2][0] << " | " << game.bord[2][1] << " | " << game.bord[2][2] << " |\n"
        << "-----------------\n";
}
void botTurn(Game* game) {
    srand(time(0));
    int i = 0, k = 0, counter = 0, xi = 0, xk = 0;
    while (!game->isUserTurn) {
        if ((counter > 0) && (game->bord[i][k] == game->userChar)) {

            if ((xi == 0) && (k == xk) && (xi == (i - 2))) {
                if (game->bord[i - 1][k] == ' ') {
                    game->isUserTurn = 1;
                    game->bord[i - 1][k] = game->botChar;	break;
                }
            }
            if ((xi == 0) && (k == xk) && (xi == (i - 1))) {
                if (game->bord[i + 1][k] == ' ') {
                    game->bord[i + 1][k] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xi == 1) && (xk == k) && (i - xi == 1)) {
                if (game->bord[i - 2][k] == ' ') {
                    game->bord[i - 2][k] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }

            if ((xk == 0) && (xi == i) && (xk == (k - 1))) {
                if (game->bord[i][k + 1] == ' ') {
                    game->bord[i][k + 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xk == 0) && (xi == i) && (xk == (k - 2))) {

                if (game->bord[i][k - 1] == ' ') {
                    game->bord[i][k - 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xk == 1) && (xi == i) && (k - xk == 1)) {
                if (game->bord[i][k - 2] == ' ') {
                    game->bord[i][k - 2] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }

            if ((xi == 0) && (xi == xk) && (i == k) && (xi == (i - 1) && (i > xi))) {
                if (game->bord[i + 1][k + 1] == ' ') {
                    game->bord[i + 1][k + 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xi == 0) && (xi == xk) && (i == k) && (xi == (i - 2) && (i > xi))) {
                if (game->bord[i - 1][k - 1] == ' ') {
                    game->bord[i - 1][k - 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xi == 1) && (xi == xk) && (i == k) && (xi == (i - 1) && (i > xi))) {
                if (game->bord[i - 2][k - 2] == ' ') {
                    game->bord[i - 2][k - 2] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }

            if ((xi == 0) && (i + k == 2) && (xk == 2) && (xi == (i - 1))) {
                if (game->bord[i + 1][k - 1] == ' ') {
                    game->bord[i + 1][k - 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xi == 0) && (i + k == 2) && (xk == 2) && (xi == (i - 2))) {
                if (game->bord[i - 1][k + 1] == ' ') {
                    game->bord[i - 1][k + 1] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            if ((xi == 1) && (i == 2) && (xk == 1)) {
                if (game->bord[i - 2][k + 2] == ' ') {
                    game->bord[i - 2][k + 2] = game->botChar;
                    game->isUserTurn = 1;	break;
                }
            }
            counter++;
        }
        else if (game->bord[i][k] == game->userChar) {
            xi = i;
            xk = k;
            counter++;
        }
        k++;

        if ((i == 2) && (k == 3) && (counter > 1)) {
            if ((xi == 2) && (xk == 2)) { break; }
            if (xk == 2) { i = xi + 1; k = 0; counter = 0; }
            else {
                i = xi; k = xk + 1; counter = 0;
            }
        }

        if ((k == 3) && (i == 2)) { break; }
        if (k == 3) { i++; k = 0; }
    }

    i = 0; k = 0; counter = 0;
    while ((i != 3) && (!game->isUserTurn)) {
        if (game->bord[i][k] == ' ') { counter++; }
        k++;
        if (k == 3) { i++; k = 0; }
    }
    if ((counter == 9) && (game->bord[1][1] != game->userChar) && (!game->isUserTurn)) {
        game->bord[1][1] = game->botChar; game->isUserTurn = 1;
    }
    else if (!game->isUserTurn) {
        i = 0; k = 0; int random_number = rand() % counter + 1;
        cout << random_number;
        counter = 0;
        while (i != 3) {
            if (game->bord[i][k] == ' ') { counter++; }
            if (counter == random_number) { game->bord[i][k] = game->botChar; break; }
            k++;
            if (k == 3) { i++; k = 0; }
        }
    }
}

void userTurn(Game* game) {
    int i = 0, k = 0;
    static int first = 0;
    first++;
    cout << "Your turn:";
    if (game->isUserTurn) {
        cin >> i >> k; i--; k--;
        if ((i >= 0) && (k >= 0) && (i <= 2) && (k <= 2) && (int(game->bord[i][k]) != int(game->botChar)) && (int(game->bord[i][k]) != int(game->userChar))) {
            game->bord[i][k] = game->userChar; game->isUserTurn = 0;
        }
        else { cout << endl <<"FALSE\n"; userTurn(game); }
    }
}

bool updateGame(Game* game) {
    srand(time(0));
    int i = 0, k = 0, counterx = 0, counter0 = 0;
    while (true) {
        if (game->bord[i][k] == game->userChar) {
            counterx++;
        }
        if (game->bord[i][k] == game->botChar) {
            counter0++;
        }
        k++;
        if (counterx == 3) { game->status = USER_WIN; return true; }
        if (counter0 == 3) { game->status = BOT_WIN; return false; }
        if ((i == 2) && (k == 3)) { break; }
        if (k == 3) { i++; k = 0; counterx = 0; counter0 = 0; }
    }
    i = 0, k = 0, counterx = 0, counter0 = 0;
    while (true) {
        if (game->bord[i][k] == game->userChar) {
            counterx++;
        }
        if (game->bord[i][k] == game->botChar) {
            counter0++;
        }
        i++;
        if (counterx == 3) { game->status = USER_WIN; return true; }
        if (counter0 == 3) { game->status = BOT_WIN; return false; }
        if ((i == 3) && (k == 2)) { break; }
        if (i == 3) { k++; i = 0; counterx = 0; counter0 = 0; }
    }

    i = 0, k = 0, counterx = 0, counter0 = 0;
    while (true) {
        if (game->bord[i][k] == game->userChar) {
            counterx++;
        }
        if (game->bord[i][k] == game->botChar) {
            counter0++;
        }
        k++; i++;
        if (counterx == 3) { game->status = USER_WIN; return true; }
        if (counter0 == 3) { game->status = BOT_WIN; return false; }
        if ((i == 3) && (k == 3)) { break; }
    }
    i = 0, k = 2, counterx = 0, counter0 = 0;
    while (true) {
        if (game->bord[i][k] == game->userChar) {
            counterx++;
        }
        if (game->bord[i][k] == game->botChar) {
            counter0++;
        }
        k--; i++;
        if (counterx == 3) { game->status = USER_WIN; return true; }
        if (counter0 == 3) { game->status = BOT_WIN; return false; }
        if ((i == 3) && (k == -1)) { break; }
    }
    i = 0, k = 0;
    while (game->bord[i][k] != ' ') {
        k++;
        if ((i == 2) && (k == 3)) { game->status = NOT_WIN; return true; }
        if (k == 3) { i++; k = 0; }

    }
    if (game->isUserTurn) { userTurn(game); game->isUserTurn = false; game->status = PLAY; return false; }
    else { botTurn(game); game->isUserTurn = true; game->status = PLAY; return false; }
    game->status = PLAY;
    return false;
}
