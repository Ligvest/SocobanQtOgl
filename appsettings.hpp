#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QGLWidget>
#include <string>
#include <vector>
#include "level.hpp"

class AppSettings {
   public:
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
    static AppSettings& instance();
    void load();
    void save();
    void loadLevelsFromXml(std::string sFileName);
    void loadTextures(std::string sPathToTextures);
    unsigned int getTextureId(eTexture texture);

    void setQGLWidget(QGLWidget* widget);

    int screenWidth() const;
    int screenHeight() const;

    std::vector<Level>* vecLevels();

   private:
    // Restrict all constructors
    AppSettings();
    ~AppSettings();
    AppSettings(const AppSettings&) = delete;
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
