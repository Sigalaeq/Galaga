#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std; 
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(1200, 1200), "Shipwars");
    Texture Playertexture;
    if (!Playertexture.loadFromFile("nave.png"))
    {
        cout<<"Error al cargar la textura del jugador"<< endl;
        return 1;
    }
    
    Sprite player(Playertexture);
    player.setPosition(400,500);
    
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

    
      

    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == Event::Closed)
                window.close();

             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, 5);


        }

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }

    return 0;
}