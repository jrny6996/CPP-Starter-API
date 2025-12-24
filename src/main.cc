#include <string>
#include <thread>
#include "crow.h"
#include "dev_utils/ongoing_processes.hpp"
#include "include/dotenv.h"
#include "services/db_connect.hpp"

int main(int argc, char* argv[]) {
    dotenv::init();


  std::cout << argv[1] << "\n";
  std::string dev_cmd = "dev";
  // crow::Blueprint api {"api"};
  bool is_dev = false;
  if (argv[1] == dev_cmd) {
    run_dev();
    is_dev = true;
  }

    std::string scaffold = "CREATE TABLE users(id SERIAL PRIMARY KEY, email varchar(128) NOT NULL, password varchar(128) NOT NULL,f_name varchar(64), l_name varchar(64), is_verified BOOLEAN); ";
    DbConnection db;
    db.exec(scaffold);


  crow::SimpleApp app;  // define your crow application
  CROW_ROUTE(app, "/")([]() {
    auto page = crow::mustache::load("index.html");
    return page.render();
  });

  CROW_ROUTE(app, "/api/example")([]() { return "Hello world"; });

  // set the port, set the app to run on multiple threads, and run the app
  if (is_dev) {
    app.port(18080).run();
  } else {
    app.port(18080).multithreaded().run();
  }
}
