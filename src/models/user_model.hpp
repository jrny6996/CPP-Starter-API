#pragma once
#include <string>
#include "../include/bcrypt/include/bcrypt.h"

class User{
    private:
    std::string password;
    public:
        std::string email;
        
        User(){
         return;   
        }
        bool check_exists(){
            return false;
        };
};


struct EmailCheck{
  bool status;
  std::optional<pqxx::result> result;
};

EmailCheck check_exists(std::string email) {
  DbConnection conn;
  std::vector<std::string> args {email};
  pqxx::connection cx = conn.get_connection();
  pqxx::work tx {cx};
  pqxx::result r = tx.exec_params(
        "SELECT 1 FROM users WHERE email = $1 LIMIT 1",
        email
    );
  if(r.empty()){
    return {false, std::nullopt};
  }else{
    EmailCheck check {true, r};
    return check;
  }
  
}

std::string hash_with_secret(std::string to_hash) {
  std::string hashed;

  return to_hash;
}
