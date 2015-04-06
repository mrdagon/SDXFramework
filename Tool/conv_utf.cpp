#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <Windows.h>

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	//Windows専用
	CreateDirectoryA("backup",NULL);

    for (int i = 1; i >= 0 ; ++i)
    {
        if (argv[i] == nullptr) break;

        std::string fileName = argv[i];

        std::basic_ofstream<char32_t> ofs;
        ofs.imbue(std::locale(std::locale(""), new std::codecvt_utf8<char32_t>));

        std::basic_ifstream<char32_t> ifs;
        ifs.imbue(std::locale(std::locale(""), new std::codecvt_utf8<char32_t>));

		std::string outFile = argv[i];
		int num = outFile.find_last_of('\\');
		outFile.insert(num, "\\backup");

		ofs.open( "buff" , std::ios::out);
        ifs.open( argv[i] , std::ios::in);

        char32_t wc;

        //Bom削除
        if (ifs.get() < 0x0080 )
        {
            ifs.seekg(0);
        }

        bool StringMode = false;

        while ( !ifs.eof() )
        {
            wc = ifs.get();
            if (ifs.eof()) break;

            if (wc < 0x0080)
            {
                if (wc == 0x0022)
                {
                    //文字リテラル中はそのままにする
                    if (StringMode) StringMode = false;
                    else            StringMode = true;
                }
                ofs.put(wc);
            }
            else if (wc < 0xFFFF)//3バイト
            {
                if (StringMode)
                {
                    ofs.put(wc);
                }
                else {
                    ofs.put('U');
                    ofs.put('C');
                    ofs.put('N');
                    
                    int n = wc / 16 / 16 / 16;
                    if (n < 10) ofs.put(0x30 + n);
                    else        ofs.put(0x41 + n - 10);

                    n = wc / 16 / 16 % 16;
                    if (n < 10) ofs.put(0x30 + n);
                    else        ofs.put(0x41 + n - 10);

                    n = wc / 16 % 16;
                    if (n < 10) ofs.put(0x30 + n);
                    else        ofs.put(0x41 + n - 10);

                    n = wc % 16;
                    if (n < 10) ofs.put(0x30 + n);
                    else        ofs.put(0x41 + n - 10);
                }
            }
        }

        ofs.close();
        ifs.close();

        //環境依存？
		//元ファイルをbackupフォルダに移動
        rename( fileName.c_str() , outFile.c_str() );
		rename("buff", fileName.c_str());
    }

    return 0;
}