#pragma once

#include <string>
#include <vector>

class Utils {
public:

    /**
     * @brief Get overlay icon path from registry.
     */
    static bool GetOverlayIconPath(std::wstring *out) {
        std::wstring res;
        if (!ReadRegistryKeySzValue(L"SOFTWARE\\AoiHosizora\\FileIconOverlay", L"Icon", &res)) {
            return false;
        }

        res = TrimWstring(res, { L' ', L'"' });
        if (res.empty()) {
            return false;
        }
        *out = res;
        return true;
    }

    /**
     * @brief Get overlay priority path from registry.
     */
    static bool GetOverlayIconPriority(int *out) {
        std::wstring res;
        if (!ReadRegistryKeySzValue(L"SOFTWARE\\AoiHosizora\\FileIconOverlay", L"Priority", &res)) {
            return false;
        }

        int priority = 0;
        try {
            priority = std::stoi(res);
        } catch (...) { }
        if (priority < 0) {
            priority = 0;
        } else if (priority > 100) {
            priority = 100;
        }

        *out = priority;
        return true;
    }

    /**
     * @brief Get file paths which is need overlay icon.
     */
    static bool GetNeedOverlayFilePaths(std::vector<std::wstring> *out) {
        std::vector<std::wstring> names = {};
        if (!EnumRegistryKeyNames(L"SOFTWARE\\AoiHosizora\\FileIconOverlay\\Files", &names)) {
            return false;
        }

        *out = {};
        for (auto name : names) {
            auto path = TrimWstring(name, { L' ', L'"' });
            if (!path.empty()) {
                out->push_back(path);
            }
        }
        return true;
    }

private:

    /**
     * @breif Represent the max register string value length.
     */
    static const UINT MAX_REG_SZ_LENGTH = 2048;

    /**
     * @breif Represent the max register name length.
     */
    static const UINT MAX_REG_NAME_LENGTH = 2048;

    /**
     * @brief Read string value from given key path and value name.
     */
    static bool ReadRegistryKeySzValue(const std::wstring &key_path, const std::wstring &value_name, std::wstring *out) {
        HKEY key;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS) {
            return false;
        }

        WCHAR buf[MAX_REG_SZ_LENGTH];
        DWORD buf_size = sizeof(buf) / sizeof(buf[0]);
        if (RegQueryValueEx(key, value_name.c_str(), nullptr, nullptr, (LPBYTE) buf, &buf_size) != ERROR_SUCCESS) {
            return false;
        }
        RegCloseKey(key);

        *out = buf;
        return true;
    }

    /**
     * @brief Enum registry key all names.
     */
    static bool EnumRegistryKeyNames(const std::wstring &key_path, std::vector<std::wstring> *out) {
        HKEY key;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS) {
            return false;
        }

        *out = {};
        int index = 0;
        WCHAR buf[MAX_REG_NAME_LENGTH];
        DWORD buf_size = sizeof(buf) / sizeof(buf[0]);
        while (RegEnumValue(key, index, buf, &buf_size, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            index++;
            buf_size = sizeof(buf) / sizeof(buf[0]);
            out->push_back(buf);
        }
        RegCloseKey(key);

        return true;
    }

    /**
     * @brief Trim the given wstring using given chars.
     */
    static std::wstring TrimWstring(const std::wstring &str, const std::vector<wchar_t> &chars) {
        if (str.empty()) {
            return str;
        }
        std::wstring copy = str;

        auto exist_eq = [](const std::vector<wchar_t> chars, wchar_t given) -> bool {
            bool found = false;
            for (auto c : chars) {
                if (c == given) {
                    found = true;
                    break;
                }
            }
            return found;
        };

        bool need_trim_start = exist_eq(chars, copy.at(0));
        while (need_trim_start) {
            copy = copy.substr(1);
            need_trim_start = exist_eq(chars, copy.at(0));
        }
        bool need_trim_end = exist_eq(chars, copy.at(copy.length() - 1));
        while (need_trim_end) {
            copy = copy.substr(0, copy.length() - 1);
            need_trim_end = exist_eq(chars, copy.at(copy.length() - 1));
        }

        return copy;
    }
};
