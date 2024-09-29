#include <mdefparser/mdefparser.h>

#include <filesystem>
#include <iostream>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path-to-def>" << std::endl;
    return 0;
  }

  auto parser = mugen::def::DefParserWin{};
  // auto parser = mugen::def::DefParser<mugen::def::MugenVersion::Win>;

  std::filesystem::path path{argv[1]};

  // Parse all params
  try {
    auto def = parser.parse(path);

    // Example.1: get required parameter
    std::cout << "name: " << def.info.name << std::endl;

    // Example.2: get optional parameter
    if (def.info.displayName.has_value()) {
      std::cout << "displayname: " << def.info.displayName.value() << std::endl;
    } else {
      std::cout << "displayname: (null)" << std::endl;
    }

    // Example.3: get version parameter
    if (def.info.mugenVersion.has_value()) {
      auto version = def.info.mugenVersion.value();
      std::cout << "mugenversion: " << version.month << "." << version.day << "." << version.year << std::endl;
    } else {
      std::cout << "mugenversion: (null)" << std::endl;
    }

    // Example.4: get vector parameter
    if (def.info.palDefaults.has_value()) {
      auto palDefaults = def.info.palDefaults.value();
      std::cout << "pal.defaults:";
      for (auto pal : palDefaults) {
        std::cout << " " << pal;
      }
      std::cout << std::endl;
    }

  } catch (const mugen::def::FileIOError& e) {
    // Throw FileIOError if path is not exist
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const mugen::def::MissingKeyError& e) {
    // Throw MissingKeyError if def has not required parameter
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const mugen::def::DequotationError& e) {
    // Throw DequotationError if dequotation failed
    std::cerr << e.what() << std::endl;
    return 1;
  }
  // All errors are sub class of std::runtime_error

  // Parse single param
  try {
    auto sff = parser.parse_item<mugen::def::DefParseKey::Sprite>(path);

    std::cout << "sprite: " << sff.filename().string() << std::endl;

  } catch (const mugen::def::FileIOError& e) {
    // Throw FileIOError if path is not exist
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const mugen::def::MissingKeyError& e) {
    // Throw MissingKeyError if def has not parameter specified DefParseKey
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const mugen::def::DequotationError& e) {
    // Throw DequotationError if dequotation failed
    // (Thrown only if key is Name, DisplayName, or Author)
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
