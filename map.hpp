#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

class Map {
   public:
    enum class eTile {
        FLOOR,
        WALL,
        PLAYER,
        PLAYER_ON_GOAL,
        BOX,
        BOX_ON_GOAL,
        GOAL
    };

   public:
    Map(std::string sMap, int iWidth, int iHeight);

    std::vector<Map::eTile> mapAsTiles() const;
    std::string mapAsString() const;

    /**
     * @brief Width of grid as columns quantity
     * @return Width of grid
     */
    float gridWidth() const;

    /**
     * @brief Height of grid as rows quantity
     * @return Height of grid
     */
    float gridHeight() const;

    /**
     * @brief Tile width in display coordinates
     * @return Tile width
     */
    float tileWidth() const;

    /**
     * @brief Tile height in display coordinates
     * @return Tile height
     */
    float tileHeight() const;

    float getTileLeftX(int iTileColumn) const;
    float getTileRightX(int iTileColumn) const;
    float getTileUpperY(int iTileRow) const;
    float getTileBottomY(int iTileRow) const;

    float firstTileX() const;
    float firstTileY() const;

    int playerX() const;
    int playerY() const;

    /**
     * @brief init mapAsTiles() by map from mapAsString()
     */
    void buildMap();

    /**
     * @brief Set variable from mapAsString()
     * @param sMap - string to set
     */
    void setMapString(std::string sMap);

    int mapColumns() const;
    int mapRows() const;
    void ResetMap();

    int goals() const;
    int boxesOnGoals() const;

   private:
    int iMapColumns_;
    int iMapRows_;
    int iPlayerX_;
    int iPlayerY_;
    float fGridWidth_;
    float fGridHeight_;
    float fTileWidth_;
    float fTileHeight_;

    float fFirstTileX_;
    float fFirstTileY_;

    int iBoxesOnGoals;
    int iGoals;

    std::string sMap_;
    std::string sInitialMap_;
    std::vector<eTile> vecMap_;
    Map::eTile charToTile(char cTile);
};

#endif  // MAP_HPP
