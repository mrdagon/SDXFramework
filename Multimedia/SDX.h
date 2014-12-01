//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include <algorithm>
#include <list>
#include <iomanip>

#include <vector>
#include <thread>
#include <mutex>

/** SDXFramework共通の名前空間.*/
namespace SDX
{
	const double PAI = 3.1415926535897931;//!<
	const double DEG = PAI / 180;//!<
}

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#pragma execution_character_set("utf-8")//charの文字コードをUTF-8に変更:Windows

#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

/*
using Image:Handle = SDL_Texture*;
using Sound:Handle = Mix_Chunk*;
using Renderer:Handle = SDL_Renderer*;
using Surface:Handle = SDL_Surface*;
using Window:Handle = SDL_Window*;
using Stick:Handle = SDL_Joystick*;
using Font:Handle = TTF_Font*;
using Color:Data = SDL_Color;
*/

#ifdef __ANDROID__
#define TABLET
#elif defined(__IPHONEOS__)
#define TABLET
#endif

#ifdef __WINDOWS__
#include<xutility>
#else
#include <locale.h>
#define sprintf_s(a,b,c,d) sprintf(a,c,d) //boost::formatにしたい
#define localtime_s(a,b) a = localtime(b)
#endif