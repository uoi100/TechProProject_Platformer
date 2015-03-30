#include "Prefix.h"
#include "Screen.h"
#include "PlayerSprite.h"

class GameScreen : public Screen {
private:
    // Player Variables
    GLuint playerVertexID_;
    GLuint playerBufferID_;
    GLuint playerIndices_;
    GLuint playerTextureID_;

    PlayerSprite* player_;

    // Projectile Variables
    GLuint projectileVertexID_;
    GLuint projectileBufferID_;
    GLuint projectileIndices_;
    GLuint projectileTextureID_;

    // Background Variables
    GLuint backgroundVertexID_;
    GLuint backgroundBufferID_;
    GLuint backgroundIndices_;
    GLuint backgroundTextureID_;

    Sprite* background_;

    // Platformer Variables
    std::vector<Sprite*> *platformArray_;

    Sprite* someBlock_;
    std::vector<Sprite*> *projectileArray_;
    std::vector<Sprite*> *enemyArray_;

    void addEnemy();
    bool checkCollision(Sprite* a, Sprite* b);
    void checkForCollisions();
    void checkOutsideScreen();
    void playerPhysics();
    bool checkBottomFloor(Sprite* a);
public:
    GameScreen(int width, int height);
    ~GameScreen();

    void mouseEvent(int button, int action);
    void render();
    void update();
};