/**
 * @file parse_item.cpp
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

#include <gtest/gtest.h>

#include <mdefparser/mdefparser.h>

using namespace std::string_view_literals;

static constexpr std::string_view NOT_EXISTING_FILE = "assets/not-existing-file.def"sv;

TEST(test_parse_item, common_parse_error) {
  auto parser = mugen::def::DefParserWin{};
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(NOT_EXISTING_FILE));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(NOT_EXISTING_FILE), mugen::def::FileIOError);
}

TEST(test_parse_item, parse_win_kfm) {
  static constexpr std::string_view kfmdef = "assets/good/kfm.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Name>(kfmdef), "Kung Fu Man");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(kfmdef), "Kung Fu Man");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::VersionDate>(kfmdef));
  auto versionDate = parser.parse_item<mugen::def::DefParseKey::VersionDate>(kfmdef);
  EXPECT_EQ(versionDate.month, 12);
  EXPECT_EQ(versionDate.day, 27);
  EXPECT_EQ(versionDate.year, 2007);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::MugenVersion>(kfmdef));
  auto mugenVersion = parser.parse_item<mugen::def::DefParseKey::MugenVersion>(kfmdef);
  EXPECT_EQ(mugenVersion.month, 4);
  EXPECT_EQ(mugenVersion.day, 14);
  EXPECT_EQ(mugenVersion.year, 2002);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Author>(kfmdef), "Elecbyte");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::PalDefaults>(kfmdef));
  auto palDefaults = parser.parse_item<mugen::def::DefParseKey::PalDefaults>(kfmdef);
  EXPECT_EQ(palDefaults.size(), 4);
  EXPECT_EQ(palDefaults[0], 6);
  EXPECT_EQ(palDefaults[1], 3);
  EXPECT_EQ(palDefaults[2], 4);
  EXPECT_EQ(palDefaults[3], 2);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cmd>(kfmdef), "kfm.cmd");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cns>(kfmdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St>(kfmdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::StCommon>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::StCommon>(kfmdef), "common1.cns");

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St2>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St2>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St3>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St3>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St4>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St4>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St5>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St5>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St6>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St6>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St7>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St7>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St8>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St8>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(kfmdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Ai>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Ai>(kfmdef), "kfm.ai");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sprite>(kfmdef), "kfm.sff");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Anim>(kfmdef), "kfm.air");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sound>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sound>(kfmdef), "kfm.snd");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal1>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal1>(kfmdef), "kfm6.act");
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal2>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal2>(kfmdef), "kfm4.act");
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal3>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal3>(kfmdef), "kfm2.act");
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal4>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal4>(kfmdef), "kfm5.act");
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal5>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal5>(kfmdef), "kfm3.act");
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal6>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal6>(kfmdef), "kfm.act");

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal7>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal7>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal8>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal8>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal9>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal9>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal10>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal10>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal11>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal11>(kfmdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal12>(kfmdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal12>(kfmdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Intro>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Intro>(kfmdef), "intro.def");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Ending>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Ending>(kfmdef), "ending.def");
}

TEST(test_parse_item, parse_win_test) {
  static constexpr std::string_view testdef = "assets/good/test.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Name>(testdef), "Kung Fu Man");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(testdef), "Kung Fu Man");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::VersionDate>(testdef));
  auto versionDate = parser.parse_item<mugen::def::DefParseKey::VersionDate>(testdef);
  EXPECT_EQ(versionDate.month, 12);
  EXPECT_EQ(versionDate.day, 27);
  EXPECT_EQ(versionDate.year, 2007);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::MugenVersion>(testdef));
  auto mugenVersion = parser.parse_item<mugen::def::DefParseKey::MugenVersion>(testdef);
  EXPECT_EQ(mugenVersion.month, 4);
  EXPECT_EQ(mugenVersion.day, 0);
  EXPECT_EQ(mugenVersion.year, 0);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(testdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::PalDefaults>(testdef));
  auto palDefaults = parser.parse_item<mugen::def::DefParseKey::PalDefaults>(testdef);
  EXPECT_EQ(palDefaults.size(), 2);
  EXPECT_EQ(palDefaults[0], 6);
  EXPECT_EQ(palDefaults[1], 3);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cmd>(testdef), "kfm.cmd");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cns>(testdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St>(testdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::StCommon>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::StCommon>(testdef), "common.cns");

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(testdef), mugen::def::MissingKeyError);
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St2>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St2>(testdef), "2.st");
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St3>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St3>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St4>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St4>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St5>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St5>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St6>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St6>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St7>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St7>(testdef), mugen::def::MissingKeyError);
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St8>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St8>(testdef), "8.st");
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(testdef), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Ai>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Ai>(testdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sprite>(testdef), "kfm.pcx");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Anim>(testdef), "anim.st");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sound>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sound>(testdef), "");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal1>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Pal1>(testdef), "kfm.act");
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal2>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal2>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal3>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal3>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal4>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal4>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal5>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal5>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal6>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal6>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal7>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal7>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal8>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal8>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal9>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal9>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal10>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal10>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal11>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal11>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Pal12>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Pal12>(testdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Intro>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Intro>(testdef), "intro.def");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Ending>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Ending>(testdef), "ending.def");
}

TEST(test_parse_item, missing_win) {
  static constexpr std::string_view missing_anim_def = "assets/bad/missing_anim.def"sv;
  static constexpr std::string_view missing_cmd_def = "assets/bad/missing_cmd.def"sv;
  static constexpr std::string_view missing_cns_def = "assets/bad/missing_cns.def"sv;
  static constexpr std::string_view missing_name_def = "assets/bad/missing_name.def"sv;
  static constexpr std::string_view missing_sprite_def = "assets/bad/missing_sprite.def"sv;
  static constexpr std::string_view missing_st_def = "assets/bad/missing_st.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(missing_anim_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(missing_anim_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(missing_cmd_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(missing_cmd_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(missing_cns_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(missing_cns_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(missing_name_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(missing_name_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(missing_sprite_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(missing_sprite_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St>(missing_st_def));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St>(missing_st_def), mugen::def::MissingKeyError);
}

TEST(test_parse_item, unquoted_win) {
  static constexpr std::string_view unquoted_name = "assets/bad/unquoted_name.def"sv;
  static constexpr std::string_view unquoted_displayname = "assets/bad/unquoted_displayname.def"sv;
  static constexpr std::string_view unquoted_author = "assets/bad/unquoted_author.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(unquoted_name));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(unquoted_name), mugen::def::DequotationError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(unquoted_displayname));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(unquoted_displayname), mugen::def::DequotationError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(unquoted_author));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(unquoted_author), mugen::def::DequotationError);
}
