#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

using namespace sf;

int main()
{
	//WINDOW
	//
	RenderWindow win;
	//For Storing Resolution 
	Vector2f res;
	//Getting Resolution
	res.x = 0.5* VideoMode::getDesktopMode().width;
	res.y = 0.5* VideoMode::getDesktopMode().height;

	//VIEW
	//
	View view;
	//Setting View Center
	view.setCenter(res.x / 2, res.y / 2);
	//Creating the Screen
	win.create(VideoMode(res.x, res.y), "Texture Problem", Style::Default);
	//Setting View Size
	view.setSize(res);

	//PLAYER
	//
	RectangleShape player;
	player.setSize(Vector2f(32.0f, 32.0f));
	player.setFillColor(Color::Blue);
	player.setPosition(view.getCenter());

	//BULLET
	//
	//Creating the Vector
	std::vector<std::unique_ptr<Bullet>> b;
  std::map<std::string, std::unique_ptr<Texture>> textures;

  auto load_texture = [&]( std::string texture_path, std::string texture_id ) {
      
    std::unique_ptr<Texture> new_texture = std::make_unique<Texture>();

    if ( new_texture->loadFromFile( texture_path ) )
    {
      textures[texture_id] = std::move( new_texture );
    }
    else
    {
      std::cout << "Failed to load \"" << texture_id << "\" for path \"" << texture_path << "\".\n";
    }
  };

  load_texture( "Graphics/bullet2.png", "bullet" );

	bool space = false;

	//For timing
	Clock clock;

	//Loop that will run it all
	while (win.isOpen())
	{
		//Timing
		Time dt = clock.restart();
		//Getting Float value
		float dtAsSeconds = dt.asSeconds();

		/*
		INPUT
		*/

		//Getting Key Press
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			space = true;
		}
		else
		{
			space = false;
		}

		//Closing the Window
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			win.close();
		}

		/*
		UPDATING
		*/

		if (space)
		{
      auto texture = textures.find( "bullet" );

      b.push_back(std::make_unique<Bullet>(*texture->second));
			b[b.size()-1]->setPos (player.getPosition());
		}



		for (auto& it : b)
		{
			//Keep Updating
			it->update();
		}

		//Bullet out of Screen
		for (int i = 0; i < b.size(); i++)
		{
			if (b[i]->getPos().y < 0.0f)
			{
				b.erase(b.begin() + i);
				i--;
			}
		}

		/*
		DRAWING
		*/
		win.clear();
		win.setView(view);


		win.draw(player);
		
		//Drawing Bullet
		for (auto& i : b)
		{
			win.draw(i->getSprite());
		}

		win.display();
	}
}
