//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//時間を取得したり計測する
bool SampleTime()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Time::ResetFPS();
    Time::ResetCount();

    int count = 0;

    Time::StartWatch();//処理時間の計測開始

    while (System::Update())
    {
        count++;
        Time::CheckFPS();//FramePerSecondを更新
        Drawing::String({ 10, 10 }, Color::White, { "FPS:", Time::GetFPS(), "\nNow:", Time::GetNowCount() });

        tm date;
        Time::GetDate(&date);

        Drawing::String({ 10, 100 }, Color::White, { date.tm_year + 1900, "年    ", date.tm_mon + 1, "月    ", date.tm_mday, "日" });

        Time::DrawWatch({ 10, 200 }, "処理時間:");//StartWatchかDrawWatchを呼んでからかかった時間をミリ秒で表示

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}