// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_DEFAULTPRINTER_HPP_
#define CACHE_DEFAULTPRINTER_HPP_

#include <Experiment.hpp>
#include <ResultsPrinter.hpp>
#include <ostream>
#include <vector>

class DefaultPrinter : public ResultsPrinter {
  void Print(std::vector<Experiment::ExperimentResult>,
             std::ostream &out) override;
};

#endif  // CACHE_DEFAULTPRINTER_HPP_
