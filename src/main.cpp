#include <memory>
#include <string>
#include <thread>
#include "controllers/user_controller.hpp"
#include "crow.h"
#include "dev_utils/ongoing_processes.hpp"
#include "include/dotenv.h"
#include "middlewares/middleware.hpp"
#include "services/db_connect.hpp"
#include <fmt/format.h>
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

  std::string scaffold =
      "CREATE TABLE users(id SERIAL PRIMARY KEY, email varchar(128) NOT NULL, "
      "password varchar(128) NOT NULL,f_name varchar(64), l_name varchar(64), "
      "is_verified BOOLEAN); ";
  DbConnection db;
  try {

    db.exec(scaffold);
  } catch (std::exception& e) {
    std::string  err_str = fmt::format("Err {}", e.what());
    std::cout << err_str << "\n";
  }

  crow::App<BaseMiddleware> app;

  create_user_route(app);
  CROW_ROUTE(app, "/")([]() {
    auto page = crow::mustache::load("index.html");
    return page.render();
  });

  if (is_dev) {
    app.port(18080).run();
  } else {
    app.port(18080).multithreaded().run();
  }
}
