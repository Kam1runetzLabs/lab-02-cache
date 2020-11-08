// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <CSVPrinter.hpp>
#include <vector>

void CSVPrinter::Print(const std::vector<Experiment::ExperimentResult>& results,
                       std::ostream& out) {
  if (results.empty()) {
    out << "No experiments results" << std::endl;
    return;
  }
  out << results.front().TravelOrder << "; ;" << std::endl;
  for (auto& result : results) {
    out << ";" << result.BufferSize / 1024 << ";" << result.Duration
        << std::endl;
  }
}
