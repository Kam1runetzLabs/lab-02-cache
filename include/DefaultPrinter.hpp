//
// Created by w1ckedente on 25.10.2020.
//

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
