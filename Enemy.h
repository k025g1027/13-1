#pragma once

class Enemy {
protected:
public:
	float posX;
	float posY;
	float speed;
	int size;
	static int isAllAlive;
	int isAlive;

	Enemy() {
		posX = 0.0f;
		posY = 0.0f;
		speed = 1.0f;
		size = 20;
		isAllAlive = true;
		isAlive = true;
	}
	
	void Kill() {
		isAllAlive = false;
	}

	void Update() {
		posX += speed;
		if(posX < 0 || posX > 1280){
			speed *= -1;
		}

		if (!isAllAlive) {
			isAlive = false;
		}

	}
};