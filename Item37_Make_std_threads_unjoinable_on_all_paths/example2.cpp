#include "ThreadRAII.h"
#include "utils.h"

constexpr auto tenMillion = 10000000;       // C++14


bool doWork(std::function<bool(int)> filter,  // as before
            int maxVal = tenMillion)
{
  std::vector<int> goodVals;                  // as before

  ThreadRAII t(
    std::thread([&filter, maxVal, &goodVals]
                {
                  for (auto i = 0; i <= maxVal; ++i)
                   { if (filter(i)) goodVals.push_back(i); }
                }),
                ThreadRAII::DtorAction::join  // RAII action
  );

  auto nh = t.get().native_handle();
  // ...

  if (conditionsAreSatisfied()) {
    t.get().join();
    performComputation(goodVals);
    return true;
  }

  return false;
}

int main()
{
    std::function<bool(int)> filter = someFilter;
    doWork(filter, 10);
}
