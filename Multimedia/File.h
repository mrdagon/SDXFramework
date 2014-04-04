﻿#pragma once//☀SDL
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

/** Androidでの保存先.*/
enum class SaveMode
{
    Asset,
    Internal,
    External
};

/** 入出力可能なテキストかバイナリファイルを表すクラス.*/
/**    \include FileSample.h*/
class File
{
private:
    SDL_RWops *handle = nullptr;
    bool canRead;
    bool canWrite;
    bool canAdd;
    bool isBinary;
    std::string fileName;
public:
    
    /** ファイル名とモードを指定して、ファイルを開く.*/
    File(const char* ファイル名 , FileMode 読み書きモード , bool バイナリファイル = false , SaveMode Androidの保存先 = SaveMode::Asset)
    {
        File::Open( ファイル名 , 読み書きモード , バイナリファイル , Androidの保存先);
    }

    ~File()
    {
        Close();
    }
    
    /** ファイルを開く.*/
    bool Open(const char* ファイル名 , FileMode 読み書きモード , bool バイナリファイル = false , SaveMode Androidの保存先 = SaveMode::Asset )
    {

#ifdef __ANDROID__
        switch(Androidの保存先)
        {
        case SaveMode::Asset:
            fileName = ファイル名;
            break;
        case SaveMode::External:
            fileName = SDL_AndroidGetExternalStoragePath();
            fileName += ファイル名;
            break;
        case SaveMode::Internal:
            fileName = SDL_AndroidGetInternalStoragePath();
            fileName += ファイル名;
            break;
        }
#else
        fileName = ファイル名;
#endif

        isBinary = バイナリファイル;
        
        switch(読み書きモード)
        {
            case FileMode::Read:
                if (isBinary)    handle = SDL_RWFromFile( fileName.c_str() , "rb" );
                else            handle = SDL_RWFromFile(fileName.c_str(), "r");

                canRead = true;
                canWrite = false;
                canAdd = false;
            break;
            case FileMode::Write:
                if (isBinary)    handle = SDL_RWFromFile(fileName.c_str(), "wb");
                else            handle = SDL_RWFromFile(fileName.c_str(), "w");
                canWrite = true;
                canRead = false;
                canAdd = false;
            break;
            case FileMode::Add:
                if (isBinary)    handle = SDL_RWFromFile(fileName.c_str(), "ab");
                else            handle = SDL_RWFromFile(fileName.c_str(), "a");
                canWrite = true;
                canAdd = true;
                canRead = false;
            break;
            case FileMode::None:
            break;
        }

        if ( handle == nullptr )
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
        if (handle)
        {
            SDL_RWclose(handle);
            handle = nullptr;
        }
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
    /**    FileMode::Readの場合成功。\n
        読込先変数にデータを読み込む。*/
    template< class T>
    bool Read(T &読み込み先変数 )
    {
        

        if (canRead)
        {
            SDL_RWread( handle, &読み込み先変数, sizeof(読み込み先変数), 1);
        }
        return canRead;
    }
    bool Read(std::string &読み込み先変数)
    {
        if (canRead)
        {
            int 文字数 = 0;
            SDL_RWread(handle, &文字数, sizeof(int), 1);

            読み込み先変数.resize(文字数);
            SDL_RWread(handle, (char*)読み込み先変数.c_str(), 文字数 , 1);
        }
        return canWrite;
    }

    /** データを書き込む.*/
    /**    FileModeがWriteかAddの場合成功。\n
        書込元変数をファイルに書き込む。*/
    template< class T>
    bool Write(T& 書込み元変数)
    {
        if (canWrite)
        {
            SDL_RWwrite( handle , &書込み元変数 , sizeof(書込み元変数) , 1);
        }
        return canWrite;
    }
    bool Write(std::string &書込み元変数)
    {
        if (canWrite)
        {
            const int 文字数 = (int)書込み元変数.size();

            SDL_RWwrite(handle, &文字数, sizeof(int), 1);
            SDL_RWwrite(handle, 書込み元変数.c_str(), 文字数, 1);
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
            std::string all;
            unsigned int fileSize = (unsigned int)handle->size(handle);
            all.resize(fileSize);
            SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

            std::string buf;
            std::istringstream iss(all);

            while (std::getline(iss, buf, '\n'))
            {
                lineS.push_back(buf);
            }
        }
        return lineS;
    }
            
    /** カンマ区切りのCSVファイルを一括読込.*/
    std::vector<std::vector<std::string>> GetCsvS()
    {
        std::vector<std::vector<std::string>> lineS;

        if( canRead )
        {
            std::string all;
            unsigned int fileSize = (unsigned int)handle->size(handle);
            all.resize(fileSize);
            SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

            int lineNo = 0;
            std::string buf;
            std::string buf2;
            std::istringstream iss(all);

            while (std::getline(iss, buf, '\n'))
            {
                std::istringstream iss2(buf);
                lineS.push_back(std::vector<std::string>());

                while (std::getline(iss2, buf2, ','))
                {
                    lineS[lineNo].push_back(buf2);
                }
                ++lineNo;
            }
        }
        return lineS;
    }
    
    /** ファイルの終端判定.*/
    bool CheckEOF()
    {
        return (SDL_RWtell(handle) == RW_SEEK_END);
    }

};
}