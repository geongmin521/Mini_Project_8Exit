#include "DataRead.h"
#include "ResourceManager.h"
#include <vector>
#include <sstream>
#include <fstream>

int DataRead::FileDataRead()
{
    std::wifstream file("data\\Data\\example.txt"); // 파일 열기
    file.imbue(std::locale("zh_CN.UTF-8"));

    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    std::wstring content; // 파일 내용을 저장할 문자열

    // 파일에서 한 줄씩 읽어서 문자열에 추가
    std::wstring line;
    while (std::getline(file, line)) {
        content += line + L'\n'; 
    }

    std::vector<std::wstring> tokens;
    std::wistringstream iss(content);
    while (std::getline(iss, line, L'\n')) {//우선               
        tokens.push_back(line);
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        int current = tokens[i].find(':'); //그곳의 인덱스를 찾는거지?
        std::wstring key = tokens[i].substr(0, current);
        std::wstring dialog = tokens[i].substr(current, tokens[i].size());
        resourceManager->InsertDialog(key, dialog);
    }
  
    file.close(); // 파일 닫기

    return 0;
}
