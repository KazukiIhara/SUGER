#pragma once

#include "!FixEngine/empty/empty.h"

class EmptyController {
public:
	EmptyController() = default;
	~EmptyController() = default;

private:
	// コントロールするエンプティ
	Empty* empty_ = nullptr;
};