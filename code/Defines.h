#pragma once

#ifndef DEFINES
#define DEFINES

// C++ built-in
#include <iostream>
#include <stdint.h>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>

/// Using
using str_view      = std::string_view;
using str           = std::string;
using i8            = std::uint8_t;
using i16           = std::uint16_t;
using i32           = std::uint32_t;
using size          = size_t;
template<typename T>
using vector        = std::vector<T>;
template<typename K, typename V>
using un_map        = std::unordered_map<K, V>; 


#endif