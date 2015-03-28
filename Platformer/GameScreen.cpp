#include "GameScreen.h"

/*
* Description: Adds enemies into the game
*/
void GameScreen::addEnemy(){
    int height = winSize_.y;
    GLfloat positionY = rand() % height;
    glm::vec2 enemySize(32, 32);
    Sprite* enemy = new Sprite(projectileTextureID_,
        makeVector2D(winSize_.x + 80, positionY),
        enemySize, winSize_ );
    enemy->setVelocity(makeVector2D(-5, 0));
    enemy->setRotation(12);
    enemyArray_->push_back(enemy);
}

/*
* Description: Checks if two sprites are colliding with eachother or not
* @Sprite* a - The first Sprite
* @Sprite* b - The second Sprite
* First Case: if a's right side is not colliding with b's left side
* Second Case: if a's left side is not colliding with b's right side
* Third Case: if a's top side is not colliding with b's bottom side
* Fourth Case: if a's bottom side is not colliding with b's top side
* if any of these cases match, return false.
*/
bool GameScreen::checkCollision(Sprite* a, Sprite* b){
    return !(
        a->getPosition().x + a->getWidth() / 2 <= b->getPosition().x - b->getWidth() / 2 ||
        a->getPosition().x - a->getWidth() / 2 >= b->getPosition().x + b->getWidth() / 2 ||
        a->getPosition().y + a->getHeight() / 2 <= b->getPosition().y - b->getHeight() / 2 ||
        a->getPosition().y - a->getHeight() / 2 >= b->getPosition().y + b->getHeight() / 2
        );
}

/*
* Description: Check if the following sprites are outside the screen
* - Projectiles
* - Enemies
* If they are, delete them to save memory space.
*/
void GameScreen::checkOutsideScreen(){
    std::vector<std::vector<Sprite*>::iterator> deleteProjectilesArray;
    std::vector<std::vector<Sprite*>::iterator> deleteEnemyArray;

    // Check if any projectiles are out of the screen, if they are prepare them for deletion
    for (std::vector<Sprite*>::iterator projectileIterator = projectileArray_->begin();
        projectileIterator != projectileArray_->end(); projectileIterator++)
    if ((*projectileIterator)->getPosition().x > winSize_.x + (*projectileIterator)->getWidth())
        deleteProjectilesArray.push_back(projectileIterator);

    // Delete projectiles that are out of the screen
    for (auto& it : deleteProjectilesArray)
        projectileArray_->erase(it);

    // Check if any enemies are out of the screen, if they are prepare them for deletion
    for (std::vector<Sprite*>::iterator enemyIterator = enemyArray_->begin();
        enemyIterator != enemyArray_->end(); enemyIterator++)
    if ((*enemyIterator)->getPosition().x < 0 - (*enemyIterator)->getWidth())
        deleteEnemyArray.push_back(enemyIterator);

    // Delete enemies that are out of the screen
    for (auto& it : deleteEnemyArray)
        enemyArray_->erase(it);
}

void GameScreen::checkForCollisions(){
    std::vector<std::vector<Sprite*>::iterator> deleteEnemies;
    std::vector<std::vector<Sprite*>::iterator> deleteProjectiles;

    // Check if there are any collisions when the enemy touches the player or projectiles
    for (std::vector<Sprite*>::iterator& it = enemyArray_->begin(); it != enemyArray_->end();
        it++){
        if (checkCollision(*it, player_))
            deleteEnemies.push_back(it);

        for (std::vector<Sprite*>::iterator& it2 = projectileArray_->begin(); it2 != projectileArray_->end();
            it2++){
            if (checkCollision((*it), (*it2))){
                deleteEnemies.push_back(it);
                deleteProjectiles.push_back(it2);
            }
        }
    }

    // Erase enemies that collided
    for (auto& it : deleteEnemies)
        enemyArray_->erase(it);

    // Erase projectiles that collided
    for (auto& it : deleteProjectiles)
        projectileArray_->erase(it);
}

/*
 * Description: Player Logic goes here
 * Basic Example of how to check for collision:
 *
 * player_->getPosition() - will give you a 2D vector that contains the x and y position.
 * so doing player_->getPosition().x - will give you the x position of the player.
 *
 * Please note that when you use player_->getPositon() you get the positon at the origin of the player, which is the literally the middle of the sprite.
 * So if you want to get the "Left" side of the player you will need to do this:
 * player_->getPosition().x - player_->getWidth()/2
 * This will get you the x value that determines the Left side of the player.
 * So say the player was 32 x 32 the origin will be at 16,16. If the player was at position 200
 * then player_->getPosition().x will give you x at 200. And if you want to find the left-side of the player
 * then you will do: player_->getPosition().x - player_->getWidth()/2
 * which will be 200 - 16 = 184
 * so his left side is at 184. Do the same for the right side and it will be 216.
 * 
 * In this case though our player is 64 x 128 ( See constructor for details on size ).
 * This logic also applies on other sprites as well.
 */
void GameScreen::playerPhysics(){
    bool yCollision = false;

    for (Sprite* platform : *platformArray_){
        if (checkCollision(player_, platform)){
            bool rightSide = false;
            int offsetY = 0;
            int offsetX = 0;
            if ((player_->getFallHeight().y > (platform->getPosition().y + platform->getHeight() / 2)) && player_->getFalling()){
                if (yCollision = collideBottom(player_, platform, &offsetY)){
                    player_->setPosition(glm::vec2(player_->getPosition().x, player_->getPosition().y + offsetY));
                    player_->setFalling(false);
                }
            }
            else if (collideSides(player_, platform, &rightSide, &offsetX)){
                if (rightSide)
                    player_->setPosition(glm::vec2(player_->getPosition().x - offsetX, player_->getPosition().y));
                else
                    player_->setPosition(glm::vec2(player_->getPosition().x + offsetX, player_->getPosition().y));
            }
        }

        if (!yCollision){
            if (!player_->getJumping() && !player_->getFalling() && !checkBottomFloor(player_)){
                player_->setFalling(true);
            }
            else if (player_->getFalling() && checkBottomFloor(player_)){
                player_->setPosition(glm::vec2(player_->getPosition().x, player_->getHeight() / 2));
                player_->setFalling(false);
            }
        }
    }
}

bool GameScreen::checkBottomFloor(Sprite* a){
    int yPos = a->getPosition().y - a->getHeight() / 2;

    if (yPos < 0)
        return true;

    return false;
}


GameScreen::GameScreen(int width, int height) : Screen(width, height){
    glm::vec2 playerSize(64, 128);
    glm::vec2 projectileSize(32, 32);

    // Create Player Vertex
    createVertex(&playerVertexID_, &playerBufferID_, &playerIndices_, playerSize.x, playerSize.y);

    // Create Projectile Vertex
    createVertex(&projectileVertexID_, &projectileBufferID_, &projectileIndices_, projectileSize.x, projectileSize.y);

    // Create Player Texture
    playerTextureID_ = loadAndBufferImage("./Image/Player.png", GL_TEXTURE0);

    // Create Projectile Texture
    projectileTextureID_ = loadAndBufferImage("./Image/Projectile.png", GL_TEXTURE0);

    // Initialize Arraylist of Projectiles and Enemies to keep track of the entities on the screen
    projectileArray_ = new std::vector < Sprite* >;
    projectileArray_->reserve(20);
    enemyArray_ = new std::vector < Sprite* >;
    enemyArray_->reserve(20);

    // Create a new player
    player_ = new PlayerSprite(playerTextureID_, makeVector2D(500, 500), playerSize, winSize_);
    player_->setSpeed(7);
    player_->setJumpStrength(15);

    // Create Platforms
    platformArray_ = new std::vector < Sprite* > ;
    for (int i = 10; i > 5; i--){
        someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (i * projectileSize.x), projectileSize.y / 2), projectileSize, winSize_);
        platformArray_->push_back(someBlock_);
    }

    // Hard-coded Staircase

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (17 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 1), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);
    
    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (17 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 2), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (17 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 3), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (17 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 4), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (16 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 1), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (16 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 2), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (16 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 3), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (15 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 1), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (15 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 2), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (20 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 2), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    someBlock_ = new Sprite(projectileTextureID_, makeVector2D(0 + (21 * projectileSize.x), projectileSize.y / 2 + projectileSize.y * 2), projectileSize, winSize_);
    platformArray_->push_back(someBlock_);

    // Collision Testing Sprite
    
}

GameScreen::~GameScreen(){
    for (auto& it : *projectileArray_)
        delete it;

    for (auto& it : *enemyArray_)
        delete it;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete projectileArray_;
    delete enemyArray_;
    delete player_;
    /*
    glDeleteBuffers(1, &vertexBufferID_);
    glDeleteTextures(1, &textureBufferID_);
    glDeleteTextures(1, &projectileBufferID_);
    glDeleteTextures(1, &enemyBufferID_);
    */
}

/*
* Description: When the mouse is clicked, do the following:
* Left Click - Shoot a projectile at the position of the player and store it
* in an array to keep track of.
*/
void GameScreen::mouseEvent(int button, int action){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glm::vec2 projectileSize(32, 32);
        Sprite* projectile = new Sprite(projectileTextureID_, player_->getPosition(), projectileSize, winSize_);
        projectile->setVelocity(makeVector2D(10, 0));
        projectile->setRotation(36);
        projectileArray_->push_back(projectile);
    }
}

void GameScreen::render(){

    // Background Render

    // Game Render

    glBindVertexArray(playerVertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerIndices_);

    // Render Player

    player_->render();

    // Render Projectiles and Enemies (cause they share the same vertex currently)

    glBindVertexArray(projectileVertexID_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, projectileIndices_);

    for (auto& it : *platformArray_)
        it->render();

    for (auto& it : *projectileArray_)
        it->render();

    for (auto& it : *enemyArray_)
        it->render();

    // Overlay Render

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GameScreen::update(){
    // Get objects around the player
    glm::vec2 playerPos = player_->getPosition();
    glm::vec2 playerSize = player_->getSize();
    std::vector<Sprite *> nearbyObjects;

    // Find nearby platforms that the player may be able to reach
    for (auto& it : *platformArray_)
    {
        glm::vec2 platformPos = it->getPosition();
        int xOffset = abs(platformPos.x - playerPos.x);
        int yOffset = abs(platformPos.y - playerPos.y);
        if ((xOffset + yOffset) <= (playerSize.x + playerSize.y)){
            nearbyObjects.push_back(it);
        }
    }

    player_->setObjects(nearbyObjects);

    player_->update();
    //playerPhysics();

    // Checks if the players or projectiles collides with the enemy.
    //checkForCollisions();

    // Erase Enemies and Projectiles that are out of screen
    checkOutsideScreen();

    // Since the update function runs 60 times per second
    // We want to create a rock every second.
    static int update = 0;
    if (update >= 60){
        addEnemy();
        update = 0;
    }
    update++;

    // Sets the rotation and updates the projectiles
    for (auto& it : *projectileArray_)
        it->update();

    for (auto& it : *enemyArray_)
        it->update();

}