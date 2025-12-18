#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

// Stuffing all the long-winded templates and string vectors here.
namespace Templates{
   using Temp = std::vector<std::string>;

   struct File {
      std::string type, filePath;

      File(std::string const& p, std::string const& t){
         filePath = t;
         type = p;
      }
      void create(std::string& proj){
         if(this->type == "file"){
            std::cout << ">> Creating file " << this->filePath << "...\n";
            std::ofstream{proj + filePath};
         } 
         if (this->type == "dir"){
            std::cout << ">> Creating directory " << this->filePath << "...\n";
            std::filesystem::create_directories(proj + filePath);
         }
      }
   };
}
