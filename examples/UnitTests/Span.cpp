
#include <span>
void Span(char C) {
  std::span<char>{&C, 1};
}
