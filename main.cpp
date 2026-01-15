#include <Novice.h>
#include <math.h>
#include "Enemy.h"
#include "Vector2.h"

struct Player {
	Vector2 position;
	float speed;
	int isShot;
};
struct Bullet {
	Vector2 position;
	float speed;
	float radius;
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
		bullet[i].radius = 10.0f;
		bullet[i].isActive = false;
	}

	Enemy enemy1(200.0f, 100.0f, 5.0f, 15);
	Enemy enemy2(200.0f, 300.0f, 7.0f, 15);

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
			//弾と敵の当たり判定
			if (enemy1.CheckHit(bullet[i].position, bullet[i].radius) && bullet[i].isActive) {
				bullet[i].isActive = false;
				bullet[i].position = { -100.0f, -100.0f };
				enemy1.Kill();
			}
			if (enemy2.CheckHit(bullet[i].position, bullet[i].radius) && bullet[i].isActive) {
				bullet[i].isActive = false;
				bullet[i].position = { -100.0f, -100.0f };
				enemy2.Kill();
			}
		}
		//敵
		enemy1.Update();
		enemy2.Update();
		




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		enemy1.Draw();
		enemy2.Draw();

		for (int i = 0; i < 100; i++) {
			Novice::DrawEllipse(
				static_cast<int>(bullet[i].position.x),
				static_cast<int>(bullet[i].position.y),
				static_cast<int>(bullet[i].radius),
				static_cast<int>(bullet[i].radius),
				0.0f,WHITE,kFillModeSolid);
		}

		Novice::DrawEllipse(
			static_cast<int>(player.position.x),
			static_cast<int>(player.position.y),
			20,
			20,
			0.0f,
			GREEN,
			kFillModeSolid);

		

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
