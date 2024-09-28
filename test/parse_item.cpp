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
  auto displayName = parser.parse_item<mugen::def::DefParseKey::DsiplayName>(kfmdef);
  EXPECT_TRUE(displayName);
  if (displayName) {
    EXPECT_EQ(*displayName, "Kung Fu Man");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::VersionDate>(kfmdef));
  auto versionDate = parser.parse_item<mugen::def::DefParseKey::VersionDate>(kfmdef);
  EXPECT_TRUE(versionDate);
  if (versionDate) {
    EXPECT_EQ(versionDate->month, 12);
    EXPECT_EQ(versionDate->day, 27);
    EXPECT_EQ(versionDate->year, 2007);
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::MugenVersion>(kfmdef));
  auto mugenVersion = parser.parse_item<mugen::def::DefParseKey::MugenVersion>(kfmdef);
  EXPECT_TRUE(mugenVersion);
  if (mugenVersion) {
    EXPECT_EQ(mugenVersion->month, 4);
    EXPECT_EQ(mugenVersion->day, 14);
    EXPECT_EQ(mugenVersion->year, 2002);
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(kfmdef));
  auto author = parser.parse_item<mugen::def::DefParseKey::Author>(kfmdef);
  EXPECT_TRUE(author);
  if (author) {
    EXPECT_EQ(*author, "Elecbyte");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::PalDefaults>(kfmdef));
  auto palDefaults = parser.parse_item<mugen::def::DefParseKey::PalDefaults>(kfmdef);
  EXPECT_TRUE(palDefaults);
  if (palDefaults) {
    EXPECT_EQ(palDefaults->size(), 4);
    EXPECT_EQ(palDefaults->operator[](0), 6);
    EXPECT_EQ(palDefaults->operator[](1), 3);
    EXPECT_EQ(palDefaults->operator[](2), 4);
    EXPECT_EQ(palDefaults->operator[](3), 2);
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cmd>(kfmdef), "kfm.cmd");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cns>(kfmdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St>(kfmdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::StCommon>(kfmdef));
  auto stCommon = parser.parse_item<mugen::def::DefParseKey::StCommon>(kfmdef);
  EXPECT_TRUE(stCommon);
  if (stCommon) {
    EXPECT_EQ(*stCommon, "common1.cns");
  }

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
  auto ai = parser.parse_item<mugen::def::DefParseKey::Ai>(kfmdef);
  EXPECT_TRUE(ai);
  if (ai) {
    EXPECT_EQ(*ai, "kfm.ai");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sprite>(kfmdef), "kfm.sff");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(kfmdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Anim>(kfmdef), "kfm.air");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sound>(kfmdef));
  auto sound = parser.parse_item<mugen::def::DefParseKey::Sound>(kfmdef);
  EXPECT_TRUE(sound);
  if (sound) {
    EXPECT_EQ(*sound, "kfm.snd");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal1>(kfmdef));
  auto pal1 = parser.parse_item<mugen::def::DefParseKey::Pal1>(kfmdef);
  EXPECT_TRUE(pal1);
  if (pal1) {
    EXPECT_EQ(*pal1, "kfm6.act");
  }
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal2>(kfmdef));
  auto pal2 = parser.parse_item<mugen::def::DefParseKey::Pal2>(kfmdef);
  EXPECT_TRUE(pal2);
  if (pal2) {
    EXPECT_EQ(*pal2, "kfm4.act");
  }
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal3>(kfmdef));
  auto pal3 = parser.parse_item<mugen::def::DefParseKey::Pal3>(kfmdef);
  EXPECT_TRUE(pal3);
  if (pal3) {
    EXPECT_EQ(*pal3, "kfm2.act");
  }
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal4>(kfmdef));
  auto pal4 = parser.parse_item<mugen::def::DefParseKey::Pal4>(kfmdef);
  EXPECT_TRUE(pal4);
  if (pal4) {
    EXPECT_EQ(*pal4, "kfm5.act");
  }
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal5>(kfmdef));
  auto pal5 = parser.parse_item<mugen::def::DefParseKey::Pal5>(kfmdef);
  EXPECT_TRUE(pal5);
  if (pal5) {
    EXPECT_EQ(*pal5, "kfm3.act");
  }
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal6>(kfmdef));
  auto pal6 = parser.parse_item<mugen::def::DefParseKey::Pal6>(kfmdef);
  EXPECT_TRUE(pal6);
  if (pal6) {
    EXPECT_EQ(*pal6, "kfm.act");
  }

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
  auto intro = parser.parse_item<mugen::def::DefParseKey::Intro>(kfmdef);
  EXPECT_TRUE(intro);
  if (intro) {
    EXPECT_EQ(*intro, "intro.def");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Ending>(kfmdef));
  auto ending = parser.parse_item<mugen::def::DefParseKey::Ending>(kfmdef);
  EXPECT_TRUE(ending);
  if (ending) {
    EXPECT_EQ(*ending, "ending.def");
  }
}

TEST(test_parse_item, parse_win_test) {
  static constexpr std::string_view testdef = "assets/good/test.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Name>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Name>(testdef), "Kung Fu Man");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::DsiplayName>(testdef));
  auto displayName = parser.parse_item<mugen::def::DefParseKey::DsiplayName>(testdef);
  EXPECT_TRUE(displayName);
  if (displayName) {
    EXPECT_EQ(*displayName, "Kung Fu Man");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::VersionDate>(testdef));
  auto versionDate = parser.parse_item<mugen::def::DefParseKey::VersionDate>(testdef);
  EXPECT_TRUE(versionDate);
  if (versionDate) {
    EXPECT_EQ(versionDate->month, 12);
    EXPECT_EQ(versionDate->day, 27);
    EXPECT_EQ(versionDate->year, 2007);
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::MugenVersion>(testdef));
  auto mugenVersion = parser.parse_item<mugen::def::DefParseKey::MugenVersion>(testdef);
  EXPECT_TRUE(mugenVersion);
  if (mugenVersion) {
    EXPECT_EQ(mugenVersion->month, 4);
    EXPECT_EQ(mugenVersion->day, 0);
    EXPECT_EQ(mugenVersion->year, 0);
  }

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Author>(testdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::PalDefaults>(testdef));
  auto palDefaults = parser.parse_item<mugen::def::DefParseKey::PalDefaults>(testdef);
  EXPECT_TRUE(palDefaults);
  if (palDefaults) {
    EXPECT_EQ(palDefaults->size(), 2);
    EXPECT_EQ(palDefaults->operator[](0), 6);
    EXPECT_EQ(palDefaults->operator[](1), 3);
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cmd>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cmd>(testdef), "kfm.cmd");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Cns>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Cns>(testdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::St>(testdef), "kfm.cns");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::StCommon>(testdef));
  auto stCommon = parser.parse_item<mugen::def::DefParseKey::StCommon>(testdef);
  EXPECT_TRUE(stCommon);
  if (stCommon) {
    EXPECT_EQ(*stCommon, "common.cns");
  }

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St0>(testdef), mugen::def::MissingKeyError);
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St1>(testdef), mugen::def::MissingKeyError);
  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::St2>(testdef));
  auto st2 = parser.parse_item<mugen::def::DefParseKey::St2>(testdef);
  EXPECT_TRUE(st2);
  if (st2) {
    EXPECT_EQ(*st2, "2.st");
  }
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
  auto st8 = parser.parse_item<mugen::def::DefParseKey::St8>(testdef);
  EXPECT_TRUE(st8);
  if (st8) {
    EXPECT_EQ(*st8, "8.st");
  }
  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::St9>(testdef), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse_item<mugen::def::DefParseKey::Ai>(testdef));
  EXPECT_THROW(parser.parse_item<mugen::def::DefParseKey::Ai>(testdef), mugen::def::MissingKeyError);

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sprite>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Sprite>(testdef), "kfm.pcx");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Anim>(testdef));
  EXPECT_EQ(parser.parse_item<mugen::def::DefParseKey::Anim>(testdef), "anim.st");

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Sound>(testdef));
  auto sound = parser.parse_item<mugen::def::DefParseKey::Sound>(testdef);
  EXPECT_TRUE(sound);
  if (sound) {
    EXPECT_EQ(*sound, "");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Pal1>(testdef));
  auto pal1 = parser.parse_item<mugen::def::DefParseKey::Pal1>(testdef);
  EXPECT_TRUE(pal1);
  if (pal1) {
    EXPECT_EQ(*pal1, "kfm.act");
  }
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
  auto intro = parser.parse_item<mugen::def::DefParseKey::Intro>(testdef);
  EXPECT_TRUE(intro);
  if (intro) {
    EXPECT_EQ(*intro, "intro.def");
  }

  EXPECT_NO_THROW(parser.parse_item<mugen::def::DefParseKey::Ending>(testdef));
  auto ending = parser.parse_item<mugen::def::DefParseKey::Ending>(testdef);
  EXPECT_TRUE(ending);
  if (ending) {
    EXPECT_EQ(*ending, "ending.def");
  }
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
