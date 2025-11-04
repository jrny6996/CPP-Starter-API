npx @tailwindcss/cli -i ./src/static/css/input.css -o ./src/static/css/output.css --watch

cd build/ && cmake ..  && make && ./Server