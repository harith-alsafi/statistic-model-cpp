#include <bits/stdc++.h>
using namespace std;
void CaseInsensitiveSort(vector<string>& strs)
{
    std::sort(
        strs.begin(),
        strs.end(),
        [](const std::string& str1, const std::string& str2){
            return std::lexicographical_compare(
                str1.begin(), str1.end(),
                str2.begin(), str2.end(),
                [](const char& char1, const char& char2) {
                    return std::tolower(char1) < std::tolower(char2);
                }
            );
        }
    );
}

std::vector<std::string> sortAsc(std::vector<std::string> a, bool len)
{
    std::vector<std::string> entries = a;
    std::sort(entries.begin(), entries.end(), [&](const std::string& a, const std::string& b) -> bool {
        for (size_t c = 0; c < a.size() and c < b.size(); c++) {
            if(!len){
                if (std::tolower(a[c]) != std::tolower(b[c])){
                    return (std::tolower(a[c]) < std::tolower(b[c]));
                }
                else{
                    return a[c] < b[c];
                }
            }
            else if (std::tolower(a[c]) != std::tolower(b[c])){
                return ((int) a[c]-48) < ((int) b[c]-48);
            }
        }
        return a.size() < b.size();
    });
    return entries;
}

std::vector<std::string> sortDes(std::vector<std::string> a, bool len)
{
    std::vector<std::string> entries = a;
    std::sort(entries.begin(), entries.end(), [&](const std::string& a, const std::string& b) -> bool {
        for (size_t c = 0; c < a.size() and c < b.size(); c++) {
            if(!len){
                if (std::tolower(a[c]) != std::tolower(b[c])){
                    return (std::tolower(a[c]) > std::tolower(b[c]));
                }
                else{
                    return a[c] > b[c];
                }
            }
            else if (std::tolower(a[c]) != std::tolower(b[c])){
                return ((int) a[c]-48) > ((int) b[c]-48);
                
            }
                
        }
        return a.size() > b.size();
    });
    return entries;
}

int main(int argc, char const *argv[])
{
    vector<string> a = {"02:40:03", "00:45:02", "00:48:07", "00:45:01"};
    // sortDes(a);
    auto b = sortAsc(a, true);
    for(int i =0; i < a.size(); i++){
        cout << b[i] << "\n";
    }
    return 0;
}
