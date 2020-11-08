//
// Created by w1ckedente on 08.11.2020.
//

#ifndef CACHE_CSVPRINTER_HPP
#define CACHE_CSVPRINTER_HPP

#include <Experiment.hpp>
#include <ResultsPrinter.hpp>

class CSVPrinter : public ResultsPrinter {
  void Print(const std::vector<Experiment::ExperimentResult> &results,
             std::ostream &out) override;
};

#endif  // CACHE_CSVPRINTER_HPP
