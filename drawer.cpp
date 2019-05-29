#include "drawer.hpp"
#include <iostream>
#include "appsettings.hpp"

Drawer::Drawer() {}

void Drawer::draw(const Level& level, QGLWidget& qglWidget) {
    drawGrid(level, qglWidget);
    drawObjects(level, qglWidget);
    drawStatistics(level, qglWidget);
}

void Drawer::drawGrid(const Level& level, QGLWidget& qglWidget) {
    /**
     * Drawing grid
     *
     **/
    //    int iNumOfRows = level.rows();
    //    int iNumOfColumns = level.columns();

    //    const Map& map = level.map();

    //    qglWidget.qglColor(Qt::gray);
    //    glBegin(GL_LINES);
    //    for (int iCurRow = 0; iCurRow <= iNumOfRows; ++iCurRow) {
    //        glVertex2i(map.getTileLeftX(0), map.getTileUpperY(iCurRow));
    //        glVertex2i(map.getTileRightX(iNumOfColumns - 1),
    //        map.getTileUpperY(iCurRow));
    //    }

    //    for (int iCurColumn = 0; iCurColumn <= iNumOfColumns; ++iCurColumn) {
    //        glVertex2i(map.getTileLeftX(iCurColumn), map.getTileUpperY(0));
    //        glVertex2i(map.getTileLeftX(iCurColumn),
    //        map.getTileUpperY(iNumOfRows));
    //    }
    //    glEnd();

    /**
     * Drawing floor on the whole map
     *
     **/
    //    int iNumOfRows = level.rows();
    //    int iNumOfColumns = level.columns();

    //    const Map& map = level.map();

    //    float fTileWidth = map.tileWidth();
    //    float fTileHeight = map.tileHeight();

    //    auto pSettings = &AppSettings::instance();

    //    unsigned uFloorSpriteId =
    //        pSettings->getTextureId(AppSettings::eTexture::FLOOR);

    //    const auto vecMap = level.map().mapAsTiles();

    //    glEnable(GL_TEXTURE_2D);
    //    for (int iCurRow = 0; iCurRow < iNumOfRows; ++iCurRow) {
    //        for (int iCurCol = 0; iCurCol < iNumOfColumns; ++iCurCol) {
    //            qglWidget.drawTexture(
    //                QRectF(map.getTileLeftX(iCurCol),
    //                map.getTileUpperY(iCurRow),
    //                       fTileWidth, fTileHeight),
    //                uFloorSpriteId);
    //        }
    //    }
    //    glDisable(GL_TEXTURE_2D);
}

void Drawer::drawObjects(const Level& level, QGLWidget& qglWidget) {
    int iNumOfRows = level.rows();
    int iNumOfColumns = level.columns();

    const Map& map = level.map();

    float fTileWidth = map.tileWidth();
    float fTileHeight = map.tileHeight();

    auto pSettings = &AppSettings::instance();

    unsigned uBoxSpriteId = pSettings->getTextureId(AppSettings::eTexture::BOX);
    unsigned uBoxOnAGoalSpriteId =
        pSettings->getTextureId(AppSettings::eTexture::BOX_ON_A_GOAL);
    unsigned uGoalSpriteId =
        pSettings->getTextureId(AppSettings::eTexture::GOAL);
    unsigned uPlayerSpriteId =
        pSettings->getTextureId(AppSettings::eTexture::PLAYER);
    unsigned uPlayerOnAGoalSpriteId =
        pSettings->getTextureId(AppSettings::eTexture::PLAYER_ON_A_GOAL);
    unsigned uWallSpriteId =
        pSettings->getTextureId(AppSettings::eTexture::WALL);
    //    unsigned uFloorSpriteId =
    //    pSettings->getTextureId(AppSettings::eTexture::FLOOR);

    const auto vecMap = map.mapAsTiles();

    glEnable(GL_TEXTURE_2D);
    for (int iCurRow = 0; iCurRow < iNumOfRows; ++iCurRow) {
        for (int iCurCol = 0; iCurCol < iNumOfColumns; ++iCurCol) {
            unsigned uSpriteId = 0;
            switch (vecMap[iCurCol + iCurRow * iNumOfColumns]) {
                case Map::eTile::BOX: {
                    uSpriteId = uBoxSpriteId;
                    break;
                }
                case Map::eTile::BOX_ON_GOAL: {
                    uSpriteId = uBoxOnAGoalSpriteId;
                    break;
                }
                case Map::eTile::GOAL: {
                    uSpriteId = uGoalSpriteId;
                    break;
                }
                case Map::eTile::PLAYER: {
                    uSpriteId = uPlayerSpriteId;
                    break;
                }
                case Map::eTile::PLAYER_ON_GOAL: {
                    uSpriteId = uPlayerOnAGoalSpriteId;
                    break;
                }
                case Map::eTile::WALL: {
                    uSpriteId = uWallSpriteId;
                    break;
                }
                case Map::eTile::FLOOR: {
                    //                    uSpriteId = uFloorSpriteId;
                    break;
                }
                default: { break; }
            }
            if (uSpriteId != 0) {
                qglWidget.drawTexture(
                    QRectF(map.getTileLeftX(iCurCol),
                           map.getTileUpperY(iCurRow), fTileWidth, fTileHeight),
                    uSpriteId);
            }
        }
    }
    glDisable(GL_TEXTURE_2D);
}

void Drawer::drawStatistics(const Level& level, QGLWidget& qglWidget) {
    QFont font = QFont("Comic Sans MS", 15);
    std::string sHud;

    sHud = "Steps: ";
    sHud += std::to_string(level.stepsPerformed());
    qglWidget.renderText(15, 20, sHud.c_str(), font);

    sHud = "Boxes on goals: ";
    sHud += std::to_string(level.boxesOnGoals());
    sHud += "/";
    sHud += std::to_string(level.goals());
    qglWidget.renderText(15, 40, sHud.c_str(), font);
}
