// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_RESULTSPRINTER_HPP_
#define INCLUDE_RESULTSPRINTER_HPP_

#include <Experiment.hpp>
#include <ostream>
#include <vector>

class ResultsPrinter {
 public:
  virtual ~ResultsPrinter() = default;
  virtual void Print(const std::vector<Experiment::ExperimentResult> &,
                     std::ostream &out) = 0;
};

#endif  // INCLUDE_RESULTSPRINTER_HPP_
