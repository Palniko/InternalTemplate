#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <Psapi.h>
#include "Defines.h"

inline FlexType PatternScanAll(std::vector<short> signature, FlexType startaddress = 0, FlexType endaddress = 0) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if (startaddress == 0) {
        startaddress = (FlexType)(si.lpMinimumApplicationAddress);
    }
    if (endaddress == 0) {
        endaddress = (FlexType)(si.lpMaximumApplicationAddress);
    }

    MEMORY_BASIC_INFORMATION mbi{ 0 };
    FlexType protectflags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

    for (FlexType i = startaddress; i < endaddress - signature.size(); i++) {
        if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi))) {
            if (mbi.Protect & protectflags || !(mbi.State & MEM_COMMIT)) {
                i += mbi.RegionSize;
                continue; // Skip unreadable regions
            }
            for (FlexType k = (FlexType)mbi.BaseAddress; k < (FlexType)mbi.BaseAddress + mbi.RegionSize - signature.size(); k++) {
                for (FlexType j = 0; j < signature.size(); j++) {
                    if (signature.at(j) != -1 && signature.at(j) != *(BYTE*)(k + j))
                        break;
                    if (j + 1 == signature.size())
                        return k;
                }
            }
            i = (FlexType)mbi.BaseAddress + mbi.RegionSize;
        }
    }
    return NULL;
}

inline FlexType PatternScanModule(const std::string& moduleName, const std::vector<short>& pattern) {
    auto comparePattern = [](BYTE* data, const std::vector<short>& pattern) -> bool {
        for (size_t i = 0; i < pattern.size(); ++i) {
            if (pattern[i] != -1 && static_cast<BYTE>(pattern[i]) != data[i]) {
                return false;
            }
        }
        return true;
        };

    HMODULE hModule = GetModuleHandleA(moduleName.c_str());
    if (!hModule) {
        return NULL;
    }

    MODULEINFO modInfo;
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
        return NULL;
    }

    BYTE* baseAddress = reinterpret_cast<BYTE*>(modInfo.lpBaseOfDll);
    FlexType moduleSize = modInfo.SizeOfImage;

    for (FlexType i = 0; i < moduleSize - pattern.size(); ++i) {
        BYTE* currentAddress = baseAddress + i;

        if (comparePattern(currentAddress, pattern)) {
            return reinterpret_cast<FlexType>(currentAddress);
        }
    }

    return NULL;
}

inline vector<string> split_string(const string& str, char delimiter) noexcept
{
    vector<string> splitted_string;

    size_t start = 0U;
    size_t end = str.find(delimiter);

    while (end != string::npos)
    {
        splitted_string.push_back(str.substr(start, end - start));
        start = end + sizeof(char);
        end = str.find(delimiter, start);
    }

    splitted_string.push_back(str.substr(start, end));

    return splitted_string;
}

inline vector<short> StringToBytesPattern(const string bytes) noexcept
{
    vector<string> bytesString = split_string(bytes, ' ');
    vector<short> vectorBytes;
    for (uint16_t i = 0; i < bytesString.size(); i++) {
        if (bytesString[i][0] == '?')
            vectorBytes.push_back(-1);
        else
            vectorBytes.push_back(stoi(bytesString[i], nullptr, 16));
    }

    return vectorBytes;
}