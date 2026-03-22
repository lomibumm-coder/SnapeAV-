#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <algorithm>

using namespace std;

// Перевод в нижний регистр для точного сравнения
string toLower(string data)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

// Загрузка списка "запрещенки"
vector<string> LoadBlacklist()
{
    vector<string> blacklist;
    ifstream file("blacklist.txt");
    string line;
    if (!file.is_open())
    {
        cout << "[!] Error: blacklist.txt not found!" << endl;
        return blacklist;
    }
    while (getline(file, line))
    {
        if (!line.empty())
        {
            // Очистка от мусорных символов (пробелы, переносы)
            line.erase(line.find_last_not_of(" \n\r\t") + 1);
            blacklist.push_back(toLower(line));
        }
    }
    return blacklist;
}

void SnapeShield()
{
    cout << "====================================" << endl;
    cout << "   SnapeAV Core v1.1 - ACTIVE      " << endl;
    cout << "   Status: Watching for Dark Arts  " << endl;
    cout << "====================================" << endl;

    while (true)
    {
        vector<string> blacklist = LoadBlacklist();
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnap != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32 pe;
            pe.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(hSnap, &pe))
            {
                do
                {
                    string procName = pe.szExeFile;
                    string lowerProc = toLower(procName);

                    // Ищем, есть ли текущий процесс в нашем черном списке
                    for (const string &forbidden : blacklist)
                    {
                        if (lowerProc == forbidden)
                        {
                            // Пробуем "убить" процесс
                            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                            if (hProcess != NULL)
                            {
                                if (TerminateProcess(hProcess, 0))
                                {
                                    cout << "[X] SnapeAV: Expelliarmus! Blocked: " << procName << endl;
                                }
                                CloseHandle(hProcess);
                            }
                            else
                            {
                                // Если не удалось открыть процесс (обычно из-за нехватки прав)
                                // cout << "[!] Cant stop " << procName << " - Need Admin rights!" << endl;
                            }
                        }
                    }
                } while (Process32Next(hSnap, &pe));
            }
            CloseHandle(hSnap);
        }
        Sleep(200); // Опрос 5 раз в секунду - баланс скорости и нагрузки на ЦП
    }
}

int main()
{
    // Устанавливаем кодировку
    setlocale(LC_ALL, "Russian");
    SetConsoleTitleA("SnapeAV Guard");

    SnapeShield();

    return 0;
}