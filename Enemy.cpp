#include <Novice.h>
#include <math.h>
#include "Enemy.h"


Enemy::Enemy(float x, float y, float speed, int radius) {
	posX_ = x;
	posY_ = y;
	speed_ = speed;
	radius_ = radius;
	isAlive_ = true;
	isAllAlive = true;
}

bool Enemy::CheckHit(const Vector2& bulletPos, float bulletRadius) const {
	float dx = bulletPos.x - posX_;
	float dy = bulletPos.y - posY_;
	float distance = sqrtf(dx * dx + dy * dy);
	
	return distance < bulletRadius + radius_;
}

bool Enemy::IsAlive() const{
	return isAlive_;
}
void Enemy::Kill() {
	if (!isAlive_) return;

	isAlive_ = false;
	isAllAlive = false;
}

void Enemy::Update() {
	posX_ += speed_;
	if (0 > posX_ - radius_ || posX_ > 1280 - radius_) {
		speed_ *= -1;
	}
	if (!isAllAlive) {
		isAlive_ = false;
	}
}

void Enemy::Draw() const {
	if (isAlive_) {
		Novice::DrawEllipse(
			static_cast<int>(posX_),
			static_cast<int>(posY_),
			radius_ * 2,
			radius_ * 2,
			0.0f,
			RED,
			kFillModeSolid);
	}
}
