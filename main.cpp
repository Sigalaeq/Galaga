#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace sf;

class Bullet {
public:
    Sprite Shape;

    Bullet(Texture &Texture, Vector2f playerPosition) {
        Shape.setTexture(Texture);
        Shape.setScale(1.f, 1.f);
        Shape.setPosition(playerPosition.x + 96.f, playerPosition.y); // Ajustar la posición de la bala
    }

    void update() {
        Shape.move(0, -10);
    }
};

class EnemyBullet {
public:
    Sprite Shape;

    EnemyBullet(Texture &Texture, Vector2f enemyPosition) {
        Shape.setTexture(Texture);
        Shape.setScale(1.f, 1.f);
        Shape.setPosition(enemyPosition.x + 16.f, enemyPosition.y); // Ajustar la posición de la bala
    }

    void update() {
        Shape.move(0, 10); // La bala del enemigo se mueve hacia abajo
    }
};

class Enemy {
public:
    Sprite Shape;

    Enemy(Texture &Texture, Vector2f position) {
        Shape.setTexture(Texture);
        Shape.setScale(2.f, 2.f); // Aumentar el tamaño del enemigo
        Shape.setPosition(position);
    }

    void update() {
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

class Heart {
public:
    Sprite Shape;

    Heart(Texture &Texture, Vector2f position) {
        Shape.setTexture(Texture);
        Shape.setScale(1.f, 1.f);
        Shape.setPosition(position);
    }

    void update() {
        Shape.move(0, 2); // El corazón se mueve hacia abajo
    }
};

int pph(int n, int pp) {
    if (n % 180 == 0) return 180 - n / 40;
    else return pp;
}

int main() {
    int pp = 170, gg = 0;
    RenderWindow window(VideoMode(1200, 800), "Galaga");
    window.setFramerateLimit(60);

    Texture playerTexture, bulletTexture, enemyTexture, enemy2Texture, enemyBulletTexture, heartTexture;
    if (!playerTexture.loadFromFile("nave.png") ||
        !bulletTexture.loadFromFile("superbullet.png") ||
        !enemyTexture.loadFromFile("bluevs.png") ||
        !enemy2Texture.loadFromFile("redvs.png") ||
        !enemyBulletTexture.loadFromFile("balita.png") ||
        !heartTexture.loadFromFile("corazon.png")) {
        cout << "Error al cargar las texturas" << endl;
        return 1;
    }

    Sprite player(playerTexture);
    player.setPosition(400, 500);

    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<Enemy2> enemies2;
    vector<EnemyBullet> enemyBullets;
    vector<Heart> hearts;

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("space.png")) {
        cout << "No se ha logrado cargar el fondo" << endl;
        return 1;
    }
    backgroundTexture.setRepeated(true);

    Sprite background(backgroundTexture);
    background.setTextureRect(IntRect(0, 0, 1200, 1200));

    int frames = 0, framesd = 0;
    int playerHealth = 3;
    int score = 0; // Variable para la puntuación

    while (window.isOpen()) {
        frames++;
        framesd++;
        int pp = pph(frames, pp);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        Vector2f m;
        float mmm = 7;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m.x = -mmm;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m.x = mmm;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            m.y = -mmm;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            m.y = mmm;

        if ((player.getPosition().x + m.x) > -100 && (player.getPosition().x + m.x) < 1100)
            player.move(m.x, 0);
        if ((player.getPosition().y + m.y) > 0 && (player.getPosition().y + m.y) < 670)
            player.move(0, m.y);
        m.x = 0.f;
        m.y = 0.f;

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (framesd >= 13) {
                Bullet newBullet(bulletTexture, player.getPosition());
                bullets.push_back(newBullet);
                framesd = 0;
            }
        }

        // Generar enemigos aleatorios
        if (frames % (pp + 30) == 0) {
            int randomX = rand() % 1000; // Posición X aleatoria
            int randomY = -rand() % 100; // Posición Y aleatoria arriba de la pantalla
            Enemy newEnemy(enemyTexture, Vector2f(randomX, randomY));
            enemies.push_back(newEnemy);
        }

        // Generar el segundo tipo de enemigos aleatorios
        if (frames % (pp + 40) == 0) {
            int randomX = rand() % 1000; // Posición X aleatoria
            int randomY = -rand() % 100; // Posición Y aleatoria arriba de la pantalla
            Enemy2 newEnemy2(enemy2Texture, Vector2f(randomX, randomY));
            enemies2.push_back(newEnemy2);
        }

        // Los enemigos disparan balas
        if (frames % pp == 0) {
            for (auto &enemy : enemies) {
                EnemyBullet newEnemyBullet(enemyBulletTexture, enemy.Shape.getPosition());
                enemyBullets.push_back(newEnemyBullet);
            }
            for (auto &enemy2 : enemies2) {
                EnemyBullet newEnemyBullet(enemyBulletTexture, enemy2.Shape.getPosition());
                enemyBullets.push_back(newEnemyBullet);
            }
        }

        // Generar corazones cada 300 frames
        if (frames % 1000 == 0) {
            int randomX = rand() % 1000; // Posición X aleatoria
            Heart newHeart(heartTexture, Vector2f(randomX, -50)); // Posición Y aleatoria arriba de la pantalla
            hearts.push_back(newHeart);
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

        // Actualizar y dibujar balas enemigas
        for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
            it->update();
            if (it->Shape.getPosition().y > 800) {
                it = enemyBullets.erase(it);
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
                score --; // Restar puntos cuando un enemigo sale de la pantalla
                cout << "Score: " << score << endl; // Imprimir el puntaje en la consola
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
                score --; // Restar puntos cuando un enemigo sale de la pantalla
                cout << "Score: " << score << endl; // Imprimir el puntaje en la consola
            } else {
                window.draw(it->Shape);
                ++it;
            }
        }

        // Actualizar y dibujar corazones
        for (auto it = hearts.begin(); it != hearts.end(); ) {
            it->update();
            if (it->Shape.getPosition().y > 800) {
                it = hearts.erase(it);
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
                    score++; // Sumar puntos cuando un enemigo es destruido
                    cout << "Score: " << score << endl; // Imprimir el puntaje en la consola
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
                        score++; // Sumar puntos cuando un enemigo es destruido
                        cout << "Score: " << score << endl; // Imprimir el puntaje en la consola
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

        // Detección de colisiones entre balas enemigas y la punta del jugador
        if (!(gg > 0)) {
            FloatRect playerTipBounds(player.getPosition().x + 96.f, player.getPosition().y, 10.f, 10.f); // Ajuste para la punta de la nave
            for (auto itEB = enemyBullets.begin(); itEB != enemyBullets.end(); ) {
                if (itEB->Shape.getGlobalBounds().intersects(playerTipBounds)) {
                    itEB = enemyBullets.erase(itEB);
                    playerHealth--;
                    cout << "Player Health: " << playerHealth << endl; // Imprimir la salud del jugador en la consola
                    gg = 10;
                   
                } else {
                    ++itEB;
                }
            }
        } else gg--;
         if (playerHealth <= 0 || score<0 ) {
                        cout << "Game Over" << endl;
                        window.close();
                    }
        // Detección de colisiones entre el jugador y los enemigos
        for (auto itE = enemies.begin(); itE != enemies.end(); ) {
            if (itE->Shape.getGlobalBounds().intersects(player.getGlobalBounds())) {
                itE = enemies.erase(itE);
                playerHealth--;
                cout << "Player Health: " << playerHealth << endl; // Imprimir la salud del jugador en la consola
                if (playerHealth <= 0) {
                    cout << "Game Over" << endl;
                    window.close();
                }
            } else {
                ++itE;
            }
        }
        for (auto itE2 = enemies2.begin(); itE2 != enemies2.end(); ) {
            if (itE2->Shape.getGlobalBounds().intersects(player.getGlobalBounds())) {
                itE2 = enemies2.erase(itE2);
                playerHealth--;
                cout << "Player Health: " << playerHealth << endl; // Imprimir la salud del jugador en la consola
                if (playerHealth <= 0) {
                    cout << "Game Over" << endl;
                    window.close();
                }
            } else {
                ++itE2;
            }
        }

        // Detección de colisiones entre el jugador y los corazones
        for (auto itH = hearts.begin(); itH != hearts.end(); ) {
            if (itH->Shape.getGlobalBounds().intersects(player.getGlobalBounds())) {
                itH = hearts.erase(itH);
                playerHealth++;
                cout << "Player Health: " << playerHealth << endl; // Imprimir la salud del jugador en la consola
            } else {
                ++itH;
            }
        }

        // Dibujar corazones en la esquina superior
        for (int i = 0; i < playerHealth; i++) {
            Sprite heart(heartTexture);
            heart.setPosition(10.f + i * 40, 10.f);
            window.draw(heart);
        }

        window.draw(player);
        window.display();
    }

    // Imprimir el puntaje final
    cout << "Tu puntaje fue: " << score << endl;

    return 0;
}
