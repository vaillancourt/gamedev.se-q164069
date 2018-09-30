#include "pch.h"
#include <SFML/Graphics.hpp>
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
	res.x = VideoMode::getDesktopMode().width;
	res.y = VideoMode::getDesktopMode().height;

	//VIEW
	//
	View view;
	//Setting View Center
	view.setCenter(res.x / 2, res.y / 2);
	//Creating the Screen
	win.create(VideoMode(res.x, res.y), "Texture Problem", Style::Fullscreen);
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
			Bullet b1;
			b1.setPos(player.getPosition());
			b.push_back(std::make_unique<Bullet>(b1));
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
