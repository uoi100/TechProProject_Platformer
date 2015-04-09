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

    // Cloud Variables
    GLuint cloudTextureID_;

    // Background Variables
    GLuint backgroundVertexID_;
    GLuint backgroundBufferID_;
    GLuint backgroundIndices_;
    GLuint backgroundTextureID_;

    Sprite* background_;

    // Platformer Variables
    GLuint platformVertexID_;
    GLuint platformBufferID_;
    GLuint platformIndices_;
    GLuint platformTextureID_;

    // End Point
    GLuint endPointVertexID_;
    GLuint endPointBufferID_;
    GLuint endPointIndices_;
    GLuint endPointTextureID_;

    Sprite* endPoint_;

    // Arraylist of Sprites
    std::vector<Sprite*> *platformArray_;
    std::vector<Sprite*> *projectileArray_;
    std::vector<Sprite*> *enemyArray_;

    void addEnemy();
    bool checkCollision(Sprite* a, Sprite* b);
    void checkForCollisions();
    void checkOutsideScreen();
    void playerPhysics();
    bool checkBottomFloor(Sprite* a);
    // Setup Platforms
    void setupLevel();
public:
    GameScreen(int width, int height);
    ~GameScreen();

    void mouseEvent(int button, int action);
    void render();
    void update();
};