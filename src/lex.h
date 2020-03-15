#include <vector>
#include <string>
#include <fstream>
#include "enumType.h"
#define for(b) for(int i=0;i<b;i++)

   typeToken reservadas(const std::string &test);
   std::vector<std::pair<typeToken,std::string>> nextToken(std::ifstream &arquivo); 