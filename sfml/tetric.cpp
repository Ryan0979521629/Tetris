#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>

using namespace std;
using namespace sf;

int mian() {
    RenderWindow window(VideoMode(320, 480), "Tetris"); //�إߵ���

    while (window.isOpen()) { //��������ɰ���ƥ�
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White); //�I���զ�
        window.display();//�i��
    }
    return 0;
}