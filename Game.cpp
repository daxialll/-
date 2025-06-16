#define NOMINMAX
#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <algorithm>

Game::Game() : p(40, 20), sc(0), t(0), over(false) {
    srand(static_cast<unsigned>(time(nullptr)));
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void Game::Run() {
    while (!over) {
        Input();
        Update();
        Render();
        Sleep(50);
    }
    system("cls");
    std::cout << "Game Over! Score: " << sc << std::endl;
}

void Game::Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': p.Move(0, -1); break;
        case 'a': p.Move(-1, 0); break;
        case 's': p.Move(0, 1); break;
        case 'd': p.Move(1, 0); break;
        case ' ': p.Shoot(); break;
        case 27: over = true; break;
        }
    }
}

void Game::Update() {
    p.Update();
    for (auto& en : e) en.Update();

    if (++t > 20) {
        Spawn();
        t = 0;
    }

    e.erase(std::remove_if(e.begin(), e.end(),
        [](const Enemy& en) { return !en.Alive() || en.Y() > 24; }), e.end());

    Check();
}

void Game::Render() {
    system("cls");
    p.Draw();
    for (auto& en : e) en.Draw();
    HUD();
}

void Game::Spawn() {
    e.emplace_back(rand() % 78, 0);
}

void Game::Check() {
    // 优化后的碰撞检测
    for (int i = 0; i < p.GetBullets().size(); i++) {
        auto& b = p.GetBullets()[i];
        for (int j = 0; j < e.size(); j++) {
            if (b.X() >= e[j].X() && b.X() <= e[j].X() + 1 &&
                b.Y() >= e[j].Y() && b.Y() <= e[j].Y() + 1) {
                e[j].Hit();
                p.RemoveBullet(i);
                if (!e[j].Alive()) sc += 10;

                break;
            }
        }
    }

    for (auto& en : e) {
        if (p.X() < en.X() + 2 && p.X() + p.W() > en.X() &&
            p.Y() < en.Y() + 2 && p.Y() + p.H() > en.Y()) {
            p.TakeDamage();
            en.Hit();
            if (!p.IsAlive()) over = true;
        }
    }
}

void Game::HUD() {
    COORD pos = { 0, 25 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Score: " << sc << " | Life: ";
    for (int i = 0; i < p.IsAlive(); i++) std::cout << "<3 ";
}