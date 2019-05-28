#include "map.hpp"
#include <iostream>
#include "appsettings.hpp"

Map::Map(std::string sMap, int iNumOfColumns, int iNumOfRows) {
    iMapColumns_ = iNumOfColumns;
    iMapRows_ = iNumOfRows;

    int iScreenWidth = AppSettings::instance().screenWidth();
    int iScreenHeight = AppSettings::instance().screenHeight();

    if ((iScreenWidth / iNumOfColumns) < (iScreenHeight / iNumOfRows)) {
        //Ширина сетки будет на пятую часть меньше ширины экрана
        fGridWidth_ = iScreenWidth - (iScreenWidth / 5);
        //Узнаем ширину одного тайла, разделив ширину сетки на количество тайлов
        //в строке
        fTileWidth_ = fGridWidth_ / iMapColumns_;
        //Тайлы будут квадратными
        fTileHeight_ = fTileWidth_;
        //Умножаем количество тайлов в высоту на ширину одного тайла и получаем
        //высоту сетки
        fGridHeight_ = fTileHeight_ * iMapRows_;
    } else {
        fGridHeight_ = iScreenHeight - (iScreenHeight / 10);
        fTileHeight_ = fGridHeight_ / iMapRows_;
        fTileWidth_ = fTileHeight_;
        fGridWidth_ = fTileHeight_ * iMapColumns_;
    }

    //Вычисляем положение первого тайла слева, учитывая, что сетка будет
    //посередине
    fFirstTileX_ = (iScreenWidth - fGridWidth_) / 2.f;

    //Отступим сверху десятую часть экрана и начнем рисовать сетку оттуда
    fFirstTileY_ = iScreenHeight / 10.f;

    sMap_ = sMap;

    buildMap();

    std::cout << playerX() << " and " << playerY() << " " << this << std::endl;
}

std::vector<Map::eTile> Map::mapAsTiles() const { return vecMap_; }

std::string Map::mapAsString() const { return sMap_; }

float Map::gridWidth() const { return fGridWidth_; }

float Map::gridHeight() const { return fGridHeight_; }

float Map::tileWidth() const { return fTileWidth_; }

float Map::tileHeight() const { return fTileHeight_; }

float Map::getTileLeftX(int iTileColumn) const {
    return fFirstTileX_ + iTileColumn * fTileWidth_;
}

float Map::getTileRightX(int iTileColumn) const {
    return fFirstTileX_ + fTileWidth_ + iTileColumn * fTileWidth_;
}

float Map::getTileUpperY(int iTileRow) const {
    return fFirstTileY_ + iTileRow * fTileHeight_;
}

float Map::getTileBottomY(int iTileRow) const {
    return fFirstTileY_ + fTileHeight_ + iTileRow * fTileHeight_;
}

float Map::firstTileX() const { return fFirstTileX_; }

float Map::firstTileY() const { return fFirstTileY_; }

int Map::playerX() const { return iPlayerX_; }

int Map::playerY() const { return iPlayerY_; }

void Map::buildMap() {
    vecMap_.clear();
    for (int iCurRow = 0; iCurRow < iMapRows_; ++iCurRow) {
        for (int iCurColumn = 0; iCurColumn < iMapColumns_; ++iCurColumn) {
            char cTile = sMap_[iCurRow * iMapColumns_ + iCurColumn];
            vecMap_.push_back(charToTile(cTile));

            if (cTile == '@') {
                iPlayerX_ = iCurColumn;
                iPlayerY_ = iCurRow;
            }
        }
    }
}

void Map::setMapString(std::string sMap) { sMap_ = sMap; }

int Map::mapColumns() const { return iMapColumns_; }

int Map::mapRows() const { return iMapRows_; }

Map::eTile Map::charToTile(char cTile) {
    Map::eTile tile;
    switch (cTile) {
        case '#':
            tile = Map::eTile::WALL;
            break;
        case '@':
            tile = Map::eTile::PLAYER;
            break;
        case '+':
            tile = Map::eTile::PLAYER_ON_GOAL;
            break;
        case '$':
            tile = Map::eTile::BOX;
            break;
        case '*':
            tile = Map::eTile::BOX_ON_GOAL;
            break;
        case '.':
            tile = Map::eTile::GOAL;
            break;
        case ' ':
            tile = Map::eTile::FLOOR;
            break;
        default:
            tile = Map::eTile::FLOOR;
            break;
    }
    return tile;
}
