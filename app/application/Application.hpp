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

Application* CreateApplication();

#endif