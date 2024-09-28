/**
 * @file parse.cpp
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

TEST(test_parse, common_parse_error) {
  auto parser = mugen::def::DefParserWin{};
  EXPECT_ANY_THROW(parser.parse(NOT_EXISTING_FILE));
  EXPECT_THROW(parser.parse(NOT_EXISTING_FILE), mugen::def::FileIOError);
}

TEST(test_parse, parse_win_kfm) {
  static constexpr std::string_view kfmdef = "assets/good/kfm.def"sv;

  auto parser = mugen::def::DefParserWin{};
  ASSERT_NO_THROW(parser.parse(kfmdef));
  try {
    auto def = parser.parse(kfmdef);

    EXPECT_EQ(def.info.name, "Kung Fu Man");

    EXPECT_TRUE(def.info.displayName);
    if (def.info.displayName) {
      EXPECT_EQ(*(def.info.displayName), "Kung Fu Man");
    }

    EXPECT_TRUE(def.info.versionDate);
    if (def.info.versionDate) {
      EXPECT_EQ((def.info.versionDate)->month, 12);
      EXPECT_EQ((def.info.versionDate)->day, 27);
      EXPECT_EQ((def.info.versionDate)->year, 2007);
    }

    EXPECT_TRUE(def.info.mugenVersion);
    if (def.info.mugenVersion) {
      EXPECT_EQ((def.info.mugenVersion)->month, 4);
      EXPECT_EQ((def.info.mugenVersion)->day, 14);
      EXPECT_EQ((def.info.mugenVersion)->year, 2002);
    }

    EXPECT_TRUE(def.info.author);
    if (def.info.author) {
      EXPECT_EQ(*(def.info.author), "Elecbyte");
    }

    EXPECT_TRUE(def.info.palDefaults);
    if (def.info.palDefaults) {
      EXPECT_EQ((def.info.palDefaults)->size(), 4);
      EXPECT_EQ((*(def.info.palDefaults))[0], 6);
      EXPECT_EQ((*(def.info.palDefaults))[1], 3);
      EXPECT_EQ((*(def.info.palDefaults))[2], 4);
      EXPECT_EQ((*(def.info.palDefaults))[3], 2);
    }

    EXPECT_EQ(def.files.cmd, "kfm.cmd");

    EXPECT_EQ(def.files.cns, "kfm.cns");

    EXPECT_EQ(def.files.st, "kfm.cns");

    EXPECT_TRUE(def.files.stcommon);
    if (def.files.stcommon) {
      EXPECT_EQ(*(def.files.stcommon), "common1.cns");
    }

    EXPECT_EQ(def.files.sprite, "kfm.sff");

    EXPECT_EQ(def.files.anim, "kfm.air");

    EXPECT_TRUE(def.files.sound);
    if (def.files.sound) {
      EXPECT_EQ(*(def.files.sound), "kfm.snd");
    }

    EXPECT_TRUE(def.files.pal1);
    if (def.files.pal1) {
      EXPECT_EQ(*(def.files.pal1), "kfm6.act");
    }

    EXPECT_TRUE(def.files.pal2);
    if (def.files.pal2) {
      EXPECT_EQ(*(def.files.pal2), "kfm4.act");
    }

    EXPECT_TRUE(def.files.pal3);
    if (def.files.pal3) {
      EXPECT_EQ(*(def.files.pal3), "kfm2.act");
    }

    EXPECT_TRUE(def.files.pal4);
    if (def.files.pal4) {
      EXPECT_EQ(*(def.files.pal4), "kfm5.act");
    }

    EXPECT_TRUE(def.files.pal5);
    if (def.files.pal5) {
      EXPECT_EQ(*(def.files.pal5), "kfm3.act");
    }

    EXPECT_TRUE(def.files.pal6);
    if (def.files.pal6) {
      EXPECT_EQ(*(def.files.pal6), "kfm.act");
    }

    EXPECT_TRUE(def.files.ai);
    if (def.files.ai) {
      EXPECT_EQ(*(def.files.ai), "kfm.ai");
    }

    EXPECT_TRUE(def.arcade.intro);
    if (def.arcade.intro) {
      EXPECT_EQ(*(def.arcade.intro), "intro.def");
    }

    EXPECT_TRUE(def.arcade.ending);
    if (def.arcade.ending) {
      EXPECT_EQ(*(def.arcade.ending), "ending.def");
    }

    EXPECT_FALSE(def.files.st0);
    EXPECT_FALSE(def.files.st1);
    EXPECT_FALSE(def.files.st2);
    EXPECT_FALSE(def.files.st3);
    EXPECT_FALSE(def.files.st4);
    EXPECT_FALSE(def.files.st5);
    EXPECT_FALSE(def.files.st6);
    EXPECT_FALSE(def.files.st7);
    EXPECT_FALSE(def.files.st8);
    EXPECT_FALSE(def.files.st9);
    EXPECT_FALSE(def.files.pal7);
    EXPECT_FALSE(def.files.pal8);
    EXPECT_FALSE(def.files.pal9);
    EXPECT_FALSE(def.files.pal10);
    EXPECT_FALSE(def.files.pal11);
    EXPECT_FALSE(def.files.pal12);
  } catch (...) {
    ASSERT_TRUE(false);
  }
}

TEST(test_parse, parse_win_test) {
  static constexpr std::string_view testdef = "assets/good/test.def"sv;
  auto parser = mugen::def::DefParserWin{};
  EXPECT_NO_THROW(parser.parse(testdef));
  try {
    auto def = parser.parse(testdef);

    EXPECT_EQ(def.info.name, "Kung Fu Man");

    EXPECT_TRUE(def.info.displayName);
    if (def.info.displayName) {
      EXPECT_EQ(*(def.info.displayName), "Kung Fu Man");
    }

    EXPECT_TRUE(def.info.versionDate);
    if (def.info.versionDate) {
      EXPECT_EQ((def.info.versionDate)->month, 12);
      EXPECT_EQ((def.info.versionDate)->day, 27);
      EXPECT_EQ((def.info.versionDate)->year, 2007);
    }

    EXPECT_TRUE(def.info.mugenVersion);
    if (def.info.mugenVersion) {
      EXPECT_EQ((def.info.mugenVersion)->month, 4);
      EXPECT_EQ((def.info.mugenVersion)->day, 0);
      EXPECT_EQ((def.info.mugenVersion)->year, 0);
    }

    EXPECT_TRUE(def.info.palDefaults);
    if (def.info.palDefaults) {
      EXPECT_EQ((def.info.palDefaults)->size(), 2);
      EXPECT_EQ((*(def.info.palDefaults))[0], 6);
      EXPECT_EQ((*(def.info.palDefaults))[1], 3);
    }

    EXPECT_EQ(def.files.cmd, "kfm.cmd");

    EXPECT_EQ(def.files.cns, "kfm.cns");

    EXPECT_EQ(def.files.st, "kfm.cns");

    EXPECT_TRUE(def.files.st2);
    if (def.files.st2) {
      EXPECT_EQ(*(def.files.st2), "2.st");
    }

    EXPECT_TRUE(def.files.st8);
    if (def.files.st8) {
      EXPECT_EQ(*(def.files.st8), "8.st");
    }

    EXPECT_TRUE(def.files.stcommon);
    if (def.files.stcommon) {
      EXPECT_EQ(*(def.files.stcommon), "common.cns");
    }

    EXPECT_EQ(def.files.sprite, "kfm.pcx");

    EXPECT_EQ(def.files.anim, "anim.st");

    EXPECT_TRUE(def.files.sound);
    if (def.files.sound) {
      EXPECT_EQ(*(def.files.sound), "");
    }

    EXPECT_TRUE(def.files.pal1);
    if (def.files.pal1) {
      EXPECT_EQ(*(def.files.pal1), "kfm.act");
    }

    EXPECT_TRUE(def.arcade.intro);
    if (def.arcade.intro) {
      EXPECT_EQ(*(def.arcade.intro), "intro.def");
    }

    EXPECT_TRUE(def.arcade.ending);
    if (def.arcade.ending) {
      EXPECT_EQ(*(def.arcade.ending), "ending.def");
    }

    EXPECT_FALSE(def.info.author);
    EXPECT_FALSE(def.files.st0);
    EXPECT_FALSE(def.files.st1);
    EXPECT_FALSE(def.files.st3);
    EXPECT_FALSE(def.files.st4);
    EXPECT_FALSE(def.files.st5);
    EXPECT_FALSE(def.files.st6);
    EXPECT_FALSE(def.files.st7);
    EXPECT_FALSE(def.files.st9);
    EXPECT_FALSE(def.files.ai);
    EXPECT_FALSE(def.files.pal2);
    EXPECT_FALSE(def.files.pal3);
    EXPECT_FALSE(def.files.pal4);
    EXPECT_FALSE(def.files.pal5);
    EXPECT_FALSE(def.files.pal6);
    EXPECT_FALSE(def.files.pal7);
    EXPECT_FALSE(def.files.pal8);
    EXPECT_FALSE(def.files.pal9);
    EXPECT_FALSE(def.files.pal10);
    EXPECT_FALSE(def.files.pal11);
    EXPECT_FALSE(def.files.pal12);
  } catch (...) {
    ASSERT_TRUE(false);
  }
}

TEST(test_parse, missing_win) {
  static constexpr std::string_view missing_anim_def = "assets/bad/missing_anim.def"sv;
  static constexpr std::string_view missing_cmd_def = "assets/bad/missing_cmd.def"sv;
  static constexpr std::string_view missing_cns_def = "assets/bad/missing_cns.def"sv;
  static constexpr std::string_view missing_name_def = "assets/bad/missing_name.def"sv;
  static constexpr std::string_view missing_sprite_def = "assets/bad/missing_sprite.def"sv;
  static constexpr std::string_view missing_st_def = "assets/bad/missing_st.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_ANY_THROW(parser.parse(missing_anim_def));
  EXPECT_THROW(parser.parse(missing_anim_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse(missing_cmd_def));
  EXPECT_THROW(parser.parse(missing_cmd_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse(missing_cns_def));
  EXPECT_THROW(parser.parse(missing_cns_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse(missing_name_def));
  EXPECT_THROW(parser.parse(missing_name_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse(missing_sprite_def));
  EXPECT_THROW(parser.parse(missing_sprite_def), mugen::def::MissingKeyError);

  EXPECT_ANY_THROW(parser.parse(missing_st_def));
  EXPECT_THROW(parser.parse(missing_st_def), mugen::def::MissingKeyError);
}

TEST(test_parse, unquoted_win) {
  static constexpr std::string_view unquoted_name = "assets/bad/unquoted_name.def"sv;
  static constexpr std::string_view unquoted_displayname = "assets/bad/unquoted_displayname.def"sv;
  static constexpr std::string_view unquoted_author = "assets/bad/unquoted_author.def"sv;

  auto parser = mugen::def::DefParserWin{};

  EXPECT_ANY_THROW(parser.parse(unquoted_name));
  EXPECT_THROW(parser.parse(unquoted_name), mugen::def::DequotationError);

  EXPECT_ANY_THROW(parser.parse(unquoted_displayname));
  EXPECT_THROW(parser.parse(unquoted_displayname), mugen::def::DequotationError);

  EXPECT_ANY_THROW(parser.parse(unquoted_author));
  EXPECT_THROW(parser.parse(unquoted_author), mugen::def::DequotationError);
}
