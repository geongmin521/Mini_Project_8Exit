#include "DataRead.h"
#include "ResourceManager.h"
#include <vector>
#include <sstream>
#include <fstream>
std::vector<std::wstring> GetData(std::wifstream& file)
{
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
    return tokens;
}
void Dialog(std::wifstream& file)
{
    std::vector<std::wstring>tokens = GetData(file);

    for (int i = 0; i < tokens.size(); i++)
    {
        int current = (int)tokens[i].find(':'); //그곳의 인덱스를 찾는거지?
        std::wstring key = tokens[i].substr(0, current);
        std::wstring dialog = tokens[i].substr(current+1, tokens[i].size());
        resourceManager->InsertDialog(key, dialog);
    }
}

void Mapdata(std::wifstream& file)
{
    std::vector<std::wstring>tokens = GetData(file);

    for (int i = 0; i < tokens.size(); i++)
    {
        int current = (int)tokens[i].find(':'); //그곳의 인덱스를 찾는거지?
        std::wstring key = tokens[i].substr(0, current); //키
        std::wstring value = tokens[i].substr(current+1, tokens[i].size()); //벨류
        std::vector<Vector3> V3Pos;     //vector3  
        std::vector<std::wstring> SPos; //string
        std::wistringstream iss(value);
        std::wstring line;
        while (std::getline(iss, line, L'/')) { // 슬래쉬로 쪼개기            
        //, 를 제외한 벨류를 넣어주기
            std::wistringstream point(line);
            std::wstring pos;
            Vector3 tmpPos;
            std::getline(point, pos, L',');
            tmpPos._x = std::stof(pos);
            std::getline(point, pos, L',');
            tmpPos._y = std::stof(pos);
            V3Pos.push_back(tmpPos);
        }
        resourceManager->InsertMapObjectPos(key, V3Pos);
    }
}

int DataRead::FileDataRead()
{
    DataFileOpen("data\\Data\\Dialog.txt", Dialog);
    DataFileOpen("data\\Data\\MapData.txt", Mapdata);
    return 0;
}

void DataRead::DataFileOpen(std::string filepath, void(*func)(std::wifstream& file))
{
    std::wifstream file = std::wifstream(filepath); // 파일 열기
    file.imbue(std::locale("zh_CN.UTF-8"));
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return;
    }

    func(file);

    file.close(); // 파일 닫기
}

