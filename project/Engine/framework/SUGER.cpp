#include "SUGER.h"

void SUGER::Initialize() {
}

void SUGER::Finalize() {
}

void SUGER::Update() {
}

void SUGER::Run() {
	// 初期化
	Initialize();
	// メインループ
	while (true) {
		// 更新
		Update();

		// 終了リクエストがあったらループを抜ける;
		if (IsEndRequest()) {
			break;
		}

		// 描画
		Draw();
	}

	// 終了
	Finalize();
}

void SUGER::PreDraw() {
}

void SUGER::PostDraw() {
}
