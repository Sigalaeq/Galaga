#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std; 
using namespace sf;

class Bullet{
public:
    Sprite Shape;
    bool collision(Vector2f bulletPosition){
        return 0 ; 
    }
    void update(){
        //if (!this->collision(Shape.getPosition()))
        Shape.move(0, -10);
    }
    Bullet (Texture &Texture, Vector2f playerPosition){
        Shape.setTexture(Texture);
        Shape.setScale(1.f,1.f);
        Shape.setPosition((playerPosition.x+90.f),playerPosition.y );
    }
};

class Enemy{
public:
    Sprite Shape;
    bool collision(Vector2f enemyPosition){
        return 0 ; 
    }
    void update(){
        //if (!this->collision(Shape.getPosition()))
        Shape.move(0, 3);
    }
    Enemy(Texture &Texture, Vector2f position){
        Shape.setTexture(Texture);
        Shape.setScale(1.f, 1.f);
        Shape.setPosition(position);
    }
};

int main()
{   
    RenderWindow window(VideoMode(1200, 800), "Galaga");
    window.setFramerateLimit(60);
    
    Texture playerTexture, bulletTexture, enemyTexture, enemy2Texture;
    if (!playerTexture.loadFromFile("nave.png") ||
        !bulletTexture.loadFromFile("superbullet.png") ||
        !enemy2Texture.loadFromFile("redvs.png") ||
        !enemyTexture.loadFromFile("bluevs.png"))
    {
        cout << "Error al cargar las texturas" << endl;
        return 1;
    }

    Sprite player(playerTexture);
    player.setPosition(400, 500);

    vector<Bullet> bullets; 
    vector<Enemy> enemies; 

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

        window.clear();
        window.draw(background);
        
        // Actualizar y dibujar balas
        for(auto &b : bullets){
            b.update();
            window.draw(b.Shape);
        }

        // Actualizar y dibujar enemigos
        for(auto &e : enemies){
            e.update();
            window.draw(e.Shape);
        }

        window.draw(player);
        window.display();
    }

    return 0;
}