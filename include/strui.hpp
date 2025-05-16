#pragma once

#ifndef STRUI_HPP
#define STRUI_HPP
#define STRUI_VERSION "1.0.0"

#include <string>
#include <vector>
#include <optional>
#include <unistr.h>     // libunistring lib → used in `width` for unicode-awarness
#include <uniwidth.h>   // libunistring lib → used in `width` for unicode-awarness

namespace strui {

    using string = std::string;
    template<typename T> using vector = std::vector<T>;
    template<typename T> using opt = std::optional<T>;

    string clean(const string& input);
    size_t flat_width(const string &input);
    size_t width(const string &input);
    size_t height(const string& input);
    size_t count(const string& value, const string& str);
    string join(const vector<string> &strings, const string &separator = "");
    string repeat(const size_t count, const string &str, const string &separator = "");
    vector<string> split(const string &str, const string &separator);

    // Remove ANSI escape sequences
    inline string clean(const string& input)
    {
        string output;
        size_t i = 0;

        while (i < input.length()) {
            if (input[i] == '\033' && i + 1 < input.length() && input[i + 1] == '[') {
                i += 2;
                while (i < input.length() && !(input[i] >= '@' && input[i] <= '~')) {
                    i++;
                }
                if (i < input.length()) i++;
            } else {
                output += input[i++];
            }
        }

        return output;
    }

    // Return display width (unicode-aware) of a string (ignoring "\n")
    inline size_t flat_width(const string &input)
    {
        std::string cleaned = clean(input);

        const uint8_t *utf8_cast = reinterpret_cast<const uint8_t *>(cleaned.c_str());
        int width = u8_width(utf8_cast, cleaned.length(), "UTF-8");

        return (width < 0) ? 0 : static_cast<size_t>(width);
    }

    // Return display width (unicode-aware) of the longest line of a string (splitted on "\n")
    inline size_t width(const string &input)
    {
        vector<string> lines = split(input, "\n");

        size_t max_width = 0;
        for (const auto& line : lines)
        {
            size_t width = flat_width(line);
            if (width > max_width) max_width = width;
        }

        return max_width;
    }

    inline size_t height(const string& input)
    {
        return count("\n", input) + 1;
    }

    inline size_t count(const string& value, const string& str)
    {
        if (value.empty()) return 0;

        size_t count = 0;
        size_t position = 0;
        while ((position = str.find(value, position)) != string::npos) {
            ++count;
            position += value.length();
        }

        return count;
    }

    inline string join(const vector<string> &strings, const string &separator)
    {
        if (strings.empty()) return "";

        string result = strings[0];
        for (size_t i = 1; i < strings.size(); ++i)
        {
            result += separator + strings[i];
        }

        return result;
    }

    inline string repeat(const size_t count, const string &str, const string &separator)
    {
        if (count == 0) return "";

        string result = str;
        for (size_t i = 1; i < count; ++i) {
            result += separator + str;
        }

        return result;
    }

    inline vector<string> split(const string &str, const string &separator)
    {
        vector<string> result;
        size_t separator_length = separator.length();
        size_t start = 0;

        while (true) {
            size_t position = str.find(separator, start);
            if (position == string::npos) break;

            result.push_back(str.substr(start, position - start));
            start = position + separator_length;
        }

        result.push_back(str.substr(start));
        return result;
    }
}

#endif

