#include <bits/stdc++.h>
#include <dirent.h>
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

std::vector<std::string> sort_asc(std::vector<std::string> a, bool len)
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

void readFolder(std::string f)
{
    const std::vector<std::string> vid_formats =
    {"mp4", "wmv", "MOV", "avi"};
    const std::vector<std::string> pic_formats =
    {"png", "jpeg", "jpg"};
    std::vector<std::string> vid_names;
    std::vector<std::string> image_names;
    auto get_name =
    [&](std::string name)->std::string{
        size_t lastindex = name.find_last_of(".");
        return name.substr(0, lastindex);
    };
    auto get_prefix =
    [&](std::string name)->std::string{
        size_t lastindex = name.find_last_of(".");
        return name.substr(lastindex+1);
    };

    /**
     * return 1 -> vid
     * return 0 -> image
     * return -1 -> neither
    **/
    auto check_file =
    [&](std::string name)->int{
        for(int i = 0; i < (int) vid_formats.size(); i++){
            if (vid_formats[i] == get_prefix(name)){
                return 1;
            }
        }
        for(int i = 0; i < (int) pic_formats.size(); i++){
            if (pic_formats[i] == get_prefix(name)){
                return 0;
            }
        }
        return -1;
    };

    auto check_file_image =
    [&](std::string name1, std::string name2)->bool{
        return get_name(name1) == get_name(name2);
    };

    DIR *dir; struct dirent *diread;

    if ((dir = opendir(f.c_str())) != NULL) {
        while ((diread = readdir(dir)) != NULL) {
            if(strcmp(diread->d_name, ".") != 0 && strcmp(diread->d_name, "..") != 0 ){
                if(check_file(diread->d_name) == 1){
                    cout << "shgs \n";
                    vid_names.push_back(diread->d_name);
                }
                else if(check_file(diread->d_name) == 0){
                    image_names.push_back(diread->d_name);
                }
            }

        }
        closedir (dir);
    } else {
        cout << "opendir";

    }
    for(int i = 0; i < (int) vid_names.size(); i++){
        for(int j = 0; j < (int) image_names.size(); j++){
            if(check_file_image(vid_names[i], image_names[j])){
                cout << 
                f+vid_names[i] << "\t" << f+image_names[j] << "\n";
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    readFolder("/media/harithalsafi/DATA/Education/University/University-Year-2/User Interfaces/cw3/tomeo/videos/");


    return 0;
}
