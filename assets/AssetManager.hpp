#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:

	static AssetManager* instance();

	static sf::Font& getFont(std::string filename);

private:

	AssetManager() {};
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	static AssetManager* m_instance;

	static std::map<std::string, sf::Font> m_fonts;
};

std::map<std::string, sf::Font> AssetManager::m_fonts;
AssetManager* AssetManager::m_instance{ nullptr };

AssetManager* AssetManager::instance()
{
    if (m_instance == nullptr)
        m_instance = new AssetManager;

    return m_instance;
}

sf::Font& AssetManager::getFont(std::string filename)
{
    auto& fonts = instance()->m_fonts;
    auto found = fonts.find(filename);

    if (found == fonts.end())
    {
        auto& font = fonts[filename];
        font.loadFromFile(filename);
        return font;
    }

    return found->second;
}
