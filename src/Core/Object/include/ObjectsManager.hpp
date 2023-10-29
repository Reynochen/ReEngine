#ifndef OBJMANAGER
#define OBJMANAGER

class Object;

class ObjManager {
    Object* objects;
    

public:
    void AddObject();
    void RemoveObject();

};

#endif