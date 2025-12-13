#include <cstring>
#include <iostream>
#include "../inc/parser.hpp"
#include "../inc/zmake.hpp"

// denable debugging
#define DEBUG

int main(int argc, char* argv[]){
   if (argc < 2){
      ZMake::printUsage();
      return 0;
   }

   std::vector<ZMake::UserInput> usrIn;
   for(int i{1}; i != argc; ++i){
      if(!strncmp(argv[i], "-", 1)){
         usrIn.emplace_back("flag", argv[i]);
      } else usrIn.emplace_back("cmd", argv[i]);
   }

   for(auto& arg : usrIn){
      // DEBUG: Print all arguments and types
      #ifdef DEBUG
      std::cout << "Type: " << arg.type << " Value: " << arg.value << '\n';
      #endif
   }
   return 0;
}
