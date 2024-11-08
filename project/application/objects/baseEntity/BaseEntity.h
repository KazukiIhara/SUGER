#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "collider/Collider.h"

class BaseEntity:public Collider {
public:
	BaseEntity() = default;
	~BaseEntity() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

	// 衝突時に呼ばれる関数
	virtual void OnCollision([[maybe_unused]] Collider* other) {}
	// 中心座標を取得
	virtual Vector3 GetCenterPosition()const = 0;


protected:
	// このオブジェクトのコントローラ
	Object3DController controller_;

};