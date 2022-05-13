#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>

using namespace std;
using namespace sf;

int mian() {
    RenderWindow window(VideoMode(320, 480), "Tetris"); //建立視窗

    while (window.isOpen()) { //視窗執行時執行事件
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White); //背景白色
        window.display();//展示
    }
    return 0;
}