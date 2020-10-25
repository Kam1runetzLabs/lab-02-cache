//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_CONFIG_H
#define CACHE_CONFIG_H

#include <cctype>

const std::size_t CacheLineSize = 64;
const std::size_t IterationsCount = 1000;
const auto MyL1dCacheSize = 64 * 1024;
const auto MyL3CacheSize = 3 * 1024 * 1024;

#endif  // CACHE_CONFIG_H
