#include "DataRead.h"
#include "ResourceManager.h"
#include <vector>
#include <sstream>
#include <fstream>

int DataRead::FileDataRead()
{
    std::wifstream file("data\\Data\\example.txt"); // ���� ����
    file.imbue(std::locale("zh_CN.UTF-8"));

    if (!file.is_open()) {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
        return 1;
    }

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

    for (int i = 0; i < tokens.size(); i++)
    {
        int current = tokens[i].find(':'); //�װ��� �ε����� ã�°���?
        std::wstring key = tokens[i].substr(0, current);
        std::wstring dialog = tokens[i].substr(current, tokens[i].size());
        resourceManager->InsertDialog(key, dialog);
    }
  
    file.close(); // ���� �ݱ�

    return 0;
}
