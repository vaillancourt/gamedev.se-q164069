#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	Texture t;
	Sprite bullet;
	Vector2f pos;
public:
	Bullet();
	~Bullet();
	void setPos(Vector2f pos);
	void update();
	Sprite getSprite();
	Vector2f getPos();
};