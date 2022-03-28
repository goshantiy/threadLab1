#include <iostream>
#include <thread>
#include <vector>
#include <random>
void generate(size_t MOD,size_t DIV,std::vector<size_t> &Array,size_t thread,size_t threadSize)
{
    std::uniform_int_distribution<> uid(1, 100);
    std::random_device rd;
    for (size_t i = thread * MOD; i < MOD * (thread + 1); i++)
        Array[i] = uid(rd);
    size_t index = MOD * threadSize + thread;
    if((index<Array.size()&&DIV))
        Array[index]= uid(rd);
}
int main()
{
    size_t arraySize = 0;
    std::cout << "Enter array size:\n";
    std::cin >> arraySize;

    size_t threadSize = 0;
    std::cout << "Enter threads number:\n";
    std::cin >> threadSize;
  
    std::vector<size_t> array;
    array.resize(arraySize);

    std::vector<std::thread> threads;
    threads.reserve(threadSize);

   const size_t mod = arraySize / threadSize;
   const size_t div = arraySize % threadSize;
   for (size_t i = 0; i < threadSize; i++)
       threads.push_back(std::thread(generate, mod, div, ref(array), i,threadSize));
   for (size_t i = 0; i < threadSize; i++)
       if (threads.at(i).joinable())
           threads.at(i).join();
   std::cout << "Generated array size = " << array.size() << std::endl;
   for (const auto& it : array)
   {
       std::cout << it << ' ';
   }
   return 0;
}

