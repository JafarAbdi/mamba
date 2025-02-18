// Copyright (c) 2019, QuantStack and Mamba Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef MAMBA_CORE_ENVIRONMENT_HPP
#define MAMBA_CORE_ENVIRONMENT_HPP

#include <map>
#include <cstdlib>
#include <cassert>
#include <string_view>
#include <optional>

#include "mamba_fs.hpp"

#ifdef _WIN32
#include <Shlobj.h>
#endif

#ifndef _WIN32
#include <sys/utsname.h>
#include <wordexp.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

extern "C"
{
    extern char** environ;
}
#endif

namespace mamba
{
    namespace env
    {
        constexpr inline const char* pathsep()
        {
#ifdef _WIN32
            return ";";
#else
            return ":";
#endif
        }

        std::optional<std::string> get(const std::string& key);
        bool set(const std::string& key, const std::string& value);
        void unset(const std::string& key);

        fs::u8path which(const std::string& exe, const std::string& override_path = "");
        fs::u8path which(const std::string& exe, const std::vector<fs::u8path>& search_paths);
        std::map<std::string, std::string> copy();
        std::string platform();
        fs::u8path home_directory();

        fs::u8path expand_user(const fs::u8path& path);
        fs::u8path shrink_user(const fs::u8path& path);
    }
}

#endif
