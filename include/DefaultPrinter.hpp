// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_DEFAULTPRINTER_HPP
#define CACHE_DEFAULTPRINTER_HPP

#include <Experiment.hpp>
#include <ResultsPrinter.hpp>
#include <vector>
#include <ostream>

class DefaultPrinter : public ResultsPrinter {
  void Print(std::vector<Experiment::ExperimentResult>, std::ostream &out) override;
};

#endif  // CACHE_DEFAULTPRINTER_HPP
