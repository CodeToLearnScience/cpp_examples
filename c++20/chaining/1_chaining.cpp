// import<ranges>;
#include <ranges>
#include <vector>

auto main() -> int {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto resuls = {
      v | views::filter([](const auto &value) { return value % 2 == 0; })};
  return 0;
}