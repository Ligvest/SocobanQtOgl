#include "socoban.hpp"
#include <QString>
#include <fstream>
#include "rapidxml/rapidxml.hpp"

Socoban::Socoban() {
    settings_ = &AppSettings::instance();
    mainMenu_ = new MainMenu();
    gameState_ = new GameState();
    settings_->loadLevelsFromXml("../SocobanQtGl/resources/100Boxes.slc");
    settings_->setQGLWidget(this);

    selectLevelMenu_ = new SelectLevelMenu(settings_->vecLevels());
}

Socoban::~Socoban() {
    delete mainMenu_;
    delete gameState_;
}

// OpenGL initialization
void Socoban::initializeGL() {
    int iWidth = settings_->screenWidth();
    int iHeight = settings_->screenHeight();

    // Set projection
    glOrtho(0, iWidth, iHeight, 0, 0, 1);

    // Disable depth buffer
    glDisable(GL_DEPTH_TEST);

    // Compute transparent color
    glEnable(GL_BLEND);

    // Draw lines with correct filtering
    glEnable(GL_LINE_SMOOTH);

    // Draw points with proper filtering
    glEnable(GL_POINT_SMOOTH);

    glEnable(GL_SMOOTH);

    // Transparent color calculate algorithm
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Two-dimensional texturing is performed
    glEnable(GL_TEXTURE_2D);

    settings_->load();
}

// Resize window handler
void Socoban::resizeGL(int aW, int aH) {
    int iWidth = settings_->screenWidth();
    int iHeight = settings_->screenHeight();

    // Replace current matrix by identity matrix
    glLoadIdentity();

    //(Xreal + 1) * (aW / 2) + x | (x is the first parameter in glViewport)
    //(Yreal + 1) * (aH / 2) + y | (y is the second parameter in glViewport)
    glViewport(0, 0, (GLint)aW, (GLint)aH);
    glOrtho(0, iWidth, iHeight, 0, 0, 1);
}

// Drawing function
void Socoban::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglClearColor(Qt::darkCyan);

    processing();
    draw();
}

// Keyboard handler
void Socoban::keyPressEvent(QKeyEvent* keyEvent) {
    switch (gameState_->curState()) {
        case GameState::eState::MENU:
            keyHandlerMainMenu(keyEvent->key());
            break;
        case GameState::eState::PLAY:
            keyHandlerPlay(keyEvent->key());
            break;
        case GameState::eState::PLAYER_STATS:
            keyHandlerPlayerStatMenu(keyEvent->key());
            break;
        case GameState::eState::SELECT_LEVEL:
            keyHandlerSelectLevelMenu(keyEvent->key());
            break;
        case GameState::eState::EXIT:
            close();
            break;
    }
}

// Processoing before drawing
void Socoban::processing() {
    switch (gameState_->curState()) {
        case GameState::eState::MENU:
            break;
        case GameState::eState::PLAY:
            break;
        case GameState::eState::PLAYER_STATS:
            break;
        case GameState::eState::SELECT_LEVEL:
            break;
        case GameState::eState::EXIT:
            close();
            break;
    }
}

void Socoban::draw() {
    switch (gameState_->curState()) {
        case GameState::eState::MENU:
            drawMenu();
            break;
        case GameState::eState::PLAY:
            drawPlay();
            break;
        case GameState::eState::PLAYER_STATS:
            drawPlayerStats();
            break;
        case GameState::eState::SELECT_LEVEL:
            drawMenuSelectLevel();
            break;
        case GameState::eState::EXIT:
            break;
    }
}

void Socoban::drawMenu() {
    QFont menuItemFont("Sans", 25);
    QFont menuItemFontSelected("Sanc", 30);

    float fMenuItemX = settings_->screenWidth() / 2 - 100;
    float fMenuItemY = settings_->screenHeight() / 3;
    float fDistBtwnItems = 55.f;
    int iEnd = mainMenu_->vecMenu().size();

    for (int i = 0; i < iEnd; ++i) {
        if (i == static_cast<int>(mainMenu_->curItem())) {
            qglColor(Qt::red);
            renderText(fMenuItemX, fMenuItemY,
                       mainMenu_->vecMenu()[i].second.c_str(),
                       menuItemFontSelected);
        } else {
            qglColor(Qt::white);
            renderText(fMenuItemX, fMenuItemY,
                       mainMenu_->vecMenu()[i].second.c_str(), menuItemFont);
        }
        fMenuItemY += fDistBtwnItems;
    }
}

void Socoban::drawMenuSelectLevel() {
    QFont menuItemFont("Sans", 25);
    QFont menuItemFontSelected("Sanc", 30);

    float fMenuItemX = settings_->screenWidth() / 2 - 100;
    float fMenuItemY = settings_->screenHeight() / 3;
    float fDistBtwnItems = 55.f;

    auto itemsToDisplay = selectLevelMenu_->rangeToDisplay();

    for (auto item : itemsToDisplay) {
        if (item.first == selectLevelMenu_->curItem()) {
            qglColor(Qt::red);
            renderText(fMenuItemX, fMenuItemY, item.second.c_str(),
                       menuItemFontSelected);
        } else {
            qglColor(Qt::white);
            renderText(fMenuItemX, fMenuItemY, item.second.c_str(),
                       menuItemFont);
        }
        fMenuItemY += fDistBtwnItems;
    }
}

void Socoban::drawPlayerStats() {}

void Socoban::drawPlay() { drawer_.draw(selectLevelMenu_->curLevel(), *this); }

void Socoban::keyHandlerMainMenu(int iKey) {
    switch (iKey) {
        case Qt::Key_Down:
            mainMenu_->nextItem();
            break;
        case Qt::Key_Up:
            mainMenu_->prevItem();
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            gameState_->setState(mainMenu_->toStateEnum());
            break;
        case Qt::Key_Escape:
            close();
            break;
        default:
            break;
    }
    updateGL();
}

void Socoban::keyHandlerSelectLevelMenu(int iKey) {
    switch (iKey) {
        case Qt::Key_Down:
            selectLevelMenu_->nextItem();
            break;
        case Qt::Key_Up:
            selectLevelMenu_->prevItem();
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            gameState_->setState(GameState::eState::PLAY);
            break;
        case Qt::Key_Escape:
            gameState_->setState(GameState::eState::MENU);
            break;
        default:
            break;
    }
    updateGL();
}

void Socoban::keyHandlerPlayerStatMenu(int iKey) {
    switch (iKey) {
        case Qt::Key_Down:
            break;
        case Qt::Key_Up:
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            break;
        case Qt::Key_Escape:
            gameState_->setState(GameState::eState::MENU);
            break;
        default:
            break;
    }
    updateGL();
}

void Socoban::keyHandlerPlay(int iKey) {
    switch (iKey) {
        case Qt::Key_Down:
            break;
        case Qt::Key_Up: {
            auto curLevel = selectLevelMenu_->curLevel();
            curLevel.playerUp();
            break;
        }
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        case Qt::Key_R:
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            break;
        case Qt::Key_Escape:
            gameState_->setState(GameState::eState::MENU);
            break;
        default:
            break;
    }
    updateGL();
}
