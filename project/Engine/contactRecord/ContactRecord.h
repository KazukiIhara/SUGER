#pragma once
#include <vector>

#include "enum/ColliderEnum.h"

class ContactRecord {
public:	
	// 履歴追加
	void AddRecord(uint32_t number);
	// 履歴チェック
	bool CheckRecord(uint32_t number);
	// 履歴抹消
	void Clear();
private:
	// 履歴
	std::vector<uint32_t> record_;
};
