//
// Created by w1ckedente on 25.10.2020.
//

#ifndef CACHE_RESULTSPRINTER_HPP
#define CACHE_RESULTSPRINTER_HPP

#include <Experiment.hpp>
#include <vector>
#include <ostream>

class ResultsPrinter {
 public:
  virtual ~ResultsPrinter() = default;
  virtual void Print(std::vector<Experiment::ExperimentResult>, std::ostream &out) = 0;
};

#endif  // CACHE_RESULTSPRINTER_HPP
