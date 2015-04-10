#include "Prefix.h"
#include "Screen.h"
#include "Sprite.h"

class CongratsScreen : public Screen {
private:
    // Menu Button Data
    GLuint menuButtonVertexID_;
    GLuint menuButtonBufferID_;
    GLuint menuButtonIndices_;

    // Menu Button Textures
    GLuint backToTitleID_;
    GLuint congratsID_;

    // Menu Buttons
    Sprite *titleBtn_;

    // Labels
    Sprite *congratsLabel_;

    bool checkButtonCollision(int xpos, int ypos, Sprite* btn);

public:
    CongratsScreen(int width, int height);
    ~CongratsScreen();

    void mouseEvent(int button, int action);
    void render();
};