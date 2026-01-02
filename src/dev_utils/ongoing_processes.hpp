#pragma once

#include <atomic>
#include <cstdlib>
#include <string>
#include <sys/prctl.h>

std::atomic<bool> running = true;
void spin_up_docker_and_watch_templates() {
  if (running) {
    std::cout << "Starting File Watch" << "\n";

    // system("docker compose up -d");
    system("./watch.sh");
  }
}
void spin_up_tailwind_watch() {
  if (running) {
    
    std::cout << "Starting Tailwind Watch" << "\n";
    system("npx @tailwindcss/cli -i ../src/static/css/input.css -o ./static/css/output.css --watch");
  }
}
void run_dev() {
  std::cout << "Running Dev Deps" << "\n";

  pid_t pid1 = fork();
    if (pid1 == 0) {
        prctl(PR_SET_PDEATHSIG, SIGKILL); // die if parent dies
        spin_up_tailwind_watch(); // blocking
        _exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        spin_up_docker_and_watch_templates(); // blocking
        _exit(0);
    }
}