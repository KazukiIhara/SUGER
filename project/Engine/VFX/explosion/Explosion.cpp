#include "Explosion.h"

#include "framework/SUGER.h"

void Explosion::Initialize() {

	// 必要なエミッターとパーティクル作成
	SUGER::CreateParticle("fire", kPlane, "circle.png");
	// fire
	fireEmitter_.Initialize(SUGER::CreateEmitter("fire"));
	fireEmitter_.SetParticle("fire");
	fireEmitter_.SetIsRepeat(false);

	fire.emitType = kRandom;
	fire.minColor = { 0.0f,0.0f,0.2f };
	fire.maxColor = { 0.0f,0.1f,1.0f };
	fire.minSize = 0.1f;
	fire.maxSize = 0.75f;
	fire.minTranslate = { -0.1f, -0.4f,0.0f };
	fire.maxTranslate = { 0.01f,0.8f,0.0f };
	fire.minVelocity = { -0.1f,0.1f,0.0f };
	fire.maxVelocity = { 0.1f,0.8f,0.0f };
	fire.minLifeTime = 0.2f;
	fire.maxLifeTime = 2.0f;
	fire.count = 100;
	fire.isRepeat = false;
	fire.frequency = 0.0f;

	fireEmitter_.SetEmitterSetting(fire);

	// fire
	fireEmitter2_.Initialize(SUGER::CreateEmitter("fire"));
	fireEmitter2_.SetParticle("fire");
	fireEmitter2_.SetIsRepeat(false);

	fire2.emitType = kRandom;
	fire2.minColor = { 0.0f,0.0f,0.2f };
	fire2.maxColor = { 0.0f,0.1f,1.0f };
	fire2.minSize = 0.07f;
	fire2.maxSize = 0.9f;
	fire2.minTranslate = { -0.23f,-0.4f,0.0f };
	fire2.maxTranslate = { 0.36f,0.35f,0.0f };
	fire2.minVelocity = { -0.1f,0.1f,0.0f };
	fire2.maxVelocity = { 0.1f,0.8f,0.0f };
	fire2.minLifeTime = 0.2f;
	fire2.maxLifeTime = 2.0f;
	fire2.count = 100;
	fire2.isRepeat = false;
	fire2.frequency = 0.0f;

	fireEmitter2_.SetEmitterSetting(fire2);

}

void Explosion::Update() {
	fireEmitter_.SetEmitterSetting(fire);
	fireEmitter2_.SetEmitterSetting(fire2);
}

void Explosion::Emit() {
	fireEmitter_.Emit();
	fireEmitter2_.Emit();

}

void ShowEmitterSettingsUI(EmitterSetting& emitterSetting) {
	if (ImGui::Begin("EmitterSettings")) {
		// 色設定
		ImGui::Text("Color");
		ImGui::ColorEdit3("Min Color", reinterpret_cast<float*>(&emitterSetting.minColor));
		ImGui::ColorEdit3("Max Color", reinterpret_cast<float*>(&emitterSetting.maxColor));

		// サイズ設定
		ImGui::Text("Size");
		ImGui::DragFloat("Min Size", &emitterSetting.minSize, 0.01f, 0.0f, 10.0f, "%.2f");
		ImGui::DragFloat("Max Size", &emitterSetting.maxSize, 0.01f, 0.0f, 10.0f, "%.2f");

		// 座標範囲設定
		ImGui::Text("Translation Range");
		ImGui::DragFloat3("Min Translate", reinterpret_cast<float*>(&emitterSetting.minTranslate), 0.01f, -10.0f, 10.0f, "%.2f");
		ImGui::DragFloat3("Max Translate", reinterpret_cast<float*>(&emitterSetting.maxTranslate), 0.01f, -10.0f, 10.0f, "%.2f");

		// 移動量設定
		ImGui::Text("Velocity Range");
		ImGui::DragFloat3("Min Velocity", reinterpret_cast<float*>(&emitterSetting.minVelocity), 0.01f, -1.0f, 1.0f, "%.2f");
		ImGui::DragFloat3("Max Velocity", reinterpret_cast<float*>(&emitterSetting.maxVelocity), 0.01f, -1.0f, 1.0f, "%.2f");

		// 生存時間設定
		ImGui::Text("Life Time");
		ImGui::DragFloat("Min Life Time", &emitterSetting.minLifeTime, 0.01f, 0.0f, 10.0f, "%.2f");
		ImGui::DragFloat("Max Life Time", &emitterSetting.maxLifeTime, 0.01f, 0.0f, 10.0f, "%.2f");

		// 発生数設定
		ImGui::Text("Particle Count");
		ImGui::DragInt("Count", reinterpret_cast<int*>(&emitterSetting.count), 1, 1, 1000);

		ImGui::End();
	}
}