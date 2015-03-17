#include "Prefix.h"

class Screen{
public:
    void virtual mouseEvent(int button, int action);
    void virtual render();
    void virtual update();
};