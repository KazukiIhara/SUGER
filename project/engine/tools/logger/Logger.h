#pragma once

#include <string>
#include <format>

// 
// �f�o�b�O���O�\���p�N���X
// 

class Logger {
public: // �ÓI�����o�֐�
	// �f�o�b�O���O�̏o��
	static void Log(const std::string& message);
	// string�^��wstring�^�ɕϊ�����֐�
	static std::wstring ConvertString(const std::string& str);
	// wstring�^��string�^�ɕϊ�����֐�
	static std::string ConvertString(const std::wstring& str);
};