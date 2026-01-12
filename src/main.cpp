#include <fmt/format.h>
#include <memory>
#include <string>
#include <thread>
#include "controllers/user_controller.hpp"
#include "crow.h"
#include "include/dotenv.h"
#include "middlewares/middleware.hpp"
#include "services/db_connect.hpp"
int main(int argc, char* argv[]) {
  try {
    dotenv::init();

    std::string scaffold =
        "CREATE TABLE users(id SERIAL PRIMARY KEY, email varchar(128) NOT "
        "NULL, "
        "password varchar(128) NOT NULL,f_name varchar(64), l_name "
        "varchar(64), "
        "is_verified BOOLEAN); ";
    DbConnection db;
    try {

      db.exec(scaffold);
    } catch (std::exception& e) {
      std::string err_str = fmt::format("Err {}", e.what());
      std::cout << err_str << "\n";
    }

    crow::App<BaseMiddleware> app;

    create_user_route(app);
    CROW_ROUTE(app, "/")([]() {
      auto page = crow::mustache::load("index.html");
      return page.render();
    });

    app.port(18080).multithreaded().run();

  } catch (std::exception& e) {
    std::string err_str = fmt::format("Err {}", e.what());
    std::cout << err_str << "\n";
  }
}
