#include "Prefix.h"
#include "Screen.h"
#include "Sprite.h"

class GameoverScreen : public Screen {
private:
    // Menu Button Data
    GLuint menuButtonVertexID_;
    GLuint menuButtonBufferID_;
    GLuint menuButtonIndices_;

    // Menu Button Textures
    GLuint backToTitleID_;
    GLuint gameOverID_;
    
    // Menu Buttons
    Sprite *titleBtn_;

    // Labels
    Sprite *gameOverLabel_;

    bool checkButtonCollision(int xpos, int ypos, Sprite* btn);

public:
    GameoverScreen(int width, int height);
    ~GameoverScreen();

    void mouseEvent(int button, int action);
    void render();
};