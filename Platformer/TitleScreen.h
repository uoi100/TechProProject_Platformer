#include "Prefix.h"
#include "Screen.h"
#include "Sprite.h"

class TitleScreen : public Screen {
private:
    GLuint menuButtonVAOID_;
    GLuint menuButtonVBOID_;
    GLuint startBtnID_;
    GLuint exitBtnID_;

    Sprite *startBtn_;
    Sprite *exitBtn_;

    bool checkButtonCollision(int xpos, int ypos, Sprite* btn);
public:
    TitleScreen(int width, int height);
    ~TitleScreen();

    void mouseEvent(int button, int action);
    void render();
    void update();
};