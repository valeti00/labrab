#include <iostream>
#include "Game.h"
#include <clocale>

using namespace std;

int main(){
    char igr;
    Game game;
    cout << "Enter X or 0: ";

    cin >> igr;
    while ((igr != 'X') && (igr != '0')) {
        cout << "\n Enter X or 0: ";

        cin >> igr;
    }
    game = initGame(igr);
    int i = 0;
    while (game.status == PLAY) {
        updateDisplay(game);
        updateGame(&game);
    }
    if (game.status == USER_WIN) { cout << "You Win\n"; }
    else if (game.status == BOT_WIN) cout << "You Lose\n";
    else {
        cout << "Draw\n";
    }
    cout << "If you want to continue click 1) ";
    cin >> i;
    if (i == 1) { main(); }
    return 0;

}
