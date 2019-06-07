#ifndef SOCOBAN_HPP
#define SOCOBAN_HPP

#include <QGLWidget>
#include <QKeyEvent>
#include "appsettings.hpp"
#include "drawer.hpp"
#include "gamestate.hpp"
#include "mainmenu.hpp"
#include "selectlevelmenu.hpp"

class Socoban : public QGLWidget {
   public:
    Socoban();
    ~Socoban() override;

    // OpenGL initialization
    void initializeGL() override;

    // Resize window handler
    void resizeGL(int, int) override;

    // Drawing function
    void paintGL() override;

    // Keyboard handler
    void keyPressEvent(QKeyEvent*) override;

   private:
    /**
     * @brief processing_
     * Another calculations before calling draw_()
     */
    void processing();

    void draw();

    void drawMenu();
    void drawMenuSelectLevel();
    void drawPlayerStats();
    void drawPlay();
    void drawVictory();

    void keyHandlerMainMenu(int iKey);
    void keyHandlerSelectLevelMenu(int iKey);
    void keyHandlerPlayerStatMenu(int iKey);
    void keyHandlerPlay(int iKey);
    void keyHandlerVictory(int iKey);

   private:
    SelectLevelMenu* selectLevelMenu_;
    MainMenu* mainMenu_;
    GameState* gameState_;
    AppSettings* settings_;
    Drawer drawer_;
};

#endif  // SOCOBAN_HPP
