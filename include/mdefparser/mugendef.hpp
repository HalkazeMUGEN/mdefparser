/**
 * @file mugendef.hpp
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

#ifndef MUGENDEF_HPP__
#define MUGENDEF_HPP__

#include "mdefparser/mdefparser.h"

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace mugen {
namespace def {

using namespace std::string_view_literals;

struct MugenDefVersion {
  std::int32_t month;
  std::int32_t day;
  std::int32_t year;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Name> {
  using type = std::string;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "name"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::DsiplayName> {
  using type = std::string;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "displayname"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::VersionDate> {
  using type = MugenDefVersion;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "versiondate"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::MugenVersion> {
  using type = MugenDefVersion;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "mugenversion"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Author> {
  using type = std::string;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "author"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::PalDefaults> {
  using type = std::vector<std::int32_t>;
  static inline constexpr std::string_view section = "[info]"sv;
  static inline constexpr std::string_view key = "pal.defaults"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Cmd> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "cmd"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Cns> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "cns"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::StCommon> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "stcommon"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St0> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st0"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St1> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st1"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St2> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st2"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St3> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st3"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St4> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st4"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St5> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st5"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St6> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st6"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St7> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st7"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St8> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st8"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::St9> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "st9"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Ai> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "ai"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Sprite> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "sprite"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Anim> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "anim"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Sound> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "sound"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal1> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal1"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal2> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal2"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal3> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal3"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal4> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal4"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal5> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal5"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal6> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal6"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal7> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal7"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal8> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal8"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal9> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal9"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal10> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal10"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal11> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal11"sv;
};
template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Pal12> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[files]"sv;
  static inline constexpr std::string_view key = "pal12"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Intro> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[arcade]"sv;
  static inline constexpr std::string_view key = "intro.storyboard"sv;
};

template <>
struct mugen::def::DefItemType<mugen::def::DefParseKey::Ending> {
  using type = std::filesystem::path;
  static inline constexpr std::string_view section = "[arcade]"sv;
  static inline constexpr std::string_view key = "ending.storyboard"sv;
};

template <>
struct MugenDef<MugenVersion::Win> {
 public:
  struct Info {
    DefItemType<DefParseKey::Name>::type name;
    std::optional<DefItemType<DefParseKey::DsiplayName>::type> displayName;
    std::optional<DefItemType<DefParseKey::VersionDate>::type> versionDate;
    std::optional<DefItemType<DefParseKey::MugenVersion>::type> mugenVersion;
    std::optional<DefItemType<DefParseKey::Author>::type> author;
    std::optional<DefItemType<DefParseKey::PalDefaults>::type> palDefaults;
  } info;

  struct Files {
    DefItemType<DefParseKey::Cmd>::type cmd;
    DefItemType<DefParseKey::Cns>::type cns;
    DefItemType<DefParseKey::St>::type st;
    std::optional<DefItemType<DefParseKey::StCommon>::type> stcommon;
    std::optional<DefItemType<DefParseKey::St0>::type> st0;
    std::optional<DefItemType<DefParseKey::St1>::type> st1;
    std::optional<DefItemType<DefParseKey::St2>::type> st2;
    std::optional<DefItemType<DefParseKey::St3>::type> st3;
    std::optional<DefItemType<DefParseKey::St4>::type> st4;
    std::optional<DefItemType<DefParseKey::St5>::type> st5;
    std::optional<DefItemType<DefParseKey::St6>::type> st6;
    std::optional<DefItemType<DefParseKey::St7>::type> st7;
    std::optional<DefItemType<DefParseKey::St8>::type> st8;
    std::optional<DefItemType<DefParseKey::St9>::type> st9;
    std::optional<DefItemType<DefParseKey::Ai>::type> ai;

    DefItemType<DefParseKey::Sprite>::type sprite;
    DefItemType<DefParseKey::Anim>::type anim;
    std::optional<DefItemType<DefParseKey::Sound>::type> sound;
    std::optional<DefItemType<DefParseKey::Pal1>::type> pal1;
    std::optional<DefItemType<DefParseKey::Pal2>::type> pal2;
    std::optional<DefItemType<DefParseKey::Pal3>::type> pal3;
    std::optional<DefItemType<DefParseKey::Pal4>::type> pal4;
    std::optional<DefItemType<DefParseKey::Pal5>::type> pal5;
    std::optional<DefItemType<DefParseKey::Pal6>::type> pal6;
    std::optional<DefItemType<DefParseKey::Pal7>::type> pal7;
    std::optional<DefItemType<DefParseKey::Pal8>::type> pal8;
    std::optional<DefItemType<DefParseKey::Pal9>::type> pal9;
    std::optional<DefItemType<DefParseKey::Pal10>::type> pal10;
    std::optional<DefItemType<DefParseKey::Pal11>::type> pal11;
    std::optional<DefItemType<DefParseKey::Pal12>::type> pal12;
  } files;

  struct Arcade {
    std::optional<DefItemType<DefParseKey::Intro>::type> intro;
    std::optional<DefItemType<DefParseKey::Ending>::type> ending;
  } arcade;
};

};  // namespace def
};  // namespace mugen

#endif  // MUGENDEF_HPP__
