#include "crow.h"
#include <thread>
void spin_up_tailwind_watch(){
    std::string watch_cmd = "npx @tailwindcss/cli -i ../src/static/css/input.css -o ../src/static/css/output.css --watch";
    system(watch_cmd.c_str());
    
    while (true)
    {
        continue;
    }
    
    return;
}



int main()
{
    std::thread t(spin_up_tailwind_watch); 
    crow::SimpleApp app; //define your crow application
    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/api/example")([](){
        return "Hello world";
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}
