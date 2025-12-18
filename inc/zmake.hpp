#pragma once
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include "parser.hpp"
#include "templates.hpp"

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
         return {">> ERROR: " + error};
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
      {"--parse", [](Args const& arg){ Parser::parseTest(Parser::projectFile); }},
      {"build", [](Args const& arg) { system("cd build && make"); }},
      {"clean", [](Args const& arg) { system("cd build && make clean"); }},
      {"run", [](Args const& arg) { system("cd build && make run"); }},
      {"new", [](Args const& arg){
         using namespace std::filesystem;
         using FileIn = std::ifstream;
         using FileOut = std::ofstream;

         try {

            if(arg.size() < 2){
               throw Error(">> Please enter project name!");
            } else if (arg.size() > 2){
               throw Error(">> Too many arguments! Please enter a project name only. (No spaces.)");
            }

            std::string projectName{arg[1]};
            std::cout << ">> Creating new project directory named '" + projectName + "'...\n";

            std::vector<Templates::File> tree {
               {"dir", "/src"},
               {"dir", "/inc"},
               {"file", "/src/main.c"},
               {"file", "/inc/" + projectName + ".h"},
               {"file", "/zmake.pdo"},
               {"file", "/.gitignore"},
            };
            for (auto& t : tree){
               t.create(projectName);
            }

            // there must be a better way.
            system(std::string{"cd " + projectName + " && git init -q"}.c_str());
         }
         catch(Error& e){ std::cerr << e.what() << '\n'; }
         catch(...){ std::cerr << "ERROR: An unknown error has occured.\n"; }
      }},
   };
   inline void runArgs(Args const& arg){
      for (auto const& a : arg){
         try {
            if(CommandHandler.find(a) == 0){
               throw Error("Argument '" + a + "' does not exist.");
            // Band-aid fix. 'new' is the only command that requires input. 
            // TODO: Make the command vector only store one command.
            } else if (a == "new"){
               CommandHandler["new"](arg);
               break;
            } 
            else CommandHandler[a](arg);
         }
         catch(Error& e){ std::cerr << e.what() << '\n'; }
         catch(...){ std::cerr << "ERROR: An unknown error has occured.\n"; }
      }
   }
}
