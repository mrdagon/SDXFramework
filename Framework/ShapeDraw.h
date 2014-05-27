#pragma once//☀SDXFramework
#include <Multimedia/Drawing.h>

namespace SDX
{
    void Complex::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
    {
        for( auto it: shapes )
        {
            it->Draw(描画色, 透過率, 座標変換Camera);
        }
    }
        
    void Point::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
    {
        Screen::SetBlendMode(BlendMode::Alpha, 透過率);
        if (座標変換Camera)
        {
            Drawing::Pixel((int)座標変換Camera->TransX(x), (int)座標変換Camera->TransY(y), 描画色);
        }
        else
        {
            Drawing::Pixel((int)x, (int)y, 描画色);
        }
        Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
    }

    void Line::Draw(Color 描画色, int 透過率, Camera *座標変換Camera ) const
    {
        Screen::SetBlendMode(BlendMode::Alpha, 透過率);
        if( 座標変換Camera )
        {
            Drawing::Line((int)座標変換Camera->TransX(xA), (int)座標変換Camera->TransY(yA), (int)座標変換Camera->TransX(xB), (int)座標変換Camera->TransY(yB), 描画色, (int)(座標変換Camera->GetZoom()));
            Drawing::Circle((int)座標変換Camera->TransX(xA), (int)座標変換Camera->TransX(yA), (int)(thickHarf*座標変換Camera->GetZoom()), 描画色, true);
            Drawing::Circle((int)座標変換Camera->TransX(xB), (int)座標変換Camera->TransX(yB), (int)(thickHarf*座標変換Camera->GetZoom()), 描画色, true);
        }
        else
        {
            Drawing::Line((int)xA, (int)yA, (int)xB, (int)yB, 描画色, (int)thick);
            Drawing::Circle((int)xA, (int)yA, (int)thickHarf, 描画色, true);
            Drawing::Circle((int)xB, (int)yB, (int)thickHarf, 描画色, true);
        }
        Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
    }
    
    void Rect::Draw( Color 描画色 , int 透過率 , Camera *座標変換Camera ) const
    {
        Screen::SetBlendMode(BlendMode::Alpha, 透過率);
        if (座標変換Camera)
        {
            Drawing::Rect
            (
                (int)座標変換Camera->TransX(x - widthLeft),
                (int)座標変換Camera->TransY(y - heightUp),
                (int)(座標変換Camera->GetZoom() * GetW() ),
                (int)(座標変換Camera->GetZoom() * GetH() ),
                描画色 ,
                true 
            );
        }
        else
        {
            Drawing::Rect
            ( 
                (int)( x - widthLeft),
                (int)( y - heightUp),
                (int) GetW() ,
                (int) GetH() ,
                描画色 ,
                true 
            );
        }
        Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
    }

    void Circle::Draw( Color 描画色 , int 透過率 , Camera *座標変換Camera ) const
    {
        Screen::SetBlendMode(BlendMode::Alpha, 透過率);
        if( 座標変換Camera )
        {
            Drawing::Circle( (int)座標変換Camera->TransX(x) , (int)座標変換Camera->TransY(y) , (int)(radius * 座標変換Camera->GetZoom()) , 描画色 , true );
        }
        else
        {
            Drawing::Circle( (int)x , (int)y , (int)radius , 描画色 , true );
        }
        Screen::SetBlendMode(BlendMode::NoBlend, 透過率);

    }
};