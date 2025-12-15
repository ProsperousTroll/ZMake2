#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include "parser.hpp"
#include <cstring>
#include <iostream>

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

   // world's babiest error struct aww :pleading:
   struct Error {
      std::string error;

      std::string what(){
         return {"ERROR: " + error};
      }

      Error(std::string const& in){
         error = in;
      }
   };

   using Args = std::vector<std::string>;
   using Handler = std::function<void(Args const& arg)>;

   inline std::unordered_map<std::string, Handler> CommandHandler{
      {"--version", [](Args const& arg){ std::cout << "ZMake " << version << '\n'; }},
      {"--help", [](Args const& arg){ printUsage(); }},
      {"--parse", [](Args const& arg){ Parser::parseInput(Parser::projectFile); }},
      {"new", [](Args const& arg){
         try {
            if(arg.size() < 2){
               throw Error("Please enter project name!");
            } else if (arg.size() > 2){
               throw Error("Too many arguments! Please enter a project name only.");
            }

            std::string projectName{arg[1]};
            std::cout << "Creating new project directory named '" + projectName + "'...\n";

         }

         catch(Error& e){
            std::cerr << e.what() << '\n';
         }

         catch(...){
            std::cerr << "ERROR: Unknown crash.\n";
         }
      }},
   };
}
