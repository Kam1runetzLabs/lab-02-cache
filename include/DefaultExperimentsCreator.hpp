//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_DEFAULTEXPERIMENTSCREATOR_HPP
#define CACHE_DEFAULTEXPERIMENTSCREATOR_HPP

#include <Experiment.hpp>
#include <ExperimentsCreator.hpp>
#include <vector>

class DefaultExperimentsCreator : public ExperimentsCreator {
 public:
  DefaultExperimentsCreator(std::size_t minCacheSize, std::size_t maxCacheSize);
  std::vector<Experiment> CreateExperiments() override;

  std::size_t GetMaxBufferSize() const override;
 private:
  std::size_t maxBufferSize;
};

#endif  // CACHE_DEFAULTEXPERIMENTSCREATOR_HPP
