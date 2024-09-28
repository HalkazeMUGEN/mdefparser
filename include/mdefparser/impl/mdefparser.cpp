/**
 * @file mdefparser.cpp
 * @author Halkaze
 * @date 2024-09-28
 *
 * @copyright Copyright (c) 2024
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef MDEFPARSER_HEADER_ONLY
#define MDEFPARSER_INLINE inline
#else
#define MDEFPARSER_INLINE
#endif

#include "mdefparser/mdefparser.h"

#include <array>
#include <cctype>
#include <cstring>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>

#include <iostream>

namespace mugen {
namespace def {
namespace internal {

using namespace std::string_view_literals;

static inline void tolowers(std::string& str, size_t count = std::string::npos) noexcept {
  if (count == std::string::npos) {
    count = str.size();
  }

  for (size_t i = 0; i < count; ++i) {
    str[i] = static_cast<char>(std::tolower(str[i]));
  }
}

static inline std::string trimline(char* line) noexcept {
  // Remove comment
  char* p = std::strchr(line, ';');
  if (p) {
    *p = '\0';
  }

  // ltrim
  size_t len = std::strlen(line);
  size_t start = std::strspn(line, " \t\n");
  if (start > 0) {
    std::memmove(line, &line[start], len + 1 - start);
    len -= start;
  }

  // rtrim
  char c;
  while (len > 0 && ((c = line[len - 1]) == ' ' || c == '\t' || c == '\n')) {
    line[len - 1] = '\0';
    --len;
  }

  return std::string(line, len + 1);
}

static inline std::optional<std::array<std::string_view, 2>> get_key_value(std::string& line) noexcept {
  // 文字「=」、文字「 」がKeyの中に含まれるケースは想定しない

  size_t delim = line.find_first_of(" \t\n=");
  if (delim == std::string::npos) {
    return std::nullopt;
  }

  // 「=」の位置を特定
  size_t eqpos = delim;
  if (line[eqpos] != '=') {
    eqpos = line.find_first_of('=');
    if (eqpos == std::string::npos) {
      return std::nullopt;
    }
  }

  // 元の文字列を Key と Value で分割
  line.data()[delim] = '\0';

  // key は小文字化して返却
  mugen::def::internal::tolowers(line, delim);
  std::string_view key(line.data(), delim + 1);

  // value のみ見つからない場合は 空文字列 を返させる
  size_t offset = line.find_first_not_of(" \t\n", eqpos + 1);
  if (offset == std::string::npos) {
    return std::make_optional<std::array<std::string_view, 2>>({key, ""sv});
  }

  std::string_view value(&line.data()[offset]);
  return std::make_optional<std::array<std::string_view, 2>>({key, value});
}

static inline std::optional<std::string_view> dequote_string(std::string_view value) noexcept {
  size_t len = value.size();
  if (value[0] == '\"' && value[len - 1] == '\"') {
    return value.substr(1, len - 2);
  } else {
    return std::nullopt;
  }
}

static inline mugen::def::MugenDefVersion convert_to_version(std::string_view value) noexcept {
  std::array<std::int32_t, 3> mdy{0, 0, 0};

  size_t start = 0;
  size_t cnt = 0;
  while (cnt < 3) {
    size_t last = value.find_first_of(',', start);
    try {
      mdy[cnt] = std::stoi(std::string{value.substr(start, last - start)});
    } catch (...) {
      break;
    }

    if (last == std::string_view::npos) {
      break;
    }
    start = last + 1;
    ++cnt;
  }

  return mugen::def::MugenDefVersion{.month = mdy[0], .day = mdy[1], .year = mdy[2]};
}

static inline std::vector<std::int32_t> parse_pal_defaults(std::string_view value) noexcept {
  // pal.defaults は 先頭4つのみ有効なので、
  // 最大長は4とする

  // 途中で数字以外が出現した場合はそこで打ち切り
  // 例) 1, 2, foo, 3 => {1, 2}

  std::vector<std::int32_t> vec{};

  size_t start = 0;
  while (vec.size() < 4) {
    size_t last = value.find_first_of(',', start);
    try {
      vec.push_back(std::stoi(std::string{value.substr(start, last - start)}));
    } catch (...) {
      return vec;
    }

    if (last == std::string_view::npos) {
      break;
    }
    start = last + 1;
  }

  return vec;
}

};  // namespace internal
};  // namespace def
};  // namespace mugen

template <>
MDEFPARSER_INLINE mugen::def::DefParserWin::DefParser() noexcept {}

template <>
MDEFPARSER_INLINE mugen::def::MugenDefWin mugen::def::DefParserWin::parse(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
    throw mugen::def::FileIOError{"Can't find the specified file."};
  }

  std::ifstream fs{path, std::ios_base::in};

  bool inInfo = false;
  bool inFiles = false;
  bool inArcade = false;

  bool hasInfo = false;
  bool hasFiles = false;
  bool hasArcade = false;

  std::optional<std::string> name{};
  std::optional<std::string> displayName{};
  std::optional<mugen::def::MugenDefVersion> versionDate{};
  std::optional<mugen::def::MugenDefVersion> mugenVersion{};
  std::optional<std::string> author{};
  std::optional<std::vector<std::int32_t>> palDefaults{};

  std::optional<std::filesystem::path> cmd{};
  std::optional<std::filesystem::path> cns{};
  std::optional<std::filesystem::path> st{};
  std::optional<std::filesystem::path> stcommon{};
  std::optional<std::filesystem::path> st0{};
  std::optional<std::filesystem::path> st1{};
  std::optional<std::filesystem::path> st2{};
  std::optional<std::filesystem::path> st3{};
  std::optional<std::filesystem::path> st4{};
  std::optional<std::filesystem::path> st5{};
  std::optional<std::filesystem::path> st6{};
  std::optional<std::filesystem::path> st7{};
  std::optional<std::filesystem::path> st8{};
  std::optional<std::filesystem::path> st9{};
  std::optional<std::filesystem::path> ai{};
  std::optional<std::filesystem::path> sprite{};
  std::optional<std::filesystem::path> anim{};
  std::optional<std::filesystem::path> sound{};
  std::optional<std::filesystem::path> pal1{};
  std::optional<std::filesystem::path> pal2{};
  std::optional<std::filesystem::path> pal3{};
  std::optional<std::filesystem::path> pal4{};
  std::optional<std::filesystem::path> pal5{};
  std::optional<std::filesystem::path> pal6{};
  std::optional<std::filesystem::path> pal7{};
  std::optional<std::filesystem::path> pal8{};
  std::optional<std::filesystem::path> pal9{};
  std::optional<std::filesystem::path> pal10{};
  std::optional<std::filesystem::path> pal11{};
  std::optional<std::filesystem::path> pal12{};

  std::optional<std::filesystem::path> intro{};
  std::optional<std::filesystem::path> ending{};

  char buffer[0x100];
  while (true) {
    fs.getline(buffer, sizeof(buffer));
    if (fs.bad() || fs.eof()) {
      break;
    }
    if (fs.fail()) {
      fs.clear(fs.rdstate() & ~std::ios_base::failbit);
    }

    auto line = mugen::def::internal::trimline(buffer);
    if (inInfo || inFiles || inArcade) {
      if (line[0] == '[') {
        inInfo = false;
        inFiles = false;
        inArcade = false;

        if (hasInfo && hasFiles && hasArcade) {
          break;
        }
      }
    }

    if (inInfo || inFiles || inArcade) {
      auto result = mugen::def::internal::get_key_value(line);
      if (result) {
        auto key = (*result)[0];
        auto value = (*result)[1];

        if (inInfo) {
          if (std::strcmp(key.data(), "name") == 0) {
            if (!name) {
              name = mugen::def::internal::dequote_string(value);
              if (!name) {
                throw mugen::def::DequotationError{"Name is not quoted."};
              }
            }
          } else if (std::strcmp(key.data(), "displayname") == 0) {
            if (!displayName) {
              displayName = mugen::def::internal::dequote_string(value);
              if (!displayName) {
                throw mugen::def::DequotationError{"DisplayName is not quoted."};
              }
            }
          } else if (std::strcmp(key.data(), "versiondate") == 0) {
            if (!versionDate) {
              versionDate = mugen::def::internal::convert_to_version(value);
            }
          } else if (std::strcmp(key.data(), "mugenversion") == 0) {
            if (!mugenVersion) {
              mugenVersion = mugen::def::internal::convert_to_version(value);
            }
          } else if (std::strcmp(key.data(), "author") == 0) {
            if (!author) {
              author = mugen::def::internal::dequote_string(value);
              if (!author) {
                throw mugen::def::DequotationError{"Author is not quoted."};
              }
            }
          } else if (std::strcmp(key.data(), "pal.defaults") == 0) {
            if (!palDefaults) {
              palDefaults = mugen::def::internal::parse_pal_defaults(value);
            }
          }
        } else if (inFiles) {
          if (std::strcmp(key.data(), "cmd") == 0) {
            if (!cmd) {
              cmd = value;
            }
          } else if (std::strcmp(key.data(), "cns") == 0) {
            if (!cns) {
              cns = value;
            }
          } else if (std::strcmp(key.data(), "st") == 0) {
            if (!st) {
              st = value;
            }
          } else if (std::strcmp(key.data(), "stcommon") == 0) {
            if (!stcommon) {
              stcommon = value;
            }
          } else if (std::strcmp(key.data(), "st0") == 0) {
            if (!st0) {
              st0 = value;
            }
          } else if (std::strcmp(key.data(), "st1") == 0) {
            if (!st1) {
              st1 = value;
            }
          } else if (std::strcmp(key.data(), "st2") == 0) {
            if (!st2) {
              st2 = value;
            }
          } else if (std::strcmp(key.data(), "st3") == 0) {
            if (!st3) {
              st3 = value;
            }
          } else if (std::strcmp(key.data(), "st4") == 0) {
            if (!st4) {
              st4 = value;
            }
          } else if (std::strcmp(key.data(), "st5") == 0) {
            if (!st5) {
              st5 = value;
            }
          } else if (std::strcmp(key.data(), "st6") == 0) {
            if (!st6) {
              st6 = value;
            }
          } else if (std::strcmp(key.data(), "st7") == 0) {
            if (!st7) {
              st7 = value;
            }
          } else if (std::strcmp(key.data(), "st8") == 0) {
            if (!st8) {
              st8 = value;
            }
          } else if (std::strcmp(key.data(), "st9") == 0) {
            if (!st9) {
              st9 = value;
            }
          } else if (std::strcmp(key.data(), "ai") == 0) {
            if (!ai) {
              ai = value;
            }
          } else if (std::strcmp(key.data(), "sprite") == 0) {
            if (!sprite) {
              sprite = value;
            }
          } else if (std::strcmp(key.data(), "anim") == 0) {
            if (!anim) {
              anim = value;
            }
          } else if (std::strcmp(key.data(), "sound") == 0) {
            if (!sound) {
              sound = value;
            }
          } else if (std::strcmp(key.data(), "pal1") == 0) {
            if (!pal1) {
              pal1 = value;
            }
          } else if (std::strcmp(key.data(), "pal2") == 0) {
            if (!pal2) {
              pal2 = value;
            }
          } else if (std::strcmp(key.data(), "pal3") == 0) {
            if (!pal3) {
              pal3 = value;
            }
          } else if (std::strcmp(key.data(), "pal4") == 0) {
            if (!pal4) {
              pal4 = value;
            }
          } else if (std::strcmp(key.data(), "pal5") == 0) {
            if (!pal5) {
              pal5 = value;
            }
          } else if (std::strcmp(key.data(), "pal6") == 0) {
            if (!pal6) {
              pal6 = value;
            }
          } else if (std::strcmp(key.data(), "pal7") == 0) {
            if (!pal7) {
              pal7 = value;
            }
          } else if (std::strcmp(key.data(), "pal8") == 0) {
            if (!pal8) {
              pal8 = value;
            }
          } else if (std::strcmp(key.data(), "pal9") == 0) {
            if (!pal9) {
              pal9 = value;
            }
          } else if (std::strcmp(key.data(), "pal10") == 0) {
            if (!pal10) {
              pal10 = value;
            }
          } else if (std::strcmp(key.data(), "pal11") == 0) {
            if (!pal11) {
              pal11 = value;
            }
          } else if (std::strcmp(key.data(), "pal12") == 0) {
            if (!pal12) {
              pal12 = value;
            }
          }
        } else if (inArcade) {
          if (std::strcmp(key.data(), "intro.storyboard") == 0) {
            if (!intro) {
              intro = value;
            }
          } else if (std::strcmp(key.data(), "ending.storyboard") == 0) {
            if (!ending) {
              ending = value;
            }
          }
        }
      }
    } else if (line[0] == '[') {
      mugen::def::internal::tolowers(line);
      if (!hasInfo && std::strcmp(line.c_str(), "[info]") == 0) {
        inInfo = true;
        hasInfo = true;
      } else if (!hasFiles && std::strcmp(line.c_str(), "[files]") == 0) {
        inFiles = true;
        hasFiles = true;
      } else if (!hasArcade && std::strcmp(line.c_str(), "[arcade]") == 0) {
        inArcade = true;
        hasArcade = true;
      }
    }
  }

  if (!name || !cmd || !cns || !st || !sprite || !anim) {
    throw mugen::def::MissingKeyError{"Required parameter does not exist."};
  }

  return mugen::def::MugenDefWin{.info{.name = *name,
                                       .displayName = displayName,
                                       .versionDate = versionDate,
                                       .mugenVersion = mugenVersion,
                                       .author = author,
                                       .palDefaults = palDefaults},
                                 .files{.cmd = *cmd,
                                        .cns = *cns,
                                        .st = *st,
                                        .stcommon = stcommon,
                                        .st0 = st0,
                                        .st1 = st1,
                                        .st2 = st2,
                                        .st3 = st3,
                                        .st4 = st4,
                                        .st5 = st5,
                                        .st6 = st6,
                                        .st7 = st7,
                                        .st8 = st8,
                                        .st9 = st9,
                                        .ai = ai,
                                        .sprite = *sprite,
                                        .anim = *anim,
                                        .sound = sound,
                                        .pal1 = pal1,
                                        .pal2 = pal2,
                                        .pal3 = pal3,
                                        .pal4 = pal4,
                                        .pal5 = pal5,
                                        .pal6 = pal6,
                                        .pal7 = pal7,
                                        .pal8 = pal8,
                                        .pal9 = pal9,
                                        .pal10 = pal10,
                                        .pal11 = pal11,
                                        .pal12 = pal12},
                                 .arcade{.intro = intro, .ending = ending}};
}

template <>
template <mugen::def::DefParseKey Key>
MDEFPARSER_INLINE typename mugen::def::DefItemType<Key>::type mugen::def::DefParserWin::parse_item(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
    throw mugen::def::FileIOError{"Can't find the specified file."};
  }

  std::ifstream fs{path, std::ios_base::in};

  bool inTargetSection = false;

  char buffer[0x100];
  while (true) {
    fs.getline(buffer, sizeof(buffer));
    if (fs.bad() || fs.eof()) {
      break;
    }
    if (fs.fail()) {
      fs.clear(fs.rdstate() & ~std::ios_base::failbit);
    }

    auto line = mugen::def::internal::trimline(buffer);
    if (inTargetSection) {
      if (line[0] == '[') {
        break;
      }

      auto result = mugen::def::internal::get_key_value(line);
      if (result) {
        auto key = (*result)[0];
        auto value = (*result)[1];

        if (std::strcmp(key.data(), mugen::def::DefItemType<Key>::key.data()) == 0) {
          if constexpr (Key == mugen::def::DefParseKey::Name || Key == mugen::def::DefParseKey::DsiplayName ||
                        Key == mugen::def::DefParseKey::Author) {
            auto dequoted = mugen::def::internal::dequote_string(value);
            if (dequoted) {
              return std::string{*dequoted};
            } else {
              throw mugen::def::DequotationError{"Required parameter is not quoted."};
            }
          } else if constexpr (Key == mugen::def::DefParseKey::VersionDate || Key == mugen::def::DefParseKey::MugenVersion) {
            return mugen::def::internal::convert_to_version(value);
          } else if constexpr (Key == mugen::def::DefParseKey::PalDefaults) {
            return mugen::def::internal::parse_pal_defaults(value);
          } else {
            return value;
          }
        }
      }
    } else if (line[0] == '[') {
      mugen::def::internal::tolowers(line);
      if (std::strcmp(line.c_str(), mugen::def::DefItemType<Key>::section.data()) == 0) {
        inTargetSection = true;
      }
    }
  }

  throw mugen::def::MissingKeyError{"Required parameter does not exist."};
}

#ifndef MDEFPARSER_HEADER_ONLY
template class mugen::def::DefParser<mugen::def::MugenVersion::Win>;

template mugen::def::DefItemType<mugen::def::DefParseKey::Name>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Name>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::DsiplayName>::type
mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::DsiplayName>(const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::VersionDate>::type
mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::VersionDate>(const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::MugenVersion>::type
mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::MugenVersion>(const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Author>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Author>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::PalDefaults>::type
mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::PalDefaults>(const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Cmd>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Cmd>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Cns>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Cns>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::StCommon>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::StCommon>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St0>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St0>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St1>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St1>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St2>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St2>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St3>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St3>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St4>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St4>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St5>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St5>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St6>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St6>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St7>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St7>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St8>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St8>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::St9>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::St9>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Ai>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Ai>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Sprite>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Sprite>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Anim>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Anim>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Sound>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Sound>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal1>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal1>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal2>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal2>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal3>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal3>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal4>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal4>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal5>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal5>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal6>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal6>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal7>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal7>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal8>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal8>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal9>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal9>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal10>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal10>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal11>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal11>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Pal12>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Pal12>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Intro>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Intro>(
    const std::filesystem::path& path);
template mugen::def::DefItemType<mugen::def::DefParseKey::Ending>::type mugen::def::DefParserWin::parse_item<mugen::def::DefParseKey::Ending>(
    const std::filesystem::path& path);
#endif
