// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_EXPERIMENTSCREATOR_HPP
#define CACHE_EXPERIMENTSCREATOR_HPP

#include <Experiment.hpp>
#include <vector>

class ExperimentsCreator {
 public:
  ExperimentsCreator([[maybe_unused]] std::size_t aL1CacheSize,
                     [[maybe_unused]] std::size_t aL2CacheSize,
                     [[maybe_unused]] std::size_t aL3CacheSize)
      : L1CacheSize(aL1CacheSize),
        L2CacheSize(aL2CacheSize),
        L3CacheSize(aL3CacheSize) {}
  virtual ~ExperimentsCreator() = default;
  virtual std::vector<Experiment> CreateExperiments() = 0;
  virtual std::size_t GetMaxBufferSize() const = 0;

 protected:
  std::size_t L1CacheSize;
  std::size_t L2CacheSize;
  std::size_t L3CacheSize;
};

#endif  // CACHE_EXPERIMENTSCREATOR_HPP
