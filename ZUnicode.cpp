#include "ZUnicode.h"
#include <stdexcept>
#include<fstream>
#include<iterator>

using namespace std;
bool c_check_utf8_bom(FILE *stream)
{
    if(ferror(stream))
    {
        throw std::runtime_error("The FILE stream occurs errors.");
    }
    auto start_pos = ftell(stream);
    if(fgetc(stream) == 0xef &&  fgetc(stream) == 0xbb && fgetc(stream) == 0xbf)
    {
        return true;
    }else
    {
        clearerr(stream);
        fseek(stream,start_pos,SEEK_SET);
        return false;
    }
}

bool check_utf8_bom(std::istream &ios_for_check)
{
    if (!ios_for_check.good())
    {
        throw std::runtime_error("The istream occurs errors.");
    }
    auto origin_pos = ios_for_check.tellg();
    if (ios_for_check.get() == 0xef && ios_for_check.get() == 0xbb && ios_for_check.get() == 0xbf)
    {
        return true;
    }
    else
    {
        ios_for_check.clear();
        ios_for_check.seekg(origin_pos);
        return false;
    }
}

bool c_check_utf8_bom(const char *cstr_for_check)
{
    if(strlen(cstr_for_check) < 3)
    {
        return false;
    }
    //const unsigned char *str_ptr = reinterpret_cast<const unsigned char *>(cstr_for_check);
    unsigned char str_ptr[3];
    memcpy(str_ptr, cstr_for_check, 3);
    if(*str_ptr == 0xef && *(str_ptr+1) == 0xbb && *(str_ptr+2) == 0xbf)
    {
        return true;
    }else
    {
        return false;
    }
}

bool check_utf8_bom(const std::string &str_for_check)
{
    return check_utf8_bom(str_for_check.c_str());
}

ssize_t in_to_chars(char *str, size_t max_size, FILE *stream)
{
    if(ferror(stream))
    {
        throw std::runtime_error("The FILE stream occurs errors.");
    }
    if(str == nullptr)
    {
        throw std::runtime_error("The str is NULL, not a buffer.");
    }

    int ch;
    char *pos = str;
    size_t num = 0;
    while (num < max_size && (ch = fgetc(stream)) != EOF)
    {
        *pos = ch;
        ++pos;
        ++num;
    }
    return pos - str;
}

ssize_t in_to_chars(char *str, size_t max_size, const char *path)
{
    FILE *stream;
    if((stream = fopen(path,"r") ) == 0)
    {
        throw std::runtime_error("Cannot open the stream correct.");
    }
    if(str == nullptr)
    {
        throw std::runtime_error("The str is NULL, not a buffer.");
    }

    return in_to_chars(str, max_size,stream);
}
size_t in_to_str(std::string &str_to_save, std::istream &ios_for_read)
{
    if (!ios_for_read.good())
    {
        throw std::runtime_error("The stream is invalid.");
    }
    check_utf8_bom(ios_for_read);
    str_to_save.erase();
    istreambuf_iterator<char> beg(ios_for_read), i_end;
    copy(beg,i_end,back_inserter(str_to_save));
    return str_to_save.size();
}

size_t in_to_str(std::string &str_to_save, const std::string &path)
{
    ifstream ios_for_read(path);
    return in_to_str(str_to_save,ios_for_read);
}

FILE *c_utf8_bom_add(FILE *stream)
{
    if(fputc(0xef, stream) !=  EOF &&  fputc(0xbb, stream) != EOF && fputc(0xbf, stream) != EOF)
    {
        return stream;
    }else
    {
        throw std::runtime_error("The stream output occurs error.");
    }
}

char *c_utf8_bom_add(char *str)
{

    if (str == nullptr)
    {
        throw std::runtime_error("The str is NULL, not a buffer.");
    }

    *str = 0xef;
    *(str+1) = 0xbb;
    *(str+2) = 0xbf;
    return str+3;
}

ostream &utf8_bom_add(ostream &output)
{

    if (!output.good())
    {
        throw std::runtime_error("The output stream is invalid.");
    }
    output.put('\xef');output.put('\xbb');output.put('\xbf');
    return output;
}


string &utf8_bom_add(std::string &str)
{
    str.insert(0, "\xef\xbb\xbf");
    return str;
}
