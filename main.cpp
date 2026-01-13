#include <Novice.h>
#include <math.h>
#include "Enemy.h"

// 2Dベクトル構造体
struct Vector2 {
	float x, y;
};

struct Player {
	Vector2 position;
	float speed;
	int isShot;
};
struct Bullet {
	Vector2 position;
	float speed;
	int isActive;
};
struct Enemys {
	Vector2 position;
	float speed;
	int isActive;
};

int Enemy::isAllAlive;

const char kWindowTitle[] = "GC1B_02_クボタ_トモユキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player player;
	player.position = { 640.0f, 360.0f };
	player.speed = 5.0f;
	player.isShot = false;

	Bullet bullet[100];
	for(int i = 0; i < 100; i++){
		bullet[i].position = { -100.0f, -100.0f };
		bullet[i].speed = 10.0f;
		bullet[i].isActive = false;
	}

	Enemy enemy1;
	enemy1.posX = 100.0f;
	enemy1.posY = 200.0f;
	enemy1.speed = 5.0f;

	Enemy enemy2;
	enemy2.posX = 200.0f;
	enemy2.posY = 400.0f;
	enemy2.speed = -5.0f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if(keys[DIK_W]){
			player.position.y -= player.speed;
		}
		if(keys[DIK_S]){
			player.position.y += player.speed;
		}
		if(keys[DIK_A]){
			player.position.x -= player.speed;
		}
		if(keys[DIK_D]){
			player.position.x += player.speed;
		}
		if (preKeys[DIK_SPACE] && !keys[DIK_SPACE]) {
			for(int i = 0; i < 100; i++){
				if(!bullet[i].isActive){
					bullet[i].position = player.position;
					bullet[i].isActive = true;
					break;
				}
			}
		}
		for(int i = 0; i < 100; i++){
			if(bullet[i].isActive){
				bullet[i].position.y -= bullet[i].speed;
				if(bullet[i].position.y < 0){
					bullet[i].isActive = false;
					bullet[i].position = { -100.0f, -100.0f };
				}
			}
		}
		//敵
		if (enemy1.isAlive) {
			enemy1.Update();
		}
		if (enemy2.isAlive) {
			enemy2.Update();
		}
		//弾と敵の当たり判定
		for(int i = 0; i < 100; i++){
			if(bullet[i].isActive){
				float dx1 = bullet[i].position.x - enemy1.posX;
				float dy1 = bullet[i].position.y - enemy1.posY;
				float distance1 = sqrtf(dx1 * dx1 + dy1 * dy1);
				if(distance1 < 15.0f){
					bullet[i].isActive = false;
					bullet[i].position = { -100.0f, -100.0f };
					enemy1.Kill();
				}
				float dx2 = bullet[i].position.x - enemy2.posX;
				float dy2 = bullet[i].position.y - enemy2.posY;
				float distance2 = sqrtf(dx2 * dx2 + dy2 * dy2);
				if(distance2 < 15.0f){
					bullet[i].isActive = false;
					bullet[i].position = { -100.0f, -100.0f };
					enemy2.Kill();
				}
			}
		}




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		for (int i = 0; i < 100; i++) {
			Novice::DrawEllipse(
				static_cast<int>(bullet[i].position.x),
				static_cast<int>(bullet[i].position.y),
				10,
				10,
				0.0f,
				WHITE,
				kFillModeSolid);
		}

		Novice::DrawEllipse(
			static_cast<int>(player.position.x),
			static_cast<int>(player.position.y),
			20,
			20,
			0.0f,
			GREEN,
			kFillModeSolid);

		if (enemy1.isAlive) {
			Novice::DrawEllipse(
				static_cast<int>(enemy1.posX),
				static_cast<int>(enemy1.posY),
				enemy1.size,
				enemy1.size,
				0.0f,
				RED,
				kFillModeSolid);
		}
		
		if (enemy2.isAlive) {
			Novice::DrawEllipse(
				static_cast<int>(enemy2.posX),
				static_cast<int>(enemy2.posY),
				enemy2.size,
				enemy2.size,
				0.0f,
				RED,
				kFillModeSolid);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
