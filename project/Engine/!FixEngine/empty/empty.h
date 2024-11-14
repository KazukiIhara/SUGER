#pragma once

// C++
#include <string>

// MyHedder
#include "worldTransform/WorldTransform.h"

class Empty {
public:
	Empty() = default;
	~Empty() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

	//
	// Setter
	//

	// 有効フラグのセット
	void SetIsActive(const bool& isActive);

	// 削除フラグのセット
	void SetIsDelete(const bool& isDelete);

	//
	// Getter
	//

	// 有効フラグのゲット
	bool GetIsActive()const;

	// 削除フラグのゲット
	bool GetIsDelete()const;

protected:
	// 名前
	std::string name_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// 有効フラグ
	bool isActive_ = true;
	// 削除フラグ
	bool isDelete_ = false;
};