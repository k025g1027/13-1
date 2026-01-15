#pragma once
#include "Vector2.h"

class Enemy {
protected:
	float posX_;
	float posY_;
	float speed_;
	int radius_;
	int isAlive_;


public:
	static int isAllAlive;
	Enemy(float x, float y, float speed, int radius);
	void Kill();
	void Update();
	void Draw() const;

	bool CheckHit(const Vector2& bulletPos, float bulletRadius) const;
	bool IsAlive() const;
	
};