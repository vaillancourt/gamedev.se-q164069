#include "pch.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{
	//Setting Texture
	if (!t.loadFromFile("Graphics/bullet.png"))
	{
		std::cout << "Bullet Texture Failed to Load\n";
	}
	else
	{
		t.loadFromFile("Graphics/bullet.png");
		bullet.setTexture(t);
	}
}

Bullet::~Bullet()
{
}

void Bullet::setPos(Vector2f pos)
{
	//Setting Position
	this->pos = pos;
	bullet.setPosition(this->pos);
}


void Bullet::update()
{
	pos = bullet.getPosition();
	
	bullet.move(0.0f, -4.0f);
	
}

Sprite Bullet::getSprite()
{
	return bullet;
}

Vector2f Bullet::getPos()
{
	return pos;
}
