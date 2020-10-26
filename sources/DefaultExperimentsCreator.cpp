// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <DefaultExperimentsCreator.hpp>
#include <Experiment.hpp>
#include <vector>

DefaultExperimentsCreator::DefaultExperimentsCreator(std::size_t minCacheSize,
                                                       std::size_t maxCacheSize)
    : ExperimentsCreator(minCacheSize, 0, maxCacheSize), maxBufferSize() {}

std::vector<Experiment> DefaultExperimentsCreator::CreateExperiments() {
  std::vector<Experiment> result;
  for (auto i = L1CacheSize / 2; i < L3CacheSize; i *= 2)
    result.emplace_back(Experiment(nullptr, i));
  result.emplace_back(Experiment(nullptr, L3CacheSize / 2 * 3));
  maxBufferSize = L3CacheSize / 2 * 3;
  return result;
}
std::size_t DefaultExperimentsCreator::GetMaxBufferSize() const {
  return maxBufferSize;
}
