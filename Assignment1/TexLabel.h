//#pragma once
//
//#include "include.h"
//#include "ShaderHelper.h"
//
//#include "Includes\ft2build.h"
//#include FT_FREETYPE_H
//
//#include <map>
//#include <string>
//#include <iostream>
//
//struct Character {
//	GLuint     TextureID;  // ID handle of the glyph texture
//	glm::ivec2 Size;       // Size of glyph
//	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
//	GLuint     Advance;    // Offset to advance to next glyph
//};
//
//
//
//class TextLabel
//{
//public:
//	TextLabel(std::string text, std::string font);
//	~TextLabel();
//
//	void Render();
//	void setPosition(glm::vec2 _position);
//	void setColor(glm::vec3 _color);
//	void setScale(GLfloat _scale);
//	void setText(std::string _text);
//	void SetHidden(bool _bHidden);
//	bool GetHidden();
//
//private:
//	std::string text;
//	GLfloat scale;
//	glm::vec3 color;
//	glm::vec2 position;
//
//	bool m_bHidden;
//
//	GLuint VAO, VBO, program;
//	std::map<GLchar, Character> Characters;
//
//
//};
//
