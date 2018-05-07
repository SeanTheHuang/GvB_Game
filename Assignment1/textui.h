#pragma once 

#include "userinterface.h"
#include <map>


struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class CTextui : public CUi
{
public:
	CTextui(glm::vec3 _position, glm::vec3 _color, std::string text, std::string font);
	~CTextui();
	virtual void Render();
	virtual bool Initialise();
	void setColor(glm::vec3 _color);
	void setText(std::string _text);

	void setPosition(glm::vec3 _position);
private:
	std::string m_text;
	glm::vec3 m_color;

	std::string m_font;
	std::map<GLchar, Character> Characters;
};