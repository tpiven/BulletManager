#include <chrono>
#include <thread>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "BulletManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "BulletManager");
    sf::Texture tileset;
    tileset.loadFromFile("res/tile.png");
    sf::Sprite tile(tileset);
    sf::Texture bullet;
    bullet.loadFromFile("res/bullet.png");
    sf::Sprite bullet_sprite(bullet);
    sf::Texture soldier;
    soldier.loadFromFile("res/sol.png");
    sf::Sprite soldier_sp;
    typedef std::chrono::duration<float, std::ratio<1>> duration;
    auto start = std::chrono::system_clock::now();
    std::list <Wall>  walls;
    walls.push_back(Wall(float2(5, 18), float2(15, 18)));
    walls.push_back(Wall(float2(48, 47), float2(63, 47)));
    walls.push_back(Wall(float2(2,30), float2(2, 35)));
    walls.push_back(Wall(float2(49, 15), float2(54, 15)));
    BulletManager *manager = new BulletManager(walls);
    std::thread t([&](){
        while (window.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            duration time = std::chrono::system_clock::now() - start;
            manager->Fire(float2(5, 10), float2(75, 73), 10, time.count(), 20);
        }

    });
    std::thread t2([&](){
        while (window.isOpen()){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            duration time = std::chrono::system_clock::now() - start;
            manager->Fire(float2(90, 25), //coordinates of the gun in meters
                          float2(5, 73), // coordinates of the target in meters
                          10, //speed in m/s
                          time.count(), // seconds since program execution
                          2); // bullet's lifetime in seconds
        }

    });
    std::thread t3([&](){
        while (window.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            duration time = std::chrono::system_clock::now() - start;
            manager->Fire(float2(89, 5), float2(73, 2), 10, time.count(), 12);
        }
    });
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            }
        window.clear(sf::Color(153, 221, 255));
        for (std::list <Wall>:: iterator  i = walls.begin(); i != walls.end(); i++) {
            float x = (*i).GetOne().GetX();
            float y = (*i).GetOne().GetY();
            while (x <= (*i).GetTwo().GetX() && y <= (*i).GetTwo().GetY()) {
                tile.setPosition(x * 10, y * 10); // 1 m = 10 pixels
                window.draw(tile);
                if ((*i).GetTwo().GetX() == (*i).GetOne().GetX())
                    y++;
                if ((*i).GetTwo().GetY() == (*i).GetOne().GetY())
                    x++;
            }
        }
        for (auto i = manager->GetManager().begin(); i < manager->GetManager().end(); i++) {
            bullet_sprite.setPosition((*i).GetCur_Pos().GetX() * 10,(*i).GetCur_Pos().GetY() * 10);
            window.draw(bullet_sprite);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        duration time = std::chrono::system_clock::now() - start;
        manager->Update(time.count());
    }
    t.join();
    t2.join();
    t3.join();
    delete manager;
    return 0;
}