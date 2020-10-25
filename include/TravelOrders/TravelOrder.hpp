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
        currentBufferIndex(aCurrentIndex), bufferSize(0) {}
  virtual ~TravelOrder() = default;

  virtual std::size_t GetNextIndex() = 0;

  virtual std::string TravelOrderName() const { return travelOrderName; }

  virtual void SetDefaultIndex() = 0;

  virtual void SetBufferSize(std::size_t buffSize) { bufferSize = buffSize; };

 protected:
  std::string travelOrderName;
  std::size_t currentBufferIndex;
  std::size_t bufferSize;
};

#endif  // CACHE_TRAVELORDER_HPP
