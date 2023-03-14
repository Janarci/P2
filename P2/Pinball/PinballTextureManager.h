
/**
 @file textureManager.h
 */
#ifndef PINBALLTEXTUREMANAGER_H
#define PINBALLTEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

 /*! \class TextureManager
  \brief A texture manager class which loads and stores textures
  */
class PinballTextureManager
{
private:
    std::map<std::string, sf::Texture> textures;    //!< Array of the textures
public:
    PinballTextureManager();   //!< Default constructor
    void loadTexture(const std::string& ksName /*!< Name of texture to load*/, const std::string& ksFilename/*!< Texture location*/); //!< Load a texture from a file
    sf::Texture& getTexture(const std::string& ksTexture); //!< Returns a texture
};
#endif
