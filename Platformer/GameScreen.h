#include "Prefix.h"
#include "Screen.h"
#include "PlayerSprite.h"

class GameScreen : public Screen {
private:
    GLuint vertexArrayObjectID_;
    GLuint smallVertexArrayObjectID_;
    GLuint vertexBufferID_;
    GLuint smallVertexBufferID_;
    GLuint textureBufferID_;
    GLuint projectileBufferID_;
    GLuint enemyBufferID_;

    PlayerSprite* player_;
    Sprite* someBlock_;
    std::vector<Sprite*> *projectileArray_;
    std::vector<Sprite*> *enemyArray_;

    void addEnemy();
    bool checkCollision(Sprite* a, Sprite* b);
    void checkForCollisions();
    void checkOutsideScreen();
    void playerPhysics();
public:
    GameScreen(int width, int height);
    ~GameScreen();

    void mouseEvent(int button, int action);
    void render();
    void update();
};