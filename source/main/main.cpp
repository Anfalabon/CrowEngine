
#include "Application.hpp"



int main()
{


    CrowEngine::Application application;

    application.Start();
    application.Run();
    application.Stop(); //right now Stop() function does nothing

    return 0;
}
