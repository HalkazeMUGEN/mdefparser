/**
 * @file exception.hpp
 * @author Halkaze
 * @date 2024-10-13
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

#ifndef MDEFPARSER_EXCEPTION_HPP__
#define MDEFPARSER_EXCEPTION_HPP__

#include "mdefparser/mdefparser.h"

#include <stdexcept>
#include <string>

namespace mugen {
namespace def {

class FileIOError : public std::runtime_error {
 public:
  explicit FileIOError(const std::string& message) noexcept : std::runtime_error{message} {}
  explicit FileIOError(const char* message) noexcept : std::runtime_error{message} {}
};

class DequotationError : public std::runtime_error {
 public:
  explicit DequotationError(const std::string& message) noexcept : std::runtime_error{message} {}
  explicit DequotationError(const char* message) noexcept : std::runtime_error{message} {}
};

class MissingKeyError : public std::runtime_error {
 public:
  explicit MissingKeyError(const std::string& message) noexcept : std::runtime_error{message} {}
  explicit MissingKeyError(const char* message) noexcept : std::runtime_error{message} {}
};

};  // namespace def
};  // namespace mugen

#endif  // MDEFPARSER_EXCEPTION_HPP__
