/*
@page HowToTiled Tiled�A�g�@�\
GUI�G�f�B�^�Ƃ���Tiled�𗘗p������@�̉���ł��B\n
Tiled�͈ȉ��������o���܂��B\n
http://www.mapeditor.org/
\n
<HR>
Tiled�ō쐬����tmx�t�@�C�����R�[�h�ɕϊ�����\�t�g�uTiledConv.exe�v�̉���ł�\n
\n
TiledConv.exe���g����tmx�t�@�C������\�[�X�R�[�h�������o���܂��B\n
\n
<B>1.tmx�t�@�C���̕ҏW</B>\n
�܂��e���v���[�g�ɏ]���āAtmx�t�@�C����ҏW���܂��B\n
������ǂނ������ƈӖ���������Ȃ��Ǝv���܂����A���ۂɎ����Ƃ���Ȃɓ���Ȃ��Ǝv���܂��B\n
�wSDXFramework/Sample/template.tmx�x�����Ȃ���ǂނƗǂ��ł��B\n
\n
<B>1.1.�I�u�W�F�N�g�N���X�̒�`<B>\n
TEMPLATE�Ƃ������O�̃I�u�W�F�N�g����C���[���쐬���܂��B\n
TEMPLATE���C���[�ɔz�u���ꂽ�l�p�`�̃p�����[�^�ɂ���āA�I�u�W�F�N�g�N���X�̃R�[�h����������܂�\n
\n
���O�ɂ̓N���X�������܂��B
��ނɂ͉摜�I�u�W�F�N�g�̏ꍇImage�A����ȊO�̏ꍇRect�Ɠ��͂��܂��B\n
�ꏊ�A�傫���A��]�͏o�͂���R�[�h�ɂ͉e����^���܂���B\n
\n
�J�X�^���v���p�e�B��ǉ����鎖�ŁA�����o�[�ϐ��ƃR�[�h�̒ǉ����s���܂��B\n
�����o�[�ϐ���ǉ��������ꍇ�́A�v���p�e�B���ɕϐ����A�v���p�e�B�̒l�Ɍ^�������ĉ������B\n
�R�[�h��ǉ��������ꍇ�́A�v���p�e�B���Ɋ֐���(�擪��~��t����)�A�v���p�e�B�̒l�ɏo�̓R�[�h����͂��ĉ������B\n
�o�̓R�[�h���Ƀ����o�[�ϐ�����ꂽ���ꍇ��@�ϐ����Ƃ��ĉ������B\n
\n
<B>1.2.�l�p�`�̔z�u<B>\n
�I�u�W�F�N�g����C���[��ǉ����A�l�p�`��z�u���܂�\n
\n
���O�ɂ̓I�u�W�F�N�g�̎��ʖ������܂��B\n
��ނɂ͐�ق�TEMPLATE���C���[��Rect�ɒ�`�����I�u�W�F�N�g�N���X�������܂��B\n
��ʏ�ŕ\���������ʒu�ɔz�u���ĉ������B\n
��]�ɂ͌��ݑΉ����Ă��Ȃ��̂ŁA��]�͂����Ȃ��ŉ�����\n
\n
�J�X�^���v���p�e�B�ɂ̓I�u�W�F�N�g�N���X�Ɠ����v���p�e�B��ǉ����A�v���p�e�B�l�̕����ɒl�����ĉ������B\n
\n
<B>1.3.�摜�̔z�u<B>\n
�^�C���Z�b�g��ǉ����܂��B\n
�^�C���Z�b�g�ɒǉ�����摜��tmx�t�@�C���̈ʒu�֌W�̓Q�[���̎��s�t�@�C���Ɖ摜�t�@�C���̈ʒu�֌W�Ɠ����ɂ��ĉ������B\n
�������C���[�Ƀ^�C����z�u���܂��B\n
\n
���O�ɂ̓I�u�W�F�N�g�̎��ʖ������܂��B\n
��ނɂ͐�ق�TEMPLATE���C���[��Image�ɒ�`�����I�u�W�F�N�g�N���X�������܂��A�ȗ������ꍇImage�Ɠ��͂����̂Ɠ����ɂȂ�܂��B\n
��ʏ�ŕ\���������ʒu�ɔz�u���ĉ������B\n
��]�ɂ͌��ݑΉ����Ă��Ȃ��̂ŁA��]�͂����Ȃ��ŉ�����\n
\n
�J�X�^���v���p�e�B�ɂ̓I�u�W�F�N�g�N���X�Ɠ����v���p�e�B��ǉ����A�v���p�e�B�l�̕����ɒl�����ĉ������B\n
\n
�ۑ�����Ə����͊����ł�\n
\n
<B>2.�R�[�h�̐���</B>\n
tmx�t�@�C������A�I�u�W�F�N�g�N���X�A�V�[���N���X�A�I�u�W�F�N�g�̗񋓌^�̃R�[�h�𐶐����܂��B\n
\n
tmx�t�@�C��������t�H���_�ɢClassTemplate.h��SceneTemplate.h��EnumTemplate.h���u���܂��B\n
(������SDXFramework/Tiled�ɒu���Ă���܂��B)\n
���̌�tmx�t�@�C����TiledConv.exe�Ƀh���b�v����ƁA�R�[�h����������܂��B\n
\n
<B>3.�������ꂽ�R�[�h�̗��p</B>\n
SDX�̃v���W�F�N�g���쐬���A���������R�[�h��main.cpp�Ɠ����ꏊ�ɒu���A�ȉ��̂悤�ȃR�[�h�����s���ĉ������B\n
\n
@code

#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

SDX::ImagePack imageS;
SDX::IFrame* frameS[10];
SDX::IFont* fontS[10];

#include "TestScene.h"

int main(int argc, char* argv[])
{
using namespace SDX;
//���O��template.tmx���R�[�h�ɕϊ���
//TestScene���̃R�[�h���쐬���Ă�����
System::Initialise("test", 640, 480);

imageS.LoadTmx("template.tmx");
fontS[0] = new Font(SystemFont::Gothic, 10);
auto frame0 = ImagePack("data/pipo-WindowBase001.png", 9, 3, 3);
auto frame1 = ImagePack("data/pipo-WindowBase004.png", 9, 3, 3);
frameS[0] = new BmpFrame(&frame0);
frameS[1] = new BmpFrame(&frame1);

TestScene scene;

while (System::Update())
{
scene.Draw();
}

return 0;
}

@endcode
\n
��������ƁA\n
\n
<B>4.���s����tmx�t�@�C����ǂݍ���</B>\n
�T���v���t�@�C�����̂܂܂��Ǝ��s����tmx�t�@�C����ҏW�A���̌�Enter�L�[�������ƃI�u�W�F�N�g�̈ʒu���X�V�����悤�ɂȂ��Ă��܂��B\n
�ǂ��Ȃ��Ă��邩��"TestScene.h"�̃R�[�h��ǂނƑ�̕�����Ǝv���܂�\n
\n
<B>5.�R�[�h�̍čX�V</B>\n
���������R�[�h������@�R�����g�ň͂܂ꂽ�������X�V����܂��B\n
\n
*/