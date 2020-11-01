// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

/*!
 * @file
 * @brief Конфигурационный файл, содержащий константы, необходимые для работы
 * программы
 * */

#ifndef INCLUDE_CONFIG_HPP_
#define INCLUDE_CONFIG_HPP_

#include <cctype>

const std::size_t CacheLineSize = 64;
const std::size_t IterationsCount = 1000;
[[maybe_unused]] const auto MyL1dCacheSize = 64 * 1024;
[[maybe_unused]] const auto MyL2CacheSize = 512 * 1024;
[[maybe_unused]] const auto MyL3CacheSize = 3 * 1024 * 1024;

#endif  // INCLUDE_CONFIG_HPP_
