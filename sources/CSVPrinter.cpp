//
// Created by w1ckedente on 08.11.2020.
//
#include <CSVPrinter.hpp>

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
