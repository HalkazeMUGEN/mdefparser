/**
 * @file mdefparser.h
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

#ifndef MDEFPARSER_H__
#define MDEFPARSER_H__

#include <filesystem>

namespace mugen {
namespace def {

enum class MugenVersion {
  Win,
  // Latest, 必要になったら実装できるように
};

template <MugenVersion version>
struct MugenDef;

enum class DefParseKey {
  Name,
  DsiplayName,
  VersionDate,
  MugenVersion,
  Author,
  PalDefaults,
  Cmd,
  Cns,
  St,
  StCommon,
  St0,
  St1,
  St2,
  St3,
  St4,
  St5,
  St6,
  St7,
  St8,
  St9,
  Ai,
  Sprite,
  Anim,
  Sound,
  Pal1,
  Pal2,
  Pal3,
  Pal4,
  Pal5,
  Pal6,
  Pal7,
  Pal8,
  Pal9,
  Pal10,
  Pal11,
  Pal12,
  Intro,
  Ending,
};

template <DefParseKey Key>
struct DefItemType;

template <MugenVersion Version>
class DefParser {
 public:
  DefParser(const DefParser&) = delete;
  DefParser& operator=(const DefParser&) = delete;

  DefParser(DefParser&&) = default;
  DefParser& operator=(DefParser&&) = default;

  explicit DefParser() noexcept;

  MugenDef<Version> parse(const std::filesystem::path& path);

  template <DefParseKey Key>
  typename DefItemType<Key>::type parse_item(const std::filesystem::path& path);
};

using DefParserWin = DefParser<MugenVersion::Win>;
using MugenDefWin = MugenDef<MugenVersion::Win>;

};  // namespace def
};  // namespace mugen

#include "mdefparser/exception.hpp"
#include "mdefparser/mugendef.hpp"

#ifdef MDEFPARSER_HEADER_ONLY
#include "mdefparser/impl/mdefparser.cpp"
#endif

#endif  // MDEFPARSER_H__
