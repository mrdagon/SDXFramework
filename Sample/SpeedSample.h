//速度オブジェクトを使う
bool SampleSpeed()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    //位置と形を持った型
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.emplace_back(new Circle(0, 50, 10));
    shapes.emplace_back(new Rect(0, 150, 20, 20));
    shapes.emplace_back(new Line(0, 250, PAI / 2, 20, 5));

    //変化する数値を表す型
    std::vector<std::shared_ptr<ISpeed>> speeds;
    speeds.emplace_back(new Speed::Liner(1));//等速
    speeds.emplace_back(new Speed::Accel(0, 0.01));//加速する
    speeds.emplace_back(new Speed::Wave(2, 0.1, 0));//平均√2で進む

    while (System::Update())
    {
        for (int i = 0; i < 3; ++i)
        {
            //速度を更新する
            speeds[i]->Update();

            //図形を移動させる
            shapes[i]->MoveA(speeds[i]->Get(), 0);

            //描画する
            shapes[i]->Draw(Color::White, 255);
        }

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}