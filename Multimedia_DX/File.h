#pragma once//☀DXLIB
#include <fstream>
#include <sstream>
#include <iostream>
#include <Multimedia/System.h>

namespace SDX
{
/** ファイルの読込書込モード.*/
enum class FileMode
{
	Read,//!< 読込のみ
	Write,//!< 書込のみ
	Add,//!< 書込時、末尾に追加
	None,//!< 開かれていない
};

/** 入出力可能なテキストかバイナリファイルを表すクラス.*/
/**	\include FileSample.h*/
class File
{
private:
	std::fstream fst;
	bool canRead;
	bool canWrite;
	bool canAdd;
	bool isBinary;
	std::string fileName;
public:
	
	/** ファイル名とモードを指定して、ファイルを開く.*/
	File(const char* ファイル名 , FileMode 読み書きモード , bool バイナリファイル = false )
	{
		File::Open( ファイル名 , 読み書きモード , バイナリファイル );
    }

    ~File()
    {
        fst.close();
    }
	
	/** ファイルを開く.*/
	bool Open(const char* ファイル名 , FileMode 読み書きモード , bool バイナリファイル = false )
	{
        fileName = ファイル名;

        isBinary = バイナリファイル;
        
		switch(読み書きモード)
		{
			case FileMode::Read:
				if( isBinary )	fst.open( fileName.c_str() , std::ios::in | std::ios::binary );
				else			fst.open( fileName.c_str() , std::ios::in );
				canRead = true;
				canWrite = false;
				canAdd = false;
			break;
			case FileMode::Write:
				if( isBinary )	fst.open( fileName.c_str() , std::ios::out | std::ios::binary );
				else			fst.open( fileName.c_str() , std::ios::out );
				canWrite = true;
				canRead = false;
				canAdd = false;
			break;
			case FileMode::Add:
				if( isBinary )	fst.open( fileName.c_str() , std::ios::out | std::ios::app | std::ios::binary );
				else			fst.open( fileName.c_str() , std::ios::out | std::ios::app );
				canWrite = true;
				canAdd = true;
				canRead = false;
			break;
            case FileMode::None:
            break;
		}

		if ( fst.fail() )
		{
			canRead = false;
			canWrite = false;
			canAdd = false;
            return false;
		}

		return true;
	}

	/** ファイルを閉じる.*/
	void Close()
	{
		fst.close();
		canRead = false;
		canWrite = false;
		canAdd = false;
	}

	/** ファイルモードを取得.*/
	FileMode GetFileMode()
	{
		if( this->canAdd )  return FileMode::Add;
		if( this->canWrite) return FileMode::Write;
		if( this->canRead ) return FileMode::Read;
		return FileMode::None;
	}

	/** ファイル名を取得.*/
	const char* GetFileName()
	{				
		return this->fileName.c_str();
	}

	/** データを読み込む.*/
	/**	FileMode::Readの場合成功。\n
		読込先変数にデータを読み込む。*/
	template< class T>
	bool Read(T &読み込み先変数 )
	{
		if (canRead) fst.read((char*)&読み込み先変数 , sizeof(読み込み先変数));
		return canRead;
	}
	bool Read(std::string &読み込み先変数)
	{
		if (canRead)
		{
			int 文字数 = 0;
			fst.read((char*)&文字数, sizeof(int));
			読み込み先変数.resize(文字数);
			fst.read((char*)読み込み先変数.c_str(), 文字数);
		}
		return canWrite;
	}

	/** データを書き込む.*/
	/**	FileModeがWriteかAddの場合成功。\n
		書込元変数をファイルに書き込む。*/
	template< class T>
	bool Write(T& 書込み元変数)
	{
		if (canWrite)
		{
			fst.write((char*)&書込み元変数, sizeof(書込み元変数));
		}
		return canWrite;
	}
	bool Write(std::string &書込み元変数)
	{
		if (canWrite)
		{
			const int 文字数 = (int)書込み元変数.size();

			fst.write((char*)&文字数,sizeof(int));
			fst.write(書込み元変数.c_str(), 文字数);
		}
		return canWrite;
	}

			
	/** FileModeがReadの場合Read、WriteかAddの場合Writeを行う.*/
	template< class T>
	bool ReadWrite(T &読み書き変数 )
	{
		if( canRead )
		{
			return Read(読み書き変数);
		}else if( canWrite ){
			return Write(読み書き変数); 
		}
		return false;
	}
	
    /** ファイルを改行区切りで一括して読み込む.*/
    std::vector<std::string> GetLineS()
    {
        std::vector<std::string> lineS;

        if (canRead)
        {
            while ( !CheckEOF() )
            {
                lineS.push_back( GetLine() );
            }
        }
        return lineS;
    }

    /** 改行区切り+カンマ区切りでCSVファイルを一括読込.*/
    std::vector<std::vector<std::string>> GetCsvS()
    {
        std::vector<std::vector<std::string>> lineS;

        if (canRead)
        {
            int lineNo = 0;
            std::string buf;

            while ( !CheckEOF() )
            {
                auto str = GetLine();
                std::istringstream iss(str);
                lineS.push_back(std::vector<std::string>());

                while (std::getline(iss, buf, ','))
                {
                    lineS[lineNo].push_back(buf);
                }

                ++lineNo;
            }
        }
        return lineS;
    }

	/** ファイルの終端判定.*/
	bool CheckEOF()
	{
		return fst.eof();
	}
};
}