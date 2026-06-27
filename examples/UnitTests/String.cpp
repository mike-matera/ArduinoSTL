#include<string>
void String()
{
  std::string S;
  S.resize_and_overwrite(10,[](char*Pointer,size_t Capacity){
    return Capacity;
  });
}