// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

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
