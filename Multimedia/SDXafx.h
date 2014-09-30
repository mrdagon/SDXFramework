//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
//多重定義の関係でプリコンパイル済みヘッダーにのみインクルードするヘッダー
#include <Framework/Hit.h>
#include <Framework/ShapeDraw.h>

namespace SDX
{
    Camera* Camera::cameraNow;

    std::mt19937 Rand::engine;

    const Color Color::Black(0x00,0x00,0x00);
    const Color Color::Dilver(0xc0, 0xc0, 0xc0);
    const Color Color::Gray(0x80, 0x80, 0x80);
    const Color Color::White(0xff, 0xff, 0xff);
    const Color Color::Maroon(0x80, 0x00, 0x00);
    const Color Color::Red(0xff, 0x00, 0x00);
    const Color Color::Purple(0x80, 0x00, 0x80);
    const Color Color::Fuchsia(0xff, 0x00, 0xff);
    const Color Color::Green(0x00, 0x80, 0x00);
    const Color Color::Lime(0x00, 0xff, 0x00);
    const Color Color::Olive(0x80, 0x80, 0x00);
    const Color Color::Yellow(0xff, 0xff, 0x00);
    const Color Color::Navy(0x00, 0x00, 0x80);
    const Color Color::Blue(0x00, 0x00, 0xff);
    const Color Color::Teal(0x00, 0x80, 0x80);
    const Color Color::Aqua(0x00, 0xff, 0xff);

    int Input::handle;
    Joypad Input::pad;
    Mouse Input::mouse;
    Keyboard Input::key;
    Touch Input::touch[10];
    Gesture Input::gesture;

    bool System::isEnd;
    Renderer System::defaultRenderer;

    Font Drawing::defaultFont;

    Time Time::singleton;

    int Music::nowVolume;
}