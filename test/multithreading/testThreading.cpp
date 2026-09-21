
#include <iostream>
#include <thread>
#include <chrono>



extern void Function();

static void sleepForWhile(std::size_t N)
{
    std::cout << "Waiting..." << '\n';
    std::this_thread::sleep_for (std::chrono::seconds(N));
}



int main()
{

    {
        std::size_t data =
        #include "data.inc"
            ;

        std::cout << data << '\n';
    }



    int sum = 0;
    volatile bool isRunning = true;
    while (isRunning)
    {
        sum += 10;
        if (sum == 100)
            break;
    }


    std::cout << sum << '\n';


    return 0;

}

