#include <iterator>
struct Module;
struct Sequential {
  Module* const Array[1] = { nullptr };
  Module* const* It = std::cend(Array);
};
void Iterator()
{
  Sequential S;
};