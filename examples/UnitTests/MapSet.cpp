
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <functional>
//move_only_function的指针比较特殊，容易出错

void MapSet()
{
  std::map<std::move_only_function<void()const>*,char>M;
  M.contains(0);
  M.erase(0);
  std::set<std::move_only_function<void()const>*>S;
  S.contains(0);
  S.erase(0);
  std::unordered_map<std::move_only_function<void()const>*,char>UM;
  UM.contains(0);
  UM.erase(0);
  std::unordered_set<std::move_only_function<void()const>*>US;
  US.contains(0);
  US.erase(0);
}
