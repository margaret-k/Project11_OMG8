#include <fstream>
#include <iostream>
#include <string>

std::string readAll(std::string fname)
{
  std::ifstream ifs(fname);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>()));

  return content;
}

bool compareFiles(std::string fname1, std::string fname2){
    std::string s1 = readAll(fname1);
    std::string s2 = readAll(fname2);
    return s1 == s2;
}

int main(int argc, char** argv){
    if (argc > 2)
        std::cout<<compareFiles(argv[1], argv[2]);
}