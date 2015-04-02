#include "Prefix.h"
#include "Sprite.h"

class PlayerSprite : public Sprite{
private:
    // Check for key inputs
    void checkInput();

    // An arraylist of objects near the player
    std::vector<Sprite *> objects_;

    // Player Variables
    bool alive_;
public:
    PlayerSprite(GLfloat textureID, glm::vec2 position, glm::vec2 size, glm::vec2 windowSize);

    // Get objects near the player
    void setObjects(std::vector<Sprite *> objects);

    // Check if the player is alive or not
    bool isAlive();

    // Window Functions
    void render(int xOffset = 0, int yOffset = 0);
    void update();
};