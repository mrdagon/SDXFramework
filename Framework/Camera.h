//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma oncenamespace SDX
{
/** カメラの追跡方式.*/
enum class ChaseType
{
    NormalChase,//!< 普通に追跡
    Smooth,//!< 加減速しつつ追跡
    XToY,//!< 横移動してから縦移動する
    YToX,//!< 縦移動してから横移動する
    Warp,//!< 一瞬で移動する
};
    
/** 2D用に座標変換を行うカメラを表すクラス.*/
/**    \include ModelSample.h*/
class Camera
{
private:
    double x;//!< 現在の位置
    double y;
    double zoom;

    double forcusX;//!< 移動目標
    double forcusY;
    double forcusZ;

    double speed;//!< 移動速度
    double speedZ;

    double centerX;//!< 焦点位置
    double centerY;

    static Camera* cameraNow;//!< 現在アクティブなカメラ

    ChaseType chaseType;//!< 追跡方法
public:
    /** カメラの作成.*/
    /** 初期座標と拡大率を指定してカメラを初期化*/
    Camera(double 座標X , double 座標Y , double 拡大率):
        x(座標X),
        y(座標Y),
        zoom(拡大率),
        forcusX(座標X),
        forcusY(座標Y),
        forcusZ(拡大率),
        speed(1),
        speedZ(1),
        centerX(座標X),
        centerY(座標Y),
        chaseType(ChaseType::Warp)
    {};
            
    /** アクティブなカメラを取得.*/
    static Camera* Now()
    {
        return cameraNow;
    }
            
    /** カメラをアクティブにする.*/
    /** 同時にアクティブになるCameraは１つだけです*/
    void SetActive()
    {
        cameraNow = this;
    }

    /** カメラの焦点を設定.*/
    void SetCenter(double X座標 , double Y座標)
    {
        this->centerX = X座標;
        this->centerY = Y座標;
    }

    /** 焦点のX座標を取得.*/
    double GetCenterX()
    {
        return this->centerX;
    }

    /** 焦点のY座標を取得.*/
    double GetCenterY()
    {
        return this->centerY;
    }

    /** 位置と倍率を設定.*/
    void Set(double X座標 , double Y座標 ,double 拡大率)
    {
        this->x = X座標;
        this->y = Y座標;
        this->zoom = 拡大率;
    }

    /** 移動目標座標を相対移動.*/
    void MoveForcus(double X座標 ,double Y座標)
    {
        this->forcusX += X座標;
        this->forcusY += Y座標;
    }
            
    /** 移動目標座標を設定.*/
    void SetForcus(double X座標 , double Y座標)
    {
        this->forcusX = X座標;
        this->forcusY = Y座標;
    }
            
    /** 拡大目標をセット.*/
    void SetZoomForcus(double 拡大率)
    {
        this->forcusZ = 拡大率;
    }
            
    /** 追跡速度を設定.*/
    void SetSpeed(double 追跡速度)
    {
        this->speed = 追跡速度;
    }
        
    /** 拡大応答速度を設定.*/
    void SetZoomSpeed(double 拡大速度)
    {
        this->speedZ = 拡大速度;
    }
            
    /** 拡大率を取得.*/
    double GetZoom()
    {
        return this->zoom;
    }
            
    /** 追跡方法を設定.*/
    void SetChaseType(ChaseType 追跡タイプ)
    {
        chaseType = 追跡タイプ;
    }

    /** 追跡方法や速度に応じてカメラ位置の更新.*/
    void Update()
    {
        x = x/2 + forcusX/2;
        y = y/2 + forcusY/2;
        zoom = zoom/2 + forcusZ/2;
    }
            
    /** カメラの位置と拡大率に応じてX座標を変換.*/
    double TransX(double X座標変換前)
    {
        return centerX + ( X座標変換前 - this->x ) * zoom;
    }
            
    /** カメラの位置と拡大率に応じてY座標を変換.*/
    double TransY(double Y座標変換前)
    {
        return centerY + ( Y座標変換前 - this->y ) * zoom;
    }

    Point Trans(const Point &変換前座標)
    {
        return Point(centerX + ( 変換前座標.x - this->x ) * zoom , centerY + ( 変換前座標.y - this->y ) * zoom );
    }
};
}
