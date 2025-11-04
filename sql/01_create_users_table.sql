CREATE TABLE users(
    id SERIAL PRIMARY KEY,
    email varchar(128) NOT NULL,
    password varchar(128) NOT NULL,
    f_name varchar(64),
    l_name varchar(64),
    is_verified BOOLEAN
);