/*
MIT License

Copyright (c) 2019 Michal Bubnár

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// [Credit] https://github.com/michalbb1/opengl4-tutorials-mbsoftworks
// [Credit] https://www.mbsoftworks.sk/tutorials/opengl4/030-animation-pt1-keyframe-md2/
// With minor modifications to fit this project.
#pragma once

#include <vector>
#include <string>
#include <sstream>


namespace string_utils
{

/**
 * Splits given string with given delimiter and returns std::vector of tokens.
 *
 * @param s String to split
 * @param t Delimiter
 *
 * @return std::vector of tokens.
 */
inline std::vector<std::string> split(std::string s, char t)
{
    std::vector<std::string> res;
    while (true)
    {
        auto pos = s.find(t);
        if (pos == -1)
        {
            if (s.size() > 0)
                res.push_back(s);
            break;
        }
        std::string tp = s.substr(0, pos);
        if (tp.size() != 0)
            res.push_back(tp);
        s = s.substr(pos + 1, s.size() - pos - 1);
    }
    return res;
}

/**
 * Goes one directory up in a path.
 * 
 * @param originalPath   Original path
 * @param slashCharacter Slash character to use (/ or \)
 * 
 * @return Path with one directory up.
 */
inline std::string upOneDirectory(const std::string& originalPath, char slashCharacter)
{
    bool isTrailingSlash = originalPath.back() == slashCharacter;
    std::vector<std::string> subPaths = split(originalPath, slashCharacter);
    std::string result = "";
    for (size_t i = 0; i < subPaths.size() - 1; i++)
    {
        if (i > 0)
            result += slashCharacter;
        result += subPaths[i];
    }
    if (isTrailingSlash && result.size() > 0)
        result += slashCharacter;

    return result;
}

/**
 * Normalizes slashes in a path, so that all slashes are consistent.
 * 
 * @param originalPath   Original path
 * @param slashCharacter Slash character to use (/ or \)
 * 
 * @return Original path with same slash character everywhere.
 */
inline std::string normalizeSlashes(const std::string& originalPath, char slashCharacter)
{
    std::string result = originalPath;
    for (char& c : result)
    {
        if (c == '\\' || c == '/')
            c = slashCharacter;
    }

    return result;
}

inline std::string getDirectoryPath(const std::string& filePath)
{
    auto lastSlashIndex = filePath.find_last_of('\\');
    if (lastSlashIndex == std::string::npos) {
        lastSlashIndex = filePath.find_last_of('/');
    }

    if (lastSlashIndex == std::string::npos) {
        return "";
    }

    return filePath.substr(0, lastSlashIndex + 1);
}

inline std::string formatStringImpl(const char* s, std::stringstream& ss)
{
    ss << s;
    return ss.str();
}

template <typename T, typename... Args>
inline std::string formatStringImpl(const char* s, std::stringstream& ss, T arg, const Args&... args)
{
    std::string result;
    while (*s != 0)
    {
        if (*s == '{' && *(s + 1) == '}')
        {
            ss << arg;
            result = formatStringImpl(s + 2 * sizeof(char), ss, args...);
            break;
        }
        else ss << *s;
        s++;
    }
    return result;
}

template <typename... Args>
inline std::string formatString(const std::string& fmt, const Args&... args)
{
    std::stringstream ss;
    return formatStringImpl(fmt.c_str(), ss, args...);
}

} // namespace string_utils