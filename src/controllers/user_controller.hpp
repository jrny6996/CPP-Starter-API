#pragma once
#include <crow.h>
#include <string>
#include "../models/user_model.hpp" 
#include <fmt/format.h>
#include "../middlewares/middleware.hpp"
#include <crow/http_request.h>
#include <sodium.h>


bool check_exists(std::string email) {
  return false;
}

bool insert_user(std::string email, std::string hashed_pw) {
  return true;
}

std::string hash_with_secret(std::string to_hash) {
  std::string hashed;

  return to_hash;
}

std::string user_onboarding(const crow::query_string params) {
  std::string status_str = "n/a";

  char* email = params.get("email");
  char* pw = params.get("password");
  if (!email || !pw) {
    return "Missing required fields";
  }

  if (check_exists(email)) {
    status_str = "User already exists";
  } else {
    std::string hashed_pw = hash_with_secret(pw);
    insert_user(email, hashed_pw);
    status_str = "Creating new user in DB";
  }
  return status_str;
}

void create_user_route(crow::Crow<BaseMiddleware>& app) {

  CROW_ROUTE(app, "/api/users")
      .methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        crow::HTTPMethod method = req.method;
        std::string msg = "n/a";
        if (crow::method_name(method) == "POST") {
          auto params = req.get_body_params();
          CROW_LOG_INFO << params;
          msg = user_onboarding(params);
        }
        std::string body = fmt::format("<h1>User performed {}</h1><h3>{}</h3> ",
                                       crow::method_name(method), msg);

        CROW_LOG_INFO << "Content-Type: "
                      << req.get_header_value("Content-Type");
        CROW_LOG_INFO << "Raw body: " << req.body;

        return body;
      });
  CROW_ROUTE(app, "/login")([]() {
    auto page = crow::mustache::load("partials/_login_form.html");
    return page.render();
  });
  return;
}