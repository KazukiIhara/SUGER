#include "Baroon.h"

#include "framework/SUGER.h"

void Baroon::Initialize(const std::string& name, const std::string& filePath, const EulerTransform3D& transform) {
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject(name, filePath, transform)));
}

void Baroon::Update() {

}