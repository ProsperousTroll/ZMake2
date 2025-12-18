#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace Parser{

   struct Std{
      inline static std::vector<std::string> grammar{
         "{",
         "}",
         ";",
         "//",
         "/*",
         "*/",
      };
      inline static std::vector<std::string> keywords{
         "opt",
         "set",
         "dir",
         "proj",
      };
      inline static std::vector<std::string> arguments{};
   };

   inline std::string getPWD(){
      return std::filesystem::current_path().string();
   }

   inline std::ifstream projectFile("zmake.pdo");
   inline std::vector<std::string> parseTest(std::ifstream& input){
      char test[512];
      std::vector<std::string> read;
      while(input.is_open()){
         if (input.getline(test, 512)){
            std::cout << test << '\n';
            read.emplace_back(test);
         } else if (input.eof()){
            return read;
            break;
         } else {
            read.emplace_back("ERROR: a line failed to parse. Is it too long?\n");
            std::cout << read[0] << '\n';
            return read;
            break;
         }
      }
      read.emplace_back("ERROR: Failed to open project file.");
      std::cout << read[0] << '\n';
      return read;
   }
   
}
