#include "textui.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shaderhelper.h"

CTextui::CTextui(glm::vec3 _position, glm::vec3 _color, std::string text, std::string font)
{
	m_text = text;
	m_color = _color;
	m_position = _position;
	m_font = font;
	m_scale = 1.0f;

	m_isInteractive = false;

	this->Initialise();
}

CTextui::~CTextui()
{

}

bool CTextui::Initialise()
{
	glUseProgram(m_program);
	ShaderHelper::CompileAndLinkShaders("text_vs.glsl", "text_fs.glsl", m_program);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_WIDTH), 0.0f, static_cast<GLfloat>(WINDOW_HEIGHT));
	glUseProgram(m_program);///problems
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	FT_Library ft;

	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, m_font.c_str(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 32);//font size

									// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		Characters.insert(std::pair<GLchar, Character>(c, character));
	}


	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void CTextui::Render()
{
	glm::vec2 textPos;
	textPos.x = m_position.x;
	textPos.y = m_position.y;

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate corresponding render state	
	glUseProgram(m_program);
	glUniform3f(glGetUniformLocation(m_program, "textColor"), m_color.x, m_color.y, m_color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = m_text.begin(); c != m_text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = textPos.x + ch.Bearing.x * m_scale;
		GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y) * m_scale;

		GLfloat w = ch.Size.x * m_scale;
		GLfloat h = ch.Size.y * m_scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
		{ xpos, ypos, 0.0, 1.0 },
		{ xpos + w, ypos, 1.0, 1.0 },

		{ xpos, ypos + h, 0.0, 0.0 },
		{ xpos + w, ypos, 1.0, 1.0 },
		{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		textPos.x += (ch.Advance >> 6) * m_scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void CTextui::setColor(glm::vec3 _color)
{
	m_color = _color;
}

void CTextui::setText(std::string _text)
{
	m_text = _text;
}

void CTextui::setPosition(glm::vec3 _position)
{
	_position.y = WINDOW_HEIGHT - _position.y;
	m_position = _position;
}