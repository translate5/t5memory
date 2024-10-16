#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>
#include <fstream>
#include <map>

class Properties {
public:
    int init();
    void deinit();
    
    //checks if key exists in memory
    bool exist(const std::string& key);

    int add_key(const std::string& key, const std::string& value);
    int set_value(const std::string& key, const std::string& value);
    int set_anyway(const std::string& key, const std::string& value);
    int get_value(const std::string& key, std::string& value);

    int add_key(const std::string& key, const int value);
    int set_value(const std::string& key, const int value);
    int set_anyway(const std::string& key, const int value);
    int get_value(const std::string& key, int& value);

    bool set_write_to_file(const bool writeToFile);
private:
    int init_home_dir_prop();
    int create_properties_file();

    int update_intData_from_file(const std::string& key);
    int update_strData_from_file(const std::string& key);

    int update_intData_in_file(const std::string& key);
    int update_strData_in_file(const std::string& key);

    int read_all_data_from_file();
    int write_all_data_to_file();

    bool exist_in_map(const std::string& key);
    bool exist_int_in_map(const std::string& key);
    bool exist_string_in_map(const std::string& key);

    //check memory and if not found- try to find in file
    int exist_int(const std::string& key);
    int exist_string(const std::string& key);

    std::map<std::string, std::string>  dataStr;
    std::map<std::string, int>          dataInt;

    std::string filename_str, filename_int;
    std::fstream fs;
    bool fWriteToFile = true;
};

#endif // _PROPERTY_H_
