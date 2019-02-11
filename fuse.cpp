#include "fuse.h"

std::vector<std::string> split(std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void CLI(){
    string input;
    do{
        printf("cli> ");
        getline(cin, input);
        identify_cmd(input);
    }while(input!="exit");

    close_disk();
}

void identify_cmd(string cmd){
    auto tokens = split(cmd, ' ');
    if(tokens[0]=="create"){
        if(tokens.size() == 3){
            create_partition((char*)tokens[1].c_str(), stoi(tokens[2])*1024*1024);
        }
    }
    if(tokens[0]=="mount"){
        if(tokens.size() == 2)
            mount((char*)tokens[1].c_str());
    }
    if(tokens[0]=="unmount"){
        if(tokens.size() == 1)
            unmount();
    }
    if(tokens[0]=="touch"){
        if(tokens.size() == 2)
            create_file((char*)tokens[1].c_str());
    }
}