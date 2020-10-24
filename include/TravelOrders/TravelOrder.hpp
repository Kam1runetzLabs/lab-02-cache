//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_TRAVELORDER_HPP
#define CACHE_TRAVELORDER_HPP

#include <string>
#include <utility>

class TravelOrder {
 public:
  TravelOrder(std::string aTravelOrderName, std::size_t aCurrentIndex)
      : travelOrderName(std::move(aTravelOrderName)),
        currentBufferIndex(aCurrentIndex) {}
  virtual ~TravelOrder() = default;

  virtual std::size_t GetNextIndex() = 0;

  virtual std::string TravelOrderName() const { return travelOrderName; }

 protected:
  std::string travelOrderName;
  std::size_t currentBufferIndex;
};

#endif  // CACHE_TRAVELORDER_HPP
