#pragma once

// C++
#include <list>

#include "structs/LineStruct.h"
#include "directX/includes/ComPtr.h"

class Line {
public:
	Line() = default;
	~Line() = default;


private:
	// ラインの最大数
	static const uint32_t kNumMaxInstance = 1024;
	// ライン
	std::list<LineData3D> lines_;

};