#pragma once

class SUGER {
public:
	// 仮想デストラクタ
	virtual~SUGER() = default;
	// 初期化
	virtual void Initialize();
	// 終了
	virtual void Finalize();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest() {
		return endRequest_;
	}
public: // 公開メンバ関数
	// 実行
	void Run();
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = false;
private: // クラスのポインタ

};