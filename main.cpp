#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std; 
using namespace sf;

class Bullet{
public:
    Sprite Shape;
    
    Bullet(Texture &Texture, Vector2f playerPosition){
        Shape.setTexture(Texture);
        Shape.setScale(1.f, 1.f);
        Shape.setPosition(playerPosition.x + playerPosition.x / 2 - 5.f, playerPosition.y - 20.f); // Ajustar la posición de la bala
    }

    void update(){
        Shape.move(0, -10);
    }
};

class Enemy{
public:
    Sprite Shape;
    
    Enemy(Texture &Texture, Vector2f position){
        Shape.setTexture(Texture);
        Shape.setScale(2.f, 2.f); // Aumentar el tamaño del enemigo
        Shape.setPosition(position);
    }

    void update(){
        Shape.move(0, 3);
    }
};

class Enemy2 {
public:
    Sprite Shape;

    Enemy2(Texture &Texture, Vector2f position) {
        Shape.setTexture(Texture);
        Shape.setScale(2.f, 2.f); // Aumentar el tamaño del enemigo
        Shape.setPosition(position);
    }

    void update() {
        Shape.move(0, 4); // Diferente velocidad para el segundo tipo de enemigo
    }
};

int main()
{   
    RenderWindow window(VideoMode(1200, 800), "Galaga");
    window.setFramerateLimit(60);
    
    Texture playerTexture, bulletTexture, enemyTexture, enemy2Texture;
    if (!playerTexture.loadFromFile("nave.png") ||
        !bulletTexture.loadFromFile("superbullet.png") ||
        !enemyTexture.loadFromFile("bluevs.png") ||
        !enemy2Texture.loadFromFile("redvs.png"))
    {
        cout << "Error al cargar las texturas" << endl;
        return 1;
    }

    Sprite player(playerTexture);
    player.setPosition(400, 500);

    vector<Bullet> bullets; 
    vector<Enemy> enemies; 
    vector<Enemy2> enemies2;

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("space.png"))
    {
        cout << "No se ha logrado cargar el fondo" << endl;
        return 1;
    }
    backgroundTexture.setRepeated(true);
    
    Sprite background(backgroundTexture);
    background.setTextureRect(IntRect(0, 0, 1200, 1200));

    int frames = 0, framesd = 0;
    
    while (window.isOpen())
    {
        frames++;
        framesd++;
        
        Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == Event::Closed)
                window.close();
        }

        Vector2f m;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
           m.x = -3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
           m.x = 3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
           m.y = -3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
           m.y = 3.5;

        if ((player.getPosition().x + m.x) > -100 && (player.getPosition().x + m.x) < 1100)
            player.move(m.x, 0);
        if ((player.getPosition().y + m.y) > 0 && (player.getPosition().y + m.y) < 670)
            player.move(0, m.y);
        m.x = 0.f;
        m.y = 0.f;

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (framesd >= 16){
                Bullet newBullet(bulletTexture, player.getPosition());
                bullets.push_back(newBullet);
                framesd = 0;
            }   
        }

        // Generar enemigos aleatorios
        if (frames % 120 == 0){
            int randomX = rand() % 1000; // Posición X aleatoria
            int randomY = -rand() % 100; // Posición Y aleatoria arriba de la pantalla
            Enemy newEnemy(enemyTexture, Vector2f(randomX, randomY));
            enemies.push_back(newEnemy);
        }

        // Generar el segundo tipo de enemigos aleatorios
        if (frames % 180 == 0){
            int randomX = rand() % 1000; // Posición X aleatoria
            int randomY = -rand() % 100; // Posición Y aleatoria arriba de la pantalla
            Enemy2 newEnemy2(enemy2Texture, Vector2f(randomX, randomY));
            enemies2.push_back(newEnemy2);
        }

        window.clear();
        window.draw(background);

        // Actualizar y dibujar balas
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->update();
            if (it->Shape.getPosition().y < 0) {
                it = bullets.erase(it);
            } else {
                window.draw(it->Shape);
                ++it;
            }
        }

        // Actualizar y dibujar enemigos
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            it->update();
            if (it->Shape.getPosition().y > 800) {
                it = enemies.erase(it);
            } else {
                window.draw(it->Shape);
                ++it;
            }
        }

        // Actualizar y dibujar el segundo tipo de enemigos
        for (auto it = enemies2.begin(); it != enemies2.end(); ) {
            it->update();
            if (it->Shape.getPosition().y > 800) {
                it = enemies2.erase(it);
            } else {
                window.draw(it->Shape);
                ++it;
            }
        }

        // Detección de colisiones
        for (auto itB = bullets.begin(); itB != bullets.end(); ) {
            bool bulletErased = false;
            for (auto itE = enemies.begin(); itE != enemies.end(); ) {
                if (itB->Shape.getGlobalBounds().intersects(itE->Shape.getGlobalBounds())) {
                    itE = enemies.erase(itE);
                    itB = bullets.erase(itB);
                    bulletErased = true;
                    break;
                } else {
                    ++itE;
                }
            }
            if (!bulletErased) {
                for (auto itE2 = enemies2.begin(); itE2 != enemies2.end(); ) {
                    if (itB->Shape.getGlobalBounds().intersects(itE2->Shape.getGlobalBounds())) {
                        itE2 = enemies2.erase(itE2);
                        itB = bullets.erase(itB);
                        bulletErased = true;
                        break;
                    } else {
                        ++itE2;
                    }
                }
            }
            if (!bulletErased) {
                ++itB;
            }
        }

        window.draw(player);
        window.display();
    }

    return 0;
}
