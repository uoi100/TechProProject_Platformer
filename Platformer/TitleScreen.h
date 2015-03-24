#include "Prefix.h"
#include "Screen.h"
#include "Sprite.h"

class TitleScreen : public Screen {
private:

    // Menu Button Data
    GLuint menuButtonVertexID_;
    GLuint menuButtonBufferID_;
    GLuint menuButtonIndices_;

    // Menu Button Textures
    GLuint startBtnID_;
    GLuint exitBtnID_;

    // Screen Variables
    Sprite *startBtn_;
    Sprite *exitBtn_;

    // Logic Functions
    bool checkButtonCollision(int xpos, int ypos, Sprite* btn);
public:
    TitleScreen(int width, int height);
    ~TitleScreen();

    void mouseEvent(int button, int action);
    void render();
    void update();
};