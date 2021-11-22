#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;


template <typename T>
class Table: public vector<vector<T>>
{
    public:
        Table();
        ~Table();

    private:
        vector<string> headers;


};