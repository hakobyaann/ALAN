#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <cctype>
#include <exception>
#include <ctime>

void insert(const std::string&, int);
void load(const std::string&, int);
void modify(const std::string&, int);
void Remove(const std::string&, int);
void operation(std::string& str);
//insert
void insert_userdata(const std::string&, const std::string&, int);
void insert_taskdata(const std::string&, const std::string&, int);
void insert_projectdata(const std::string&, const std::string&, int);
//load
void load_userdata(const std::string&, const std::string&, int);
void load_taskdata(const std::string&, const std::string&, int);
void load_projectdata(const std::string&, const std::string&, int);
//modify
void modify_userdata(const std::string&, const std::string&, int);
void modify_taskdata(const std::string&, const std::string&, int);
void modify_projectdata(const std::string&, const std::string&, int);

std::map<std::string, void(*)(const std::string&, int)>M;
std::map<std::string,  void(*)(const std::string&, const std::string&, int)>F;
std::map<std::string,  void(*)(const std::string&, const std::string&, int)>L;
std::map<std::string,  void(*)(const std::string&, const std::string&, int)>U;
