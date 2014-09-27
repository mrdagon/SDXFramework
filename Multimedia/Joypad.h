//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Multimedia/InputEnum.h>

namespace SDX
{
/** ジョイパッドの状態を表すクラス.*/
/**    \include InputSample.h*/
class Joypad
{
private:
    PadType inputType = PadType::KeyAndPad1;
    StickHandle handle;
    Joypad(const Joypad &joypad){};
    Joypad operator =(const Joypad &joypad) = delete;
public:
    int StickX = 0;
    int StickY = 0;

    bool press[32];

    Key Down;
    Key Left;
    Key Right;
    Key Up;
    Key Button1;
    Key Button2;
    Key Button3;
    Key Button4;
    Key Button5;
    Key Button6;
    Key Button7;
    Key Button8;
    Key Button9;
    Key Button10;
    Key Button11;
    Key Button12;
    Key Button13;
    Key Button14;
    Key Button15;
    Key Button16;
    Key Button17;
    Key Button18;
    Key Button19;
    Key Button20;
    Key Button21;
    Key Button22;
    Key Button23;
    Key Button24;
    Key Button25;
    Key Button26;
    Key Button27;
    Key Button28;

    Joypad(){}

    void Open()
    {
        handle = SDL_JoystickOpen(0);
    }

    /** パッドの作成.*/
    void Make(PadType パッドタイプ)
    {
        inputType = パッドタイプ;
    }
            
    /** 状態のリセット.*/
    void Reset()
    {
        Up.Reset();
        Down.Reset();
        Left.Reset();
        Right.Reset();
        Button1.Reset();
        Button2.Reset();
        Button3.Reset();
        Button4.Reset();
        Button5.Reset();
        Button6.Reset();
        Button7.Reset();
        Button8.Reset();
        Button9.Reset();
        Button10.Reset();
        Button11.Reset();
        Button12.Reset();
        Button13.Reset();
        Button14.Reset();
        Button15.Reset();
        Button16.Reset();
        Button17.Reset();
        Button18.Reset();
        Button19.Reset();
        Button20.Reset();
        Button21.Reset();
        Button22.Reset();
        Button23.Reset();
        Button24.Reset();
        Button25.Reset();
        Button26.Reset();
        Button27.Reset();
        Button28.Reset();

        StickX = 0;
        StickY = 0;
    }
        
    /** 状態の更新.*/
    void Update()
    {
        Down.Update( press[(int)PadCode::Down]);
        Left.Update(press[(int)PadCode::Left]);
        Right.Update(press[(int)PadCode::Right]);
        Up.Update(press[(int)PadCode::Up]);
        Button1.Update(press[(int)PadCode::Button1]);
        Button2.Update(press[(int)PadCode::Button2]);
        Button3.Update(press[(int)PadCode::Button3]);
        Button4.Update(press[(int)PadCode::Button4]);
        Button5.Update(press[(int)PadCode::Button5]);
        Button6.Update(press[(int)PadCode::Button6]);
        Button7.Update(press[(int)PadCode::Button7]);
        Button8.Update(press[(int)PadCode::Button8]);
        Button9.Update(press[(int)PadCode::Button9]);
        Button10.Update(press[(int)PadCode::Button10]);
        Button11.Update(press[(int)PadCode::Button11]);
        Button12.Update(press[(int)PadCode::Button12]);
        Button13.Update(press[(int)PadCode::Button13]);
        Button14.Update(press[(int)PadCode::Button14]);
        Button15.Update(press[(int)PadCode::Button15]);
        Button16.Update(press[(int)PadCode::Button16]);
        Button17.Update(press[(int)PadCode::Button17]);
        Button18.Update(press[(int)PadCode::Button18]);
        Button19.Update(press[(int)PadCode::Button19]);
        Button20.Update(press[(int)PadCode::Button20]);
        Button21.Update(press[(int)PadCode::Button21]);
        Button22.Update(press[(int)PadCode::Button22]);
        Button23.Update(press[(int)PadCode::Button23]);
        Button24.Update(press[(int)PadCode::Button24]);
        Button25.Update(press[(int)PadCode::Button25]);
        Button26.Update(press[(int)PadCode::Button26]);
        Button27.Update(press[(int)PadCode::Button27]);
        Button28.Update(press[(int)PadCode::Button28]);
    }
            
    /** パッドタイプの取得.*/
    PadType GetInputType()
    {
        return inputType;
    }
            
    /** パッドタイプの設定.*/
    void SetInputType(PadType 入力タイプ)
    {
        inputType = 入力タイプ;
    }
      
    /** パッドを振動させる[未実装].*/
    /**    指定した強さ(0.0～1.0)で指定ミリ秒パッドを振動させる\n
        時間が-1の場合、StopVibration関数を呼ぶまで振動させる*/
    bool StartVibration(double 強さ,int 振動ミリ秒)
    {
        return false;
    }
    
    /** パッドの振動を停止する[未実装].*/
    bool StopVibration()
    {
        return false;
    }
        
    /** 接続中のパッド数を取得.*/
    static int GetCount()
    {
        return SDL_NumJoysticks();
    }
};
}