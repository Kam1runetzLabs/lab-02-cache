// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <cctype>

const std::size_t CacheLineSize = 64;
const std::size_t IterationsCount = 1000;
const auto MyL1dCacheSize = 64 * 1024;
const auto MyL3CacheSize = 3 * 1024 * 1024;
[[maybe_unused]] const auto GCC_PrefetchEnable = true;

#endif  // INCLUDE_CONFIG_H_
