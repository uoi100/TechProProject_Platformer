#include "Prefix.h"
#include "Screen.h"
#include "PlayerSprite.h"

class GameScreen : public Screen {
private:
    // Player Shader Variables
    GLuint playerVertexID_;
    GLuint playerBufferID_;
    GLuint playerIndices_;

    // Player Texture Variables
    GLuint playerTextureID_;

    // Projectile Shader Variables
    GLuint projectileVertexID_;
    GLuint projectileBufferID_;
    GLuint projectileIndices_;

    // Projectile Texture Variables
    GLuint projectileTextureID_;

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