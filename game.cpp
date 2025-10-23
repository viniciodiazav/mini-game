#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string>

using namespace std;

array<int, 2> randomPosition(array<int, 2> position, int gameRange) {
    srand(time(0));
    position[0] = rand() % gameRange;
    position[1] = rand() % gameRange;
    return position;
}

vector<vector<int>> initGame(vector<vector<int>> game, int gameRange) {
    for (int j = 0; j < gameRange; j++) {
        game.push_back(vector<int> {});
        for (int i = 0; i < gameRange; i++) {
            game.at(j).push_back(0);
        }
    }
    return game;
}

void printGame(vector<vector<int>> game, int gameRange) {
    for (int j = 0; j < gameRange; j++) {
        for (int i = 0; i < gameRange; i++) {
            if (game.at(j).at(i) == 0) {
                cout << "-" << " ";
            }
            if (game.at(j).at(i) == 1) {
                cout << "A" << " ";
            }
            if (game.at(j).at(i) == 2) {
                cout << "/" << " ";
            }
            // cout << game.at(j).at(i) << " ";
        }
        cout << endl;
    }
}

array<int, 2> findPosition(vector<vector<int>> game, array<int, 2> position, int gameRange) {
    int j = 0;
    bool find = false;
    while (not find && j < gameRange) {
        int i = 0;
        while (not find && i < gameRange) {
            if (game.at(j).at(i) == 1) {
                position[0] = j;
                position[1] = i;
                find = true;
            }
            i++;
        }
        j++;
    }
    return position;
}

vector<vector<int>> moveD(vector<vector<int>> game, array<int, 2> position,int gameRange) {
    if (position[1] == gameRange - 1) {
        game.at(position[0]).at(position[1]) = 0;
        game.at(position[0]).at(0) = 1;
        return game;
    }
    if (game.at(position[0]).at(position[1] + 1) == 2) {
        return game;
    }
    game.at(position[0]).at(position[1]) = 0;
    game.at(position[0]).at(position[1] + 1) = 1;
    return game;
}

vector<vector<int>> moveA(vector<vector<int>> game, array<int, 2> position,int gameRange) {
    if (position[1] == 0) {
        game.at(position[0]).at(position[1]) = 0;
        game.at(position[0]).at(gameRange - 1) = 1;
        return game;
    }
        if (game.at(position[0]).at(position[1] - 1) == 2) {
        return game;
    }
    game.at(position[0]).at(position[1]) = 0;
    game.at(position[0]).at(position[1] - 1) = 1;
    return game;
}

vector<vector<int>> moveW(vector<vector<int>> game, array<int, 2> position,int gameRange) {
    if (position[0] == 0) {
        game.at(position[0]).at(position[1]) = 0;
        game.at(gameRange - 1).at(position[1]) = 1;
        return game;
    }
    if (game.at(position[0] - 1).at(position[1]) == 2) {
        return game;
    }
    game.at(position[0]).at(position[1]) = 0;
    game.at(position[0] - 1).at(position[1]) = 1;
    return game;
}

vector<vector<int>> moveS(vector<vector<int>> game, array<int, 2> position,int gameRange) {
    if (position[0] == gameRange - 1) {
        game.at(position[0]).at(position[1]) = 0;
        game.at(0).at(position[1]) = 1;
        return game;
    }
    if (game.at(position[0] + 1).at(position[1]) == 2) {
        return game;
    }
    game.at(position[0]).at(position[1]) = 0;
    game.at(position[0] + 1).at(position[1]) = 1;
    return game;
}

vector<vector<int>> draw(vector<vector<int>> game, array<int, 2> position, char preMv, int gameRange) {
    switch (preMv) {
        case 'd':
            if (position[1] == gameRange - 1) {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0]).at(0) = 1;
            } else {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0]).at(position[1] + 1) = 1;
            }
            break;
        case 'a':
            if (position[1] == 0) {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0]).at(gameRange - 1) = 1;
            } else {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0]).at(position[1] - 1) = 1;
            }
            break;
        case 'w':
            if (position[0] == 0) {
                game.at(position[0]).at(position[1]) = 2;
                game.at(gameRange - 1).at(position[1]) = 1;
            } else {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0] - 1).at(position[1]) = 1;
            }
            break;
        case 's':
            if (position[0] == gameRange - 1) {
                game.at(position[0]).at(position[1]) = 2;
                game.at(0).at(position[1]) = 1;
            } else {
                game.at(position[0]).at(position[1]) = 2;
                game.at(position[0] + 1).at(position[1]) = 1;
            }
            break;
    }
    return game;
}

vector<vector<int>> functionality(vector<vector<int>> game, array<int, 2> position,int gameRange, char mv, char preMv) {
    switch (mv) {
        case 'd':
            game = moveD(game, position, gameRange);
            break;
        case 'a': 
            game = moveA(game, position, gameRange);
            break;
        case 'w': 
            game = moveW(game, position, gameRange);
            break;
        case 's': 
            game = moveS(game, position, gameRange);
            break;
        case ' ':
            game = draw(game, position, preMv, gameRange);
            break;
    }
    return game;
}

int main(void) {

    int gameRange = 10;
    vector<vector<int>> game {};
    array<int, 2> position {};
    char mv {}, preMv {};
    string start;

    cout << "Type \"start\" and press enter to start: ";
    cin >> start;

    if (start == "start") {

        game = initGame(game, gameRange);
        game.at(randomPosition(position, gameRange)[0]).at(randomPosition(position, gameRange)[1]) = 1;

        while (true) {
            system("cls");
            cout << "Pres 'q' to quit" << endl;
            printGame(game, gameRange);
            mv = _getch();
            preMv = (mv != ' ') ? mv : preMv;
            game = functionality(game, findPosition(game, position, gameRange), gameRange, mv, preMv);
            if (mv == 'q') {break;}
        }

    }

    return 0;
}