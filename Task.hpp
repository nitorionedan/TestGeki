#pragma once

//�^�X�N�N���X�B�����̃��W���[���͂��ׂĂ���Task�N���X���p������B
class Task
{
public:
	virtual ~Task(){}
	virtual void Initialize(){}		//�����������͎������Ȃ��Ă�����
	virtual void Finalize(){}   	//�I�������͎������Ȃ��Ă�����
	virtual void Update() = 0;	//�X�V�����͕K���p����Ŏ�������
	virtual void Draw() = 0;	//�`�揈���͕K���p����Ŏ�������
};