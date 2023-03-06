#include "config.h"
#include <map>
#include <fstream>
#include <iostream>
#include "./opentm2/core/utilities/LogWrapper.h"

int config::parse() {
    std::fstream file(filename);
    if (!file) {
        //std::cerr << "Failed to open config file\n";
        T5LOG(T5ERROR) <<":: Failed to open config file " << filename;
        return -1;
    }
    T5LOG( T5INFO) << ":: Success in opening config file " << filename;
    std::string line;
    std::string::size_type n;
    const char delim = '=';

    while (getline(file, line)) {
        n = line.find(delim);
        if (n != std::string::npos)
            data.insert({ line.substr(0, n), line.substr(n + 1, std::string::npos) });
    }

    return 0;
}
