#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
struct point { int x, y; }a[4], b[4];
const int px = 20;
const int py = 10;
int plane[px][py] = { 0 };
//建置方塊
int square[7][4] = {
    2,4,5,7, //閃電
    1,3,5,7, //直條
    3,5,4,7, //半十字架
    3,5,4,6, //閃電
    2,3,4,5, //方塊
    3,5,7,6, //J
    2,3,5,7  //L
};
bool over = 0;
bool boundary()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= py || a[i].y >= px) return 0;
        else if (plane[a[i].y][a[i].x]) return 0;

    return 1;
}

int main() {
    SoundBuffer buffer;
    buffer.loadFromFile("songs/sfml.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();
    RenderWindow window(VideoMode(600, 1000), "Tetris"); //建立視窗
    Texture t, t1, t2;
    srand(time(0));
    int move = 0;
    int colorN = 1;
    bool rotate = 0;
    double delay;
    double start = 0;
    int down = 0;
    int x = 1000000000000000000;
    delay = 105.375;//819/800*1000
    t.loadFromFile("img/12345678.png");
    t1.loadFromFile("img/NXXr56dh.png");
    t2.loadFromFile("img/107758580_310857190070231_5112728586985535061_n.png");
    Sprite gameover(t2);
    Sprite bg(t1);
    Sprite s(t);
    s.setTextureRect(IntRect(0, 0, 40, 40));
    Clock clock;
    int n = rand() % 7;
    for (int i = 0; i < 4; i++) {
        a[i].x = square[n][i] % 2;
        a[i].y = square[n][i] / 2;
    }
    while (window.isOpen()) { //視窗執行時執行事件
        double time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        start += time;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::EventType::KeyPressed)
                if (event.key.code == Keyboard::Up) rotate = true;
                else if (event.key.code == sf::Keyboard::Key::Left) move = -1;
                else if (event.key.code == sf::Keyboard::Key::Right) move = 1;
                else if (event.key.code == sf::Keyboard::Key::Down) down = 1;


        }
        //移動//
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += move;
        }
        if (!boundary()) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }
        //向下//
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].y += down;
        }
        if (!boundary()) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }

        //旋轉//
        if (rotate)
        {
            point p = a[1];
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!boundary()) {
                for (int i = 0; i < 4; i++) {
                    a[i] = b[i];
                }
            }
        }


        if (start > delay) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;

                start = 0;
            }

            if (!boundary()) {
                for (int i = 0; i < 4; i++) {
                    plane[b[i].y][b[i].x] = colorN;
                    colorN = 1 + rand() % 6;
                    int n = rand() % 7;
                    for (int i = 0; i < 4; i++) {
                        a[i].x = square[n][i] % 2;
                        a[i].y = square[n][i] / 2;
                    }

                }
            }
            start = 0;
        }
        int k = px - 1;
        for (int i = px - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < py; j++)
            {
                if (plane[i][j]) count++;
                plane[k][j] = plane[i][j];
            }
            if (count < py) k--;
        }
        for (int i = 0; i < 10; i++) {
            if (plane[1][i] == 1) over = 1;
        }
        down = 0;
        move = 0; rotate = 0;
        window.clear(Color::Black);
        window.draw(bg);
        for (int i = 0; i < px; i++) {
            for (int j = 0; j < py; j++) {
                if (plane[i][j] == 0) continue;
                s.setTextureRect(IntRect(colorN * 40, 0, 40, 40));
                s.setPosition(j * 40, i * 40), window.draw(s);
            }
        }

        for (int i = 0; i < 4; ++i) {
            s.setTextureRect(IntRect(colorN * 40, 0, 40, 40));
            s.setPosition(a[i].x * 40, a[i].y * 40);
            window.draw(s);
        }

        window.display();//展示
        if (over == 1) {
            break;
        }

    }

    sf::RenderWindow windows(sf::VideoMode(720, 715), "SFML works!");

    while (windows.isOpen())
    {
        sf::Event event;
        while (windows.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windows.close();
        }

        windows.clear();
        windows.draw(gameover);
        windows.display();
    }
    return 0;
}