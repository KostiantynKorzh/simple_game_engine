#include <iostream>
#include <vector>
#include <conio.h>
#include <chrono>

using namespace std;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32

class GameEntity {
public:
    int mass;
    int x;
    int y;
    int vy;

    GameEntity() {
        this->y = 10;
        this->vy = -2;
    }

    GameEntity(int mass, int x, int y, int vy) : mass(mass), x(x), y(y), vy(vy) {
    }
};

vector<GameEntity> gameEntities;

string ground = "ggggggggggggggggggggggggggg";
string wall = "wwwwwwwwwwwwwwwwwwwwwwwwwww";

void calculateGravity(GameEntity &gameEntity) {
    cout << "Before: \nX: " << gameEntity.x << ", Y: " << gameEntity.y << ", VY: " << gameEntity.vy << endl;
    if (gameEntity.y == 0 && abs(gameEntity.vy) == 1) {
        gameEntity.vy = 0;
    } else if (gameEntity.y == 0) {
        gameEntity.vy = -gameEntity.vy / 2;
    }
    gameEntity.vy -= 1;
    gameEntity.y += gameEntity.vy;
    if (gameEntity.y < 0) {
        gameEntity.y = 0;
    }
    cout << "After: \nX: " << gameEntity.x << ", Y: " << gameEntity.y << ", VY: " << gameEntity.vy << endl;
}

void calculatePhysics() {
    for (int i = 0; i < gameEntities.size(); ++i) {
        calculateGravity(gameEntities[i]);
    }
}

void renderGameEntity() {
    for (int i = 20; i >= 0; --i) {
        string resultString = wall;
        for (int j = 0; j < gameEntities.size(); ++j) {
            if (i == gameEntities[j].y) {
                resultString[gameEntities[j].x - 1] = '0';
            }
        }
        if (resultString.size() != 0) {
            cout << resultString << endl;
        } else {
            cout << wall << endl;
        }
    }
    cout << ground << endl;
}

void checkForUserInput() {
    if (kbhit()) {
        char c = getch();
        switch (c) {
//        case KEY_UP:
//            break;
            case SPACE:
                for (int j = 0; j < gameEntities.size(); ++j) {
                    if (gameEntities.at(j).vy == -1 && gameEntities.at(j).y == 0) {
                        gameEntities.at(j).vy += 20;
                    }
                }
                break;
            case KEY_LEFT:
                for (int j = 0; j < gameEntities.size(); ++j) {
                    int x = gameEntities.at(j).x;
                    if (x > 1) {
                        gameEntities.at(j).x--;
                    }
                }
                break;
            case KEY_RIGHT:
                for (int j = 0; j < gameEntities.size(); ++j) {
                    int x = gameEntities.at(j).x;
                    if (x < 27) {
                        gameEntities.at(j).x++;
                    }
                }
                break;
            default:
                cout << "" << endl;
                break;
        }
    }
}

[[noreturn]] void renderAll() {
    auto time1 = std::chrono::system_clock::now().time_since_epoch().count();
    while (true) {
        checkForUserInput();
        auto time2 = std::chrono::system_clock::now().time_since_epoch().count();
        if (time2 - time1 >= 100000000) {
            system("cls");
            calculatePhysics();
            renderGameEntity();

            time1 = std::chrono::system_clock::now().time_since_epoch().count();
        }
    }
}

void init() {
    gameEntities.emplace_back(1, 2, 10, -1);
//    gameEntities.emplace_back(1, 11, 12, -3);
//    gameEntities.emplace_back(1, 2, 5, 2);
}

int main() {
    init();
    renderAll();
    return 0;
}


