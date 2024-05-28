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
int main()
{   
    
    
    RenderWindow window(VideoMode(1200, 800), "Galaga");
    window.setFramerateLimit(60);
    Texture PlayerTexture;
    if (!PlayerTexture.loadFromFile("nave.png"))
    {
        cout<<"Error al cargar la textura del jugador"<< endl;
        return 1;
    }
    
    Sprite Player(PlayerTexture);
    Player.setPosition(400,500);

    Texture bulletTexture;
    if (!bulletTexture.loadFromFile("superbullet.png"))
    {
        cout<<"Error al cargar la textura del proyectil" << endl;
        return 1;
    }
    
    vector<Bullet> bullets; 
    
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("space.png"))
    {
        cout<<"No se ha logrado cargar el fondo"<< endl;
        return 1;
    }
     backgroundTexture.setRepeated(true);
    
    Sprite background;
    background.setTexture(backgroundTexture);
    background.setTextureRect(IntRect(0,0,1200,1200));

        
      
    int frames =0, framesd = 0;
    
    
    while (window.isOpen())
    {
        frames++;
        framesd++;
        if(frames%60 == 0){

        }
        Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == Event::Closed)
                window.close();
        }
        Vector2f m;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
           m.x=-3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
           m.x=3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
           m.y=-3.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
           m.y=3.5;

        if((Player.getPosition().x +m.x)>-100 && (Player.getPosition().x +m.x)<1100)Player.move(m.x,0);
        if((Player.getPosition().y +m.y)>0 && (Player.getPosition().y +m.y)<670)Player.move(0,m.y);
        m.x=0.f;
        m.y=0.f;
           if (Keyboard::isKeyPressed(Keyboard::Space)) {
             if(framesd>=16){
            Bullet newBullet(bulletTexture, Player.getPosition());
            bullets.push_back(newBullet);
            framesd=0;
             }
            
        }
        window.clear();
        window.draw(background);
        for(auto &b : bullets){

            b.update();
            window.draw(b.Shape);
        }
        window.draw(Player);
        window.display();

        }

        
    

    return 0;
}