#include "../inc/zmake.hpp"

// enable debugging
#define DEBUG

int main(int argc, char* argv[]){
   if (argc < 2){
      ZMake::printUsage();
      return 0;
   }

   // TODO: fix this.
   ZMake::Args flag, cmd;
   for(int i{1}; i != argc; ++i){
      (!strncmp(argv[i], "--", 1)) ? flag.emplace_back(argv[i]) : cmd.emplace_back(argv[i]);
   }
   ZMake::runArgs(flag);
   ZMake::runArgs(cmd);

   return 0;
}
