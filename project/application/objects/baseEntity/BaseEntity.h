#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "collider/Collider.h"
#include "contactRecord/ContactRecord.h"

class BaseEntity:public Collider {
public:
	BaseEntity() = default;
	~BaseEntity() = default;

	// 中心座標を取得
	virtual Vector3 GetCenterPosition()override;

	// 接触履歴を削除
	void ClearContactRecord();

protected:
	// このオブジェクトのコントローラ
	Object3DController controller_;

	// 接触履歴計測クラス
	ContactRecord contactRecord_;

};