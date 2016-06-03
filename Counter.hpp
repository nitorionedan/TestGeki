#pragma once


//
// �J�E���^�[���悭�g���̂ō��܂����B
// ���炩�ɁuTimer�v���Ă������O�ɂ̂ق����ǂ��B�Ȃ��Ȃ猸�Z�`��������B
//

class Counter
{
public:
	Counter();							// ���ʂ̃R���X�g���N�^�͎g�p�֎~
	Counter::Counter(const int&  max);	// �J�E���g����ő�t���[�����������ɂ���
	~Counter() {}
	void Update();						// ���ꂪ�Ă΂��x�ɃJ�E���g�_�E�����܂�
	int  Remainder(const int  divisor);	// �����ƌ��݂̃J�E���g�����������܂��Ԃ��܂��B
	int  GetNowcount();					// ���݂̃J�E���g��Ԃ��܂�
	void isCount(const bool f_count_);	// �J�E���g���邩�ǂ�����؂�ւ���
	void Reset();						// ���݂̃J�E���^�[�������l�ɖ߂��܂�
	bool isLast();						// �Ō�̃J�E���g�ɂȂ������ǂ���
	bool isEach(const int& MIN, const int& MAX); // �w��͈͓̔��ł����H

	const int  MAX_COUNT;				// �ő�J�E���g

private:
	int  counter;						// �J�E���^�[
	bool f_count;						// �J�E���g���邩�ǂ���
	bool f_wrap;						// �O�ɂȂ����㏟��Ƀ��Z�b�g���邩�ǂ���
};