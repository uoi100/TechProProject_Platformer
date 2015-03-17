#include "Prefix.h"
#include "GameScreen.h"
#include "TitleScreen.h"

class GameWindow
{
private:
    int width_;
    int height_;
    GLFWwindow* window_;
    GLuint vertexArrayObjectID_;
    GLuint smallVertexArrayObjectID_;
    GLuint vertexBufferID_;
    GLuint smallVertexBufferID_;
    GLuint textureBufferID_;
    GLuint projectileBufferID_;
    GLuint enemyBufferID_;

    PlayerSprite* player_;
    std::vector<Sprite*> *projectileArray_;
    std::vector<Sprite*> *enemyArray_;
    Screen *currentScreen;

    void addEnemy();
    bool checkCollision(Sprite* a, Sprite* b);
    void checkForCollisions();
    void checkOutsideScreen();
    void setupGL(int width, int height, const char* title);
public: 
    GameWindow(int width, int height, const char* winTitle);
    ~GameWindow();

    void mouseEvent(int button, int action);
    int getWidth();
    int getHeight();
    GLFWwindow* getWindow();

    void render();
    void update();
};



