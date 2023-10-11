#ifndef APPLICATION
#define APPLICATION

class Application
{
    void updateDraw();
    
public:
    Application();
    ~Application();
    
    void run();
};

Application* CreateApllication();

#endif