#include <vector>
#include <iostream>
#include <string>

namespace ZMake {
   inline std::string version{"0.0.1"};

   inline std::vector<std::string> usage{
      "ZMake " + version + " \n",
      "Usage: zmake <flag> <command> \n",
      "\n",
      "Commands: \n",
      "new : Creates a new ZMake project directory. \n",
      "init : Initializes the working directory as a ZMake project. \n",
      "build : Builds a ZMake project in a new 'build' directory. \n",
      "run : Builds a ZMake project, then runs the compiled project. \n",
      "clean : Clears the build directory. \n",
      "\n",
      "Flags: \n",
      "--help, -h : Prints this. \n",
      "--version, -v : Show the installed ZMake version. \n",
      "--parse, -p : Run a parser test on the project file. \n",
   };

   inline void printUsage(){
      for (auto& line : usage){
         std::cout << line;
      }
   }

   struct UserInput {
      std::string type;
      std::string value;

      UserInput(std::string const& t, std::string const& v){
         type = t;
         value = v;
      }
   };

   inline void runCommands(UserInput const& in){
      if(in.value == "new"){
         std::cout << "Running NEW\n";
      }
      if(in.value == "--help"){
         printUsage();
      }
   }

   inline void runFlags(UserInput const& in){
      if(in.value == "--help"){
         printUsage();
      }
   }

   enum Commands {
      NEW,
      INIT,
      BUILD,
      RUN,
      CLEAN,
   };

   enum Flags {
      VERSION,
      HELP,
      PARSE,
   };
}
