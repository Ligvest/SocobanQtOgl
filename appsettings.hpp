#ifndef APPSETTINGS_H
#define APPSETTINGS_H

/**
  @file File that describes AppSettings class
 **/
#include <QGLWidget>
#include <string>
#include <vector>
#include "level.hpp"

/**
 * @brief The AppSettings class
 * @details Singletone class, that contains most of settings of the Socoban
 */
class AppSettings {
   public:
    /**
     * @brief Enumeration for naming sprites
     */
    enum class eTexture {
        PLAYER = 0,
        PLAYER_ON_A_GOAL,
        WALL,
        BOX,
        BOX_ON_A_GOAL,
        GOAL,
        FLOOR,
        END
    };
    static AppSettings instance_;

   public:
    /**
     * @brief Get instance of the Singletone
     * @return instance of the class
     */
    static AppSettings& instance();

    /**
     * @brief Loads a saved game.
     * @warning Not implemented.
     */
    void load();

    /**
     * @brief Saves a game.
     * @warning Not implemented.
     */
    void save();

    /**
     * @brief Loads levels from xml file and puts it in vecLevels()
     * @param sFileName - xml file with levels
     */
    void loadLevelsFromXml(std::string sFileName);

    /**
     * @brief Loads textures from png files and puts their IDs in piTextureIds_
     * array
     * @param sPathToTextures - path to folder with sprites
     */
    void loadTextures(std::string sPathToTextures);

    /**
     * @brief Get texture Id by texture enumeration value
     * @param texture - texture enum value
     * @return Id of the given texture
     */
    unsigned int getTextureId(eTexture texture);

    /**
     * @brief Sets QGLWidget to use it for drawing
     * @param widget - QGLWidget to set
     */
    void setQGLWidget(QGLWidget* widget);

    /**
     * @brief Get screen width
     * @return Screen width
     */
    int screenWidth() const;

    /**
     * @brief Get screen height
     * @return Screen height
     */
    int screenHeight() const;

    /**
     * @brief Get vector of levels
     * @return Vector of levels
     */
    std::vector<Level>* vecLevels();

   private:
    // Restrict all constructors
    /**
     * @brief Private constructor to rich singletone principles.
     */
    AppSettings();

    /**
     * @brief Private destructor to rich singletone principles.
     */
    ~AppSettings();

    /**
     * @brief Private copy constructor to rich singletone principles.
     */
    AppSettings(const AppSettings&) = delete;

    /**
     * @brief Private assignment operator to rich singletone principles.
     */
    AppSettings& operator=(const AppSettings&) = delete;

   private:
    int screenWidth_;
    int screenHeight_;
    std::vector<char> loadFileToCharVector(std::string sFileName);
    std::vector<Level> vecLevels_;
    QGLWidget* pQGLWidget_;
    unsigned int* piTextureIds_;
};

#endif  // APPSETTINGS_H
