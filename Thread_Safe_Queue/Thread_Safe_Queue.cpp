#include <iostream>
#include "thread_pool.h"

void fun1()
{
    std::cout << "fun1 " << std::endl;
}

void fun2()
{
    std::cout << "fun2 " << std::endl;
}

int main()
{
    thread_pool thrPool;

    while (true) 
    {
        thrPool.submit(fun1);
        thrPool.submit(fun2);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
