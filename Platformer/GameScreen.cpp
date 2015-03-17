#include "GameScreen.h"

/*
* Description: Adds enemies into the game
*/
void GameScreen::addEnemy(){
    GLfloat positionY = rand() % height_;
    Sprite* enemy = new Sprite(enemyBufferID_, makeVector2D(width_ + 80, positionY), 32, 32);
    enemy->setVelocity(makeVector2D(-5, 0));
    enemy->setRotationVelocity(12);
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
    if ((*projectileIterator)->getPosition().x > width_ + (*projectileIterator)->getWidth())
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

GameScreen::GameScreen(int width, int height) : Screen(width, height){
    createVertexBuffer(&vertexArrayObjectID_, &vertexBufferID_, 64, 128);
    createVertexBuffer(&smallVertexArrayObjectID_, &smallVertexBufferID_, 32, 32);

    textureBufferID_ = loadAndBufferImage("./Image/Player.png");
    projectileBufferID_ = loadAndBufferImage("./Image/Projectile.png");
    enemyBufferID_ = loadAndBufferImage("./Image/Enemy.png");

    projectileArray_ = new std::vector < Sprite* >;
    projectileArray_->reserve(20);
    enemyArray_ = new std::vector < Sprite* >;
    enemyArray_->reserve(20);

    player_ = new PlayerSprite(textureBufferID_, makeVector2D(500, 500), 64, 128);
    player_->setBoundingBox(makeBoundingBox(height_, 0, 0, width_));
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
    glDeleteBuffers(1, &vertexBufferID_);
    glDeleteTextures(1, &textureBufferID_);
    glDeleteTextures(1, &projectileBufferID_);
    glDeleteTextures(1, &enemyBufferID_);
}

/*
* Description: When the mouse is clicked, do the following:
* Left Click - Shoot a projectile at the position of the player and store it
* in an array to keep track of.
*/
void GameScreen::mouseEvent(int button, int action){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        Sprite* projectile = new Sprite(projectileBufferID_, player_->getPosition(), 32, 32);
        projectile->setVelocity(makeVector2D(10, 0));
        projectile->setRotationVelocity(36);
        projectileArray_->push_back(projectile);
    }
}

void GameScreen::render(){
    glBindVertexArray(vertexArrayObjectID_);

    player_->render();

    glBindVertexArray(smallVertexArrayObjectID_);
    for (auto& it : *projectileArray_)
        it->render();

    for (auto& it : *enemyArray_)
        it->render();
}

void GameScreen::update(){
    player_->update();

    // Checks if the players or projectiles collides with the enemy.
    checkForCollisions();

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