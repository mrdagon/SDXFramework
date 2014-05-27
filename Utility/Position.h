#pragma once//☀SDXFramework

namespace SDX
{
    /*点.*/
    template<class Type>
    struct Pos
    {
        Pos(Type X,Type Y):
            X(X),
            Y(Y)
        {}

        Type X;
        Type Y;   
    };

    /*四角形.*/
    template<class Type>
    struct Box
    {
        Box(Type X,Type Y,Type W,Type H):
            X(X),
            Y(Y),
            W(W),
            H(H)
        {}

        Type X;
        Type Y;
        Type W;
        Type H;
    };



}