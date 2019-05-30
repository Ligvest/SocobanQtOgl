#include "appsettings.hpp"
#include <QImage>
#include <fstream>
#include "rapidxml/rapidxml.hpp"

AppSettings::AppSettings()
    : screenWidth_(800),
      screenHeight_(600),
      piTextureIds_(new unsigned int[static_cast<unsigned int>(
                                         AppSettings::eTexture::END) -
                                     1]) {}

AppSettings::~AppSettings() {
    delete[] piTextureIds_;
    save();
}

AppSettings& AppSettings::instance() {
    static AppSettings settings;
    return settings;
}

void AppSettings::load() { loadTextures("../SocobanQtGl/resources/"); }

void AppSettings::save() {}

int AppSettings::screenWidth() const { return screenWidth_; }

int AppSettings::screenHeight() const { return screenHeight_; }

void AppSettings::loadLevelsFromXml(std::string sFileName) {
    std::vector<char> vecXmlContent = loadFileToCharVector(sFileName);

    rapidxml::xml_document<> xmlDoc;
    xmlDoc.parse<0>(&vecXmlContent[0]);

    rapidxml::xml_node<>* rootNode = xmlDoc.first_node("SokobanLevels");
    rapidxml::xml_node<>* levelsNode = rootNode->first_node("LevelCollection");

    for (const rapidxml::xml_node<>* levelNode =
             levelsNode->first_node("Level");
         levelNode; levelNode = levelNode->next_sibling()) {
        std::string sMap;
        int iMapWidth = std::stoi(levelNode->first_attribute("Width")->value());
        int iMapHeight =
            std::stoi(levelNode->first_attribute("Height")->value());
        std::string sMapName = levelNode->first_attribute("Id")->value();
        for (const rapidxml::xml_node<>* mapNode = levelNode->first_node("L");
             mapNode; mapNode = mapNode->next_sibling()) {
            // We store our map in one string. To understand how many symbols we
            // need to draw in one row, we fill whole row with spaces and then
            // replace necessary spaces by map data
            std::string sMapCurRow = std::string(mapNode->value());
            size_t uBeginOfCurRow = sMap.size();
            sMap += std::string(iMapWidth, ' ');
            sMap.replace(uBeginOfCurRow, sMapCurRow.size(), sMapCurRow);
        }
        vecLevels_.emplace_back(iMapWidth, iMapHeight, sMapName, sMap);
        sMap.clear();
    }
}

void AppSettings::loadTextures(std::string sPathToTextures) {
    glEnable(GL_TEXTURE_2D);

    std::function<unsigned int(std::string sFileName)> loadTexture =
        [this](std::string sFileName) -> unsigned int {
        QImage pngImage;
        if (!pngImage.load(sFileName.c_str())) {
            throw std::invalid_argument("Wrong sprite file \"" + sFileName +
                                        "\"");
        }
        return pQGLWidget_->bindTexture(pngImage);
    };

    piTextureIds_[static_cast<unsigned int>(eTexture::PLAYER)] =
        loadTexture(sPathToTextures + "player.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::BOX)] =
        loadTexture(sPathToTextures + "box.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::BOX_ON_A_GOAL)] =
        loadTexture(sPathToTextures + "boxonagoal.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::GOAL)] =
        loadTexture(sPathToTextures + "goal.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::FLOOR)] =
        loadTexture(sPathToTextures + "floor.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::WALL)] =
        loadTexture(sPathToTextures + "wall.png");
    piTextureIds_[static_cast<unsigned int>(eTexture::PLAYER_ON_A_GOAL)] =
        loadTexture(sPathToTextures + "playeronagoal.png");

    glDisable(GL_TEXTURE_2D);
}

unsigned int AppSettings::getTextureId(eTexture texture) {
    return piTextureIds_[static_cast<unsigned int>(texture)];
}

void AppSettings::setQGLWidget(QGLWidget* pQGLWidget) {
    pQGLWidget_ = pQGLWidget;
}

std::vector<char> AppSettings::loadFileToCharVector(std::string sFileName) {
    // Read the xml file into a string
    std::ifstream fileInputStream(sFileName);

    std::vector<char> vecFileContent(
        (std::istreambuf_iterator<char>(fileInputStream)),
        std::istreambuf_iterator<char>());

    vecFileContent.push_back('\0');
    return vecFileContent;
}

std::vector<Level>* AppSettings::vecLevels() { return &vecLevels_; }
