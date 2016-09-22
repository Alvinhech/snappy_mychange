    #include <string>  
    #include <cstring>  
    using std::string;  
      
    namespace File  
    {  
      void ReadFileToStringOrDie(const char* filename, string* data);  
      
      void ReadFileToStringOrDie(const string& filename, string* data);  
      
      void WriteStringToFileOrDie(const string& str, const char* filename);  
    }  