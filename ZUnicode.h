/**
 * @file ZUnicode.h
 * @brief 本文件是关于字符串与unicode编解码的一个简洁库，包括utf8与gbk之间的转换，检查和添加utf8 bom头
 * bom 头：0xef 0xbb 0xbf
 * @author lzh
 * @date 2021-10-05
 */

#ifndef ZUNICODE_H
#define ZUNICODE_H
#include <string>
#include <cstdio>
#include <iostream>
#include "boost/locale.hpp"

///将std::string类型的字节串按照gbk编码方式解码（反序列化）成std::wstring的unicode串，
inline std::wstring gbk_decode(const std::string &str)
{
    return boost::locale::conv::to_utf<wchar_t>(str, "GBK");
}
///将std::string类型的字节串按照utf8编码方式解码（反序列化）成std::wstring的unicode串，
inline std::wstring utf8_decode(const std::string &str)
{
    return boost::locale::conv::to_utf<wchar_t>(str, "UTF-8");
}
///将std::wstring类型的gbk串编码（序列化）成std::string类型的字节串
inline std::string  gbk_encode(const std::wstring &str)
{
    return boost::locale::conv::from_utf<wchar_t>(str, "GBK");
}
///将std::wstring类型的utf8串编码（序列化）成std::string类型的字节串
inline std::string utf8_encode(const std::wstring &str)
{
    return boost::locale::conv::from_utf<wchar_t>(str, "UTF-8");
}

///检查FILE*中开头处是否有utf8 bom 头，如果有则返回true，同时将流置于bom头之后；如果没有则返回false，同时流的位置不变。
bool c_check_utf8_bom(FILE *stream);
///检查istream中开头处是否有utf8 bom 头，如果有则返回true，同时将流置于bom头之后；如果没有则返回false，同时流的位置不变。
bool check_utf8_bom(std::istream &ios_for_check);
///检查c语言以空终止的字符串开头处是否有utf8 bom 头，如果有则返回true，如果没有则返回false，不论是否有bom头都不对字符串做任何修改。
bool c_check_utf8_bom(const char *cstr_for_check);
///检查字符串开头处是否有utf8 bom 头，如果有则返回true，如果没有则返回false，不论是否有bom头都不对字符串做任何修改。
bool check_utf8_bom(const std::string &str_for_check);
///将流FILE*中的所有内容读取到缓冲str中,缓冲能存储的最大字节数为max_size
ssize_t in_to_chars(char *str, size_t max_size, FILE *stream);
///将文件中的所有内容读取到缓冲str中,缓冲能存储的最大字节数为max_size
ssize_t in_to_chars(char *str, size_t max_size, const char *path);
///将流istream中的所有内容读取到缓冲str中,缓冲能存储的最大字节数为max_size
size_t in_to_str(std::string &str_to_save, std::istream &ios_for_read);
///将路径文件中的所有内容读取到缓冲str中,缓冲能存储的最大字节数为max_size
size_t in_to_str(std::string &str_to_save, const std::string &path);
///向stream添加utf8 bom头
FILE *c_utf8_bom_add(FILE *stream);
///将str前三个字节更改为utf8 bom头
char *c_utf8_bom_add(char *str);
///向ostream添加utf8 bom头
std::ostream &utf8_bom_add(std::ostream &output);
///将str前三个字节更改为utf8 bom头
std::string &utf8_bom_add(std::string &str);


#endif // ZUNICODE_H
