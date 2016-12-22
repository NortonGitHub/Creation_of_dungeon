
#include "DxLib.h"
#include "Main.h"
#include "MainLoop.h"

Main::Main()
{
}


Main::~Main()
{
}

//���[�v�̑�{
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(1280, 720, 32);


    if (DxLib_Init() == -1)     // �c�w���C�u��������������
    {
        return -1;          // �G���[���N�����璼���ɏI��
    }

    MainLoop main_loop;

    main_loop.GameLoop();

    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;               // �\�t�g�̏I�� 
}