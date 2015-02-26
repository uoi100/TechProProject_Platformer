#include "GameWindow.h"
#include <algorithm>
#include <string>

GLuint GameWindow::createVertexBuffer(int width, int height){
    GLuint vertexBufferID;
    // Create a name buffer object for vertexBufferID
    glGenBuffers(1, &vertexBufferID);
    // Sets an array buffer pointed at vertexBufferID
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    // Create a vertex with 4 points for our entities
    VertexData square[] = {
            { { -width / 2, -height / 2, 0.0f }, { 0.0f, 0.0f } },     // Bottom-Left
            { { width / 2, -height / 2, 0.0f }, { 1.0f, 0.0f } },   // Bottom-Right
            { { width / 2, height / 2, 0.0f }, { 1.0f, 1.0f } }, // Top-Right
            { { -width / 2, height / 2, 0.0f }, { 0.0f, 1.0f } }    // Top-Left
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

    return vertexBufferID;
}

// We want to render load and buffer images for drawing
GLuint GameWindow::loadAndBufferImage(const char* fileName){

    GLuint textureBufferID = SOIL_load_OGL_texture(
        fileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA);

    if (textureBufferID == 0)
        return NULL;

    glBindTexture(GL_TEXTURE_2D, textureBufferID);

    // Sets Texture Environment, in this case we want to set the environment
    // to make the image transparent
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureBufferID;
}

/*
 * Description: Adds enemies into the game
 */
void GameWindow::addEnemy(){
    GLfloat positionY = rand() % height_;
    Sprite* enemy = new Sprite(enemyBufferID_, makeVector2D(width_ + 80, positionY), 80, 120);
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
bool GameWindow::checkCollision(Sprite* a, Sprite* b){
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
void GameWindow::checkOutsideScreen(){
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

void GameWindow::checkForCollisions(){
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

// Sets up OpenGL and Glew which allows for the graphics operations to work.
void GameWindow::setupGL(int width, int height, const char* title){
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);

    //Glew Init must be initialized after a Context is set.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //Specifies the area that will be drawn
    glViewport(0, 0, width_, height_);
    // Clear background and fill with the color white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable usage of 2D Textures
    glEnable(GL_TEXTURE_2D);
    // Enable usage of Alpha Blending, for transparent images
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the current matrix to the GL_PROJECTION matrix
    // Which is the matrix that "Projects" how you see when things are drawn
    glMatrixMode(GL_PROJECTION);
    // replace the current matrix with the identity matrix
    glLoadIdentity();
    // Defines a 2D orthographic projection matrix
    // basically the clipping plane which "clips out" things that would be
    // drawn outside as we would not see it anyways.
    gluOrtho2D(0, width_, 0, height_);
    // Set the current matrix to the GL_MODELVIEW matrix
    // Which is basically for our objects to be drawn and then translated onto our projection
    glMatrixMode(GL_MODELVIEW);

    /*
    // Create a name buffer object for vertexBufferID
    glGenBuffers(1, &vertexBufferID_);
    // Sets an array buffer pointed at vertexBufferID
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_);
    // Create a vertex with 4 points for our entities
    //VertexData *vertices = makeVertices(64, 128);
    int texWidth = 64;
    int texHeight = 128;

    VertexData square[] = {
    { { -texWidth / 2, -texHeight / 2, 0.0f }, { 0.0f, 0.0f } },     // Bottom-Left
    { { texWidth / 2, -texHeight / 2, 0.0f }, { 1.0f, 0.0f } },   // Bottom-Right
    { { texWidth / 2, texHeight / 2, 0.0f }, { 1.0f, 1.0f } }, // Top-Right
    { { -texWidth / 2, texHeight / 2, 0.0f }, { 0.0f, 1.0f } }    // Top-Left
    };

    // Adds the data of vertices into the buffer for static drawing operations
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
    */
    vertexBufferID_ = createVertexBuffer(64, 128);

    // Allows the client to use vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Lets the drawing know the size of the array, what data type it should expect,
    // the size of the struct, and an offset of the struct and the member that will be read.
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, positionCoordinates));

    // Lets the drawing know the texture coordinates of the array, this is used so it knows the corners of the image
    
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData),
        (GLvoid *)offsetof(VertexData, textureCoordinates));
}

/*
 * Description: Constructor
 * - Sets up openGL and Glew
 * - Sets up the Sprites (Entities) for the game.
 */
GameWindow::GameWindow(int width, int height, const char* winTitle):
width_{ width }, height_{ height }, vertexBufferID_{ 0 }, textureBufferID_{ 0 }{
    setupGL(width_, height_, winTitle);

    textureBufferID_ = loadAndBufferImage("./Image/Player.png");
    projectileBufferID_ = loadAndBufferImage("./Image/Projectile.png");
    enemyBufferID_ = loadAndBufferImage("./Image/Enemy.png");

    projectileArray_ = new std::vector < Sprite* >;
    projectileArray_->reserve(20);
    enemyArray_ = new std::vector < Sprite* > ;
    enemyArray_->reserve(20);

    player_ = new PlayerSprite(textureBufferID_, makeVector2D(500,500), 80, 120);
    player_->setBoundingBox(makeBoundingBox(height_, 0, 0, width_));
}

GameWindow::~GameWindow(){
    for (auto& it : *projectileArray_)
        delete it;

    for (auto& it : *enemyArray_)
        delete it;
    
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
void GameWindow::mouseEvent(int button, int action){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        Sprite* projectile = new Sprite(projectileBufferID_, player_->getPosition(), 80, 120);
        projectile->setVelocity(makeVector2D(10, 0));
        projectile->setRotationVelocity(36);
        projectileArray_->push_back(projectile);
    }
}

int GameWindow::getWidth(){
    return width_;
}

int GameWindow::getHeight(){
    return height_;
}

GLFWwindow* GameWindow::getWindow(){
    return window_;
}


/*
 * Description: Main drawing operations for objects will be here.
 */
void GameWindow::render(){
    glClear(GL_COLOR_BUFFER_BIT);

    player_->render();

    for (auto& it : *projectileArray_)
        it->render();

    for (auto& it : *enemyArray_)
        it->render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

// This is where the update functions of objects go
void GameWindow::update(){
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