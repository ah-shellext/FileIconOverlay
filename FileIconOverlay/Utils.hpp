#pragma once

#include <string>
#include <vector>

class Utils {
public:

    /**
     * @breif Represent the max register key length.
     */
    static const UINT MAX_REG_KEY_LENGTH = 2048;

    /**
     * @breif Represent the max register string value length.
     */
    static const UINT MAX_REG_SZ_LENGTH = 2048;

    /**
     * @brief Get overlay icon path from registry.
     */
    static bool GetOverlayIconPath(std::wstring *out) {
        // get key
        std::wstring reg_path = L"SOFTWARE\\AoiHosizora\\FileIconOverlay";
        HKEY root_key;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, reg_path.c_str(), 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &root_key) != ERROR_SUCCESS) {
            return false;
        }

        // get icon value
        WCHAR buf[MAX_REG_SZ_LENGTH];
        DWORD buf_size = sizeof(buf) / sizeof(buf[0]);
        if (RegQueryValueEx(root_key, L"Icon", nullptr, nullptr, (LPBYTE) buf, &buf_size) != ERROR_SUCCESS) {
            return false;
        }
        RegCloseKey(root_key);

        // check icon value
        std::wstring path = buf;
        path = TrimWstring(path, { L' ', L'"' });
        if (path.empty()) {
            return false;
        }

        // set return value
        *out = path;
        return true;
    }

    static bool GetOverlayIconPriority(int *out) {
        // get key
        std::wstring reg_path = L"SOFTWARE\\AoiHosizora\\FileIconOverlay";
        HKEY root_key;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, reg_path.c_str(), 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &root_key) != ERROR_SUCCESS) {
            return false;
        }

        // get priority value
        WCHAR buf[MAX_REG_SZ_LENGTH];
        DWORD buf_size = sizeof(buf) / sizeof(buf[0]);
        if (RegQueryValueEx(root_key, L"Priority", nullptr, nullptr, (LPBYTE) buf, &buf_size) != ERROR_SUCCESS) {
            return false;
        }
        RegCloseKey(root_key);

        // check priority value
        std::wstring priority_str = buf;
        int priority = 0;
        try {
            priority = std::stoi(priority_str);
        } catch (...) { }
        if (priority < 0) {
            priority = 0;
        } else if (priority > 100) {
            priority = 100;
        }

        // set return value
        *out = priority;
        return true;
    }

    /**
     * @brief Get file paths which is need overlay icon.
     */
    static bool GetNeedOverlayFilePaths(std::vector<std::wstring> *out) {
        // get key
        std::wstring reg_path = L"SOFTWARE\\AoiHosizora\\FileIconOverlay\\Files";
        HKEY reg_key;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, reg_path.c_str(), 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &reg_key) != ERROR_SUCCESS) {
            return false;
        }

        // get sub keys
        *out = {};
        int index = 0;
        WCHAR buf[MAX_REG_KEY_LENGTH];
        DWORD buf_size = sizeof(buf) / sizeof(buf[0]);
        while (RegEnumValue(reg_key, index, buf, &buf_size, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            index++;
            buf_size = sizeof(buf) / sizeof(buf[0]);

            // check path
            std::wstring path = buf;
            path = TrimWstring(path, { L' ', L'"' });
            out->push_back(path);
        }
        RegCloseKey(reg_key);

        return true;
    }

private:

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
