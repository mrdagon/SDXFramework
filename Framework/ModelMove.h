#pragma once//☀SDXFramework
#include <SDXFrameWork.h>

namespace SDX
{
///** Modelの移動を行うクラス.*/
///**    \include ModelSample.h*/
//class ModelMove
//{
//public:
//    Model *model;
//    
//    ModelMove(Model *移動対象):
//        model(移動対象)
//    {}
//
//    /** Modelの向きに移動.*/
//    void MoveFront(double 速度)
//    {
//        model->MovePolar(速度, model->GetAngle());
//    }
//
//    /** 範囲外に出ると反転する.*/
//    void MoveBound(double 速度, double &角度, Rect &移動範囲)
//    {
//        //範囲外にいる
//        if (model->GetX() < 移動範囲.GetLeft())
//        {
//            if (角度 > PAI / 2 && 角度 < PAI * 3 / 2)
//            {
//                角度 = -PAI - 角度;
//            }
//        }
//
//        if (model->GetX() > 移動範囲.GetRight())
//        {
//            if (角度 < PAI / 2 || 角度 > PAI * 3 / 2)
//            {
//                角度 = PAI - 角度;
//            }
//        }
//        else if (model->GetY() < 移動範囲.GetTop())
//        {
//            if (角度 > PAI)
//            {
//                角度 = PAI * 2 - 角度;
//            }
//        }
//        else if (model->GetY() > 移動範囲.GetBottom())
//        {
//            if (角度 < PAI)
//            {
//                角度 = -角度;
//            }
//        }
//
//        if (角度 < 0) 角度 += PAI * 2;
//        if (角度 > PAI * 2) 角度 -= PAI * 2;
//
//        model->MovePolar(速度, 角度);
//    }
//
//    /** 目標座標まで移動.*/
//    bool MoveToPoint(double 速度, double 目標X, double 目標Y)
//    {
//        const double lx = 目標X - model->GetX();
//        const double ly = 目標Y - model->GetY();
//
//        if (lx * lx + ly * ly <= 速度 * 速度)
//        {
//            model->SetPos(目標X, 目標Y);
//            return true;
//        }
//        else{
//            const double angle = atan2(ly, lx);
//            model->MovePolar(速度, angle);
//            return false;
//        }
//    }
//
//    struct MoveCircleState
//    {
//        MoveCircleState(double 初角) :
//        angle(初角)
//        {}
//
//        double angle;
//        double preX;
//        double preY;
//        bool   isInit = false;
//    };
//
//    /** 円周上を移動.*/
//    void MoveCircle( double 角速度, MoveCircleState &状態, double 半径X, double 半径Y)
//    {
//        if (!状態.isInit)
//        {
//            状態.preX = cos(状態.angle) * 半径X;
//            状態.preY = sin(状態.angle) * 半径Y;
//        }
//        
//        状態.angle += 角速度;
//
//        const double nextX = cos(状態.angle) * 半径X;
//        const double nextY = sin(状態.angle) * 半径Y;
//
//        model->Move(nextX - 状態.preX, nextY - 状態.preY);
//
//        状態.preX = nextX;
//        状態.preY = nextY;
//    }
//
//    struct VibrateState
//    {
//        double moveX = 0;
//        double moveY = 0;
//    };
//
//    /** 範囲内でランダムに移動.*/
//    void Vibrate(VibrateState &状態, double X振幅, double Y振幅)
//    {
//        状態.moveX = Rand::Get(-X振幅, X振幅) - 状態.moveX;
//        状態.moveY = Rand::Get(-Y振幅, Y振幅) - 状態.moveY;
//        model->Move(状態.moveX, 状態.moveY);
//    }
//};
}