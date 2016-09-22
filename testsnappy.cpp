#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include<string.h>
// #include "spfs_communication.h"
#include "snappy.h"
using namespace std;

#define BUF_SIZE 4*1024
#define COM_FILE_NAME  "1.txt"
#define UNCOM_FILE_NAME "1.snappy"


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




int main(int arg , char **argv)
{

    if(!strcmp(argv[1],"-d"))
    {
        string instr;
   File::ReadFileToStringOrDie(UNCOM_FILE_NAME,&instr);
   string outstr;
    int w_fd=open(COM_FILE_NAME,O_WRONLY|O_CREAT);
    close(w_fd);

    snappy::Uncompress(instr.data(),instr.size(),&outstr);

    File::WriteStringToFileOrDie(outstr,COM_FILE_NAME);

    }
else
{
    string instr;
   File::ReadFileToStringOrDie(COM_FILE_NAME,&instr);
   string outstr;
    int w_fd=open(UNCOM_FILE_NAME,O_WRONLY|O_CREAT);
    close(w_fd);

    snappy::Compress(instr.data(),instr.size(),&outstr);

    File::WriteStringToFileOrDie(outstr,UNCOM_FILE_NAME);

}





return 0;
}
