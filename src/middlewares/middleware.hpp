#pragma once
#include <crow.h>


struct BaseMiddleware{

  struct context{};
   void before_handle(crow::request& req, crow::response& res, context& ctx)
    {
     
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx)
    {}

};
