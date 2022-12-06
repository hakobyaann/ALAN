#include "headers.h"

int main()
{
   std::string command = "";
   std::cout << "Command line: ";
   getline(std::cin, command);
   operation(command);

}

void operation(std::string& command)
{
    std::string word = "";
    int i = 0;
    while (command[i] == ' ')
    {
        ++i;
    }

    while (command[i] != ' ')
    {
        if (ispunct(command[i]))
        {
            throw std::invalid_argument("The given argument is ivalid!");
        }
        command[i] = tolower(command[i]);
        word += command[i];
        ++i;
    }

    if (word != "insert" && word != "load" && word != "modify" && word != "remove")
    {
        throw std::invalid_argument("The given argument is ivalid!");    
    }
    
    M["insert"] = &insert;
    M["load"] = &load;
    M["modify"] = &modify;
    M["remove"] = &Remove;
    M[word](command, i);
}

void insert(const std::string& str, int index)
{
    std::string filename = "";
    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != ' ')
    {
        filename += str[index];
        ++index;
    }

    if (filename != "user.data" && filename != "task.data" && filename != "project.data")
    {
        throw std::invalid_argument("Incorrect file name!");
    }

    F["user.data"] = &insert_userdata;
    F["task.data"] = &insert_taskdata;
    F["project.data"] = &insert_projectdata;
    F[filename](filename, str, index);

}

void load(const std::string& str, int index)
{
    std::string filename = "";
    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != ' ')
    {
        filename += str[index];
        ++index;
    }   
    L["user.data"] = &load_userdata;
    L["task.data"] = &load_taskdata;
    L["project.data"] = &load_projectdata;
    L[filename](filename, str, index);

}
void modify(const std::string& str, int index)
{
    std::string filename = "";
    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != ' ')
    {
        filename += str[index];
        ++index;
    }   
    U["user.data"] = &modify_userdata;
    U["task.data"] = &modify_taskdata;
    U["project.data"] = &modify_projectdata;
    U[filename](filename, str, index);
}

void Remove(const std::string& str, int index){}

void insert_userdata(const std::string& filename, const std::string& str, int index)
{
    std::string name = "";
    std::string age = "";
    while (str[index] != ':')
    {
        ++index;
    }
    ++index;

    while (str[index] == ' ')
    {
        ++index;
    }
    
    while (str[index] != ' ')
    {
        name += str[index];
        ++index;
    }

    while (str[index] != ':')
    {
        ++index;
    }
    ++index;

    while (index < str.size())
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            age += str[index];
            ++index;
        }
        else if (str[index] == ' ')
        {
            age += '$'; 
            break;
        }
        else
        {
            throw std::invalid_argument("An invalid age!");
        }
        
    }

    std::fstream fin(filename, std::ios::app);
    if (fin.is_open()) 
    {
        fin << name << '\n';
        fin << age << '\n';
    }   
    fin.close();
}

void insert_taskdata(const std::string& filename, const std::string& str, int index)
{
    std::string title = "";
    std::string description = "";
    while (str[index] != ':')
    {
        ++index;
    }
    ++index;

    while (str[index] == ' ')
    {
        ++index;
    }
    
    while (str[index] != ' ')
    {
        title += str[index];
        ++index;
    }

    while (str[index] != ':')
    {
        ++index;
    }
    ++index;
    
    while (index < str.size())
    {
       description += str[index];
       ++index;
    }
    
    std::fstream fin(filename, std::ios::app);
    if (fin.is_open()) 
    {
        fin << title << '\n';
        fin << description << '\n';
    }   
    fin.close();
}

void insert_projectdata(const std::string& filename, const std::string& str, int index)
{
    std::string title = "";
    std::string created_at = "";
    while (str[index] != ':')
    {
        ++index;
    }
    ++index;

    while (str[index] == ' ')
    {
        ++index;
    }
    
    while (str[index] != ' ')
    {
        title += str[index];
        ++index;
    }

    while (str[index] != ':')
    {
        ++index;
    }
    ++index;
    
    while (index < str.size())
    {
       created_at += str[index];
       ++index;
    }
    struct tm tm;
    std::string s("32/02/2013");
    if (!strptime(created_at.c_str(), "%d/%m/%Y", &tm))
    {
        std::invalid_argument("Ivalid date");
    }

    std::fstream fin(filename, std::ios::app);
    if (fin.is_open()) 
    {
        fin << title << '\n';
        fin << created_at << '\n';
    }   
    fin.close();
}

void load_userdata(const std::string& filename, const std::string& str, int index)
{

}
void load_taskdata(const std::string& filename, const std::string& str, int index){}
void load_projectdata(const std::string& filename, const std::string& str, int index){}

void modify_userdata(const std::string& filename, const std::string& str, int index)
{
    std::string name = "";
    std::string age = "";
    std::string place = "";

    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != '=' && str[index] != ' ')
    {
        place += str[index];
        ++index;
    }
    
    while (str[index] == ' ' || str[index] == '=')
    {
        ++index;
    }
    
    if (place == "name")
    {
        while (str[index] == ' ')
        {
            ++index;
        }

        while (str[index] != ' ')
        {
            name += str[index];
            ++index;
        }

        while (str[index] == ' ')
        {
            ++index;
        }
        place = "";

        while (str[index] != ' ' && str[index] != '=')
        {
            place += str[index];
            ++index;
        }

        while (str[index] == ' ' || str[index] == '=')
        {
            ++index;
        }
        
        if (place == "name")
        {
            std::string name1 = "";
            while (str[index] != ' ' && index < str.size())
            {
                name1 += str[index];
                ++index;
            }
            std::string line = "";
            std::ifstream file(filename);
            std::ofstream temp;
            temp.open("temp.txt");
            if (file.is_open())
            {
                while (getline(file, line))
                {
                    if (line  == name)
                    {
                        temp << name1 << std::endl;
                    }
                    else
                    {
                        temp << line << std::endl;
                    }
                }
                temp.close();
                file.close();
                rename("temp.txt", "user.data");
            }
        }        
        else if (place == "age")
        {
            std::string age1 = "";
            while (str[index] != ' ' && index < str.size())
            {
                age1 += str[index];
                ++index;
            }
            std::string st = "";
            std::ifstream inFile(filename);
            std::ofstream tmp("tmp.txt");
            bool flag = false;

            if (inFile.is_open())
            {
                while (getline(inFile, st))
                {
                    if (st == name)
                    {
                        tmp << name << std::endl;
                        flag = true;
                    }
                    else
                    {
                        if (flag == true)
                        {
                            tmp << age1 << std::endl;
                            flag = false;
                        }
                        else
                        {
                            tmp << st << std::endl;
                        }
                    }
                }
                tmp.close();
                inFile.close();
                rename("tmp.txt", "user.data");
            }

        }
        else
        {
            throw std::logic_error("The command is not found!");    
        }
        
    }

    else if (place == "age")
    {
        while (str[index] == ' ')
        {
            ++index;
        }

        while (str[index] != ' ')
        {
            age += str[index];
            ++index;
        }

        while (str[index] == ' ')
        {
            ++index;
        }
        place = "";

        while (str[index] != ' ' && str[index] != '=')
        {
            place += str[index];
            ++index;
        }

        while (str[index] == ' ' || str[index] == '=')
        {
            ++index;
        }
            if (place == "age")
            {
                std::string age2 = "";
                while (str[index] != ' ' && index < str.size())
                {
                    age2 += str[index];
                    ++index;
                }
                std::string lin = "";
                std::ifstream file(filename);
                std::ofstream temp;
                temp.open("temp.txt");
                if (file.is_open())
                {
                    while (getline(file, lin))
                    {
                        if (lin  == age)
                        {
                            temp << age2 << std::endl;
                        }
                        else
                        {
                            temp << lin << std::endl;
                        }
                    }
                    temp.close();
                    file.close();
                    rename("temp.txt", "user.data");
                }
            }
            else if (place == "name")
            {
                std::string name2 = "";
                while (str[index] != ' ' && index < str.size())
                {
                    name2 += str[index];
                    ++index;
                }
                std::string line = "";
                std::ifstream inFile(filename);
                std::ofstream tmp("tmp.txt");
                int count = 0;
                std::vector<int>vec;
                int i = 0;

                if (inFile.is_open())
                {
                    while (getline(inFile, line))
                    {
                        ++count;
                        if (line == age)
                        {
                           vec.push_back(count - 1);

                        } 
                    }
                    inFile.close();
                    i = 0;
                    count = 0;
                
                inFile.open(filename);
                if (inFile.is_open())
                {
                    while (getline(inFile, line))
                    {
                        ++count;
                        if (count == vec[i])
                        {
                            tmp << name2 << std::endl;
                            ++i;
                        }
                        else
                        {
                            tmp << line << std::endl;
                        }
                    }
                }
                else
                {
                    throw std::logic_error("The file is closed!");
                }
                }
                tmp.close();
                inFile.close();
                rename("tmp.txt", "user.data");
        }
    }
}

void modify_taskdata(const std::string& filename, const std::string& str, int index)
{
    std::string title = "";
    std::string place = "";

    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != '=' && str[index] != ' ')
    {
        place += str[index];
        ++index;
    }
    
    while (str[index] == ' ' || str[index] == '=')
    {
        ++index;
    }
    if (place == "title")
    {
        while (str[index] == ' ')
        {
            ++index;
        }

        while (str[index] != ' ')
        {
            title += str[index];
            ++index;
        }

        while (str[index] == ' ')
        {
            ++index;
        }
        place = "";

        while (str[index] != ' ' && str[index] != '=')
        {
            place += str[index];
            ++index;
        }

        while (str[index] == ' ' || str[index] == '=')
        {
            ++index;
        }
        if (place == "title")
        {
            std::string title1 = "";
            std::string description = "";

            while (str[index] != ' ' && index < str.size())
            {
                title1 += str[index];
                ++index;
            }
            std::string line = "";
            std::ifstream file(filename);
            std::ofstream temp;
            temp.open("temp.txt");
            if (file.is_open())
            {
                while (getline(file, line))
                {
                    if (line  == title)
                    {
                        temp << title1 << std::endl;
                    }
                    else
                    {
                        temp << line << std::endl;
                    }
                }

                temp.close();
                file.close();
                rename("temp.txt", "task.data");
            } 
        }
        else if (place == "description")
        {
            std::string description1 = "";
            while (str[index] != ' ' && index < str.size())
            {
                description1 += str[index];
                ++index;
            }
            std::string st = "";
            std::ifstream inFile(filename);
            std::ofstream tmp("tmp.txt");
            bool flag = false;

            if (inFile.is_open())
            {
                while (getline(inFile, st))
                {
                    if (st == title)
                    {
                        tmp << st << std::endl;
                        flag = true;
                    }
                    else
                    {
                        if (flag == true)
                        {
                            tmp << description1 << std::endl;
                            flag = false;
                        }
                        else
                        {
                            tmp << st << std::endl;
                        }
                    }
                }
            }
            tmp.close();
            inFile.close();
            rename("tmp.txt", "task.data");
        }
              
    }
}

void modify_projectdata(const std::string& filename, const std::string& str, int index)
{
    std::string title = "";
    std::string place = "";
    std::string created_at = "";

    while (str[index] == ' ')
    {
        ++index;
    }

    while (str[index] != '=' && str[index] != ' ')
    {
        place += str[index];
        ++index;
    }
    
    while (str[index] == ' ' || str[index] == '=')
    {
        ++index;
    }
    if (place == "title")
    {
        while (str[index] == ' ')
        {
            ++index;
        }

        while (str[index] != ' ')
        {
            title += str[index];
            ++index;
        }

        while (str[index] == ' ')
        {
            ++index;
        }
        place = "";

        while (str[index] != ' ' && str[index] != '=')
        {
            place += str[index];
            ++index;
        }

        while (str[index] == ' ' || str[index] == '=')
        {
            ++index;
        }

        if (place == "title")
        {
            std::string title1 = "";
            std::string description = "";

            while (str[index] != ' ' && index < str.size())
            {
                title1 += str[index];
                ++index;
            }
            std::string line = "";
            std::ifstream file(filename);
            std::ofstream temp;
            temp.open("temp.txt");
            if (file.is_open())
            {
                while (getline(file, line))
                {
                    if (line  == title)
                    {
                        temp << title1 << std::endl;
                    }
                    else
                    {
                        temp << line << std::endl;
                    }
                }

                temp.close();
                file.close();
                rename("temp.txt", "project.data");
            } 
        }
        else if (place == "created_at")
        {
            struct tm tm;
            std::string s("32/02/2013");
            if (!strptime(created_at.c_str(), "%d/%m/%Y", &tm))
            {
                std::invalid_argument("Ivalid date");
            }

            std::fstream fin(filename, std::ios::app);
            if (fin.is_open()) 
            {
                fin << created_at << '\n';
            }   
            fin.close();
        }
    }
   
    
}