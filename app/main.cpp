#include "application/Application.hpp"

int main(int argc, char* argv[]) {
    Application* app = CreateApplication();
    app->run();

    delete app;
    return 0;
}