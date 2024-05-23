#include "DataRead.h"
#include "ResourceManager.h"
#include <vector>
#include <sstream>
#include <fstream>
std::vector<std::wstring> GetData(std::wifstream& file)
{
    std::wstring content; // ���� ������ ������ ���ڿ�

    // ���Ͽ��� �� �پ� �о ���ڿ��� �߰�
    std::wstring line;
    while (std::getline(file, line)) {
        content += line + L'\n';
    }

    std::vector<std::wstring> tokens;
    std::wistringstream iss(content);
    while (std::getline(iss, line, L'\n')) {//�켱               
        tokens.push_back(line);
    }
    return tokens;
}
void Dialog(std::wifstream& file)
{
    std::vector<std::wstring>tokens = GetData(file);

    for (int i = 0; i < tokens.size(); i++)
    {
        int current = (int)tokens[i].find(':'); //�װ��� �ε����� ã�°���?
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
        int current = (int)tokens[i].find(':'); //�װ��� �ε����� ã�°���?
        std::wstring key = tokens[i].substr(0, current); //Ű
        std::wstring value = tokens[i].substr(current+1, tokens[i].size()); //����
        std::vector<Vector3> V3Pos;     //vector3  
        std::vector<std::wstring> SPos; //string
        std::wistringstream iss(value);
        std::wstring line;
        while (std::getline(iss, line, L'/')) { // �������� �ɰ���            
        //, �� ������ ������ �־��ֱ�
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
    std::wifstream file = std::wifstream(filepath); // ���� ����
    file.imbue(std::locale("zh_CN.UTF-8"));
    if (!file.is_open()) {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
        return;
    }

    func(file);

    file.close(); // ���� �ݱ�
}

