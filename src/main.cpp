#include "../inc/zmake.hpp"

// enable debugging
#define DEBUG

int main(int argc, char* argv[]){
   if (argc < 2){
      ZMake::printUsage();
      return 0;
   }

   ZMake::Args userIn;
   for(int i{1}; i != argc; ++i){
      // TODO: fix this.
      ZMake::Args flag;
      ZMake::Args cmd;
      (!strncmp(argv[i], "--", 1)) ? flag.emplace_back(argv[i]) : cmd.emplace_back(argv[i]);
      for (auto& arg : flag){ userIn.emplace_back(arg); }
      for (auto& arg : cmd){ userIn.emplace_back(arg); }
   }

   for (auto& arg : userIn){
      try {
         if(ZMake::CommandHandler.find(arg) == 0){
            throw ZMake::Error("argument '" + arg + "' does not exist.");
         } else ZMake::CommandHandler[arg](userIn);
      }

      catch(ZMake::Error& e) {
         std::cerr << e.what() << '\n';
         return 1;
      }

      catch(...){
         std::cerr << "ERROR: Something went HORRIBLY wrong. IDEK what, man. That's crazy what you just did.\n";
         return 2;
      }
   }


   #ifdef DEBUG
   for (auto& arg : userIn){
      std::cout << arg << '\n';
   }
   #endif

   return 0;
}
