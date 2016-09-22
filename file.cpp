#include "file.h"  
#include <cstdio>  
#include <cstdlib>  
namespace File  
{  
  void ReadFileToStringOrDie(const char* filename, string* data)  
  {  
    FILE* fp = fopen(filename, "rb");  
    if (fp == NULL)  
    {  
      perror(filename);  
      exit(1);  
    }  
  
    data->clear();  
    while (!feof(fp))  
    {  
      char buf[4096];  
      size_t ret = fread(buf, 1, 4096, fp);  
      if (ret == 0 && ferror(fp))  
      {  
        perror("fread");  
        exit(1);  
      }  
      data->append(string(buf, ret));  
    }  
  
    fclose(fp);  
  }  
  
  void ReadFileToStringOrDie(const string& filename, string* data)  
  {  
    ReadFileToStringOrDie(filename.c_str(), data);  
  }  
  
  void WriteStringToFileOrDie(const string& str, const char* filename)  
  {  
    FILE* fp = fopen(filename, "wb");  
    if (fp == NULL)   
    {  
      perror(filename);  
      exit(1);  
    }  
  
    int ret = fwrite(str.data(), str.size(), 1, fp);  
    if (ret != 1)   
    {  
      perror("fwrite");  
      exit(1);  
    }  
  
    fclose(fp);  
  }  
  
} 