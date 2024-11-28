// SpriteSheet
// Charles Tiemeyer, Oct 2024

#include "SpriteSheet.h"
#include "TEAL\WindowManager.h" 

SpriteSheet::SpriteSheet(sf::Texture& tex, int CellCountHor, int CellCountVert)
{
	Fontexture = tex;

	// Rectangle dimension corresponding to a single cell of the sprite sheet
	cellWidth = tex.getSize().x / CellCountHor;
	cellHeight = tex.getSize().y / CellCountVert;

	GlyphCollection.resize(CellCountHor * CellCountVert);

	// Initialize each sprite with the corrrect rectangle
	int left;
	int top;
	for (int j = 0; j < CellCountVert; j++)
	{
		top = j * cellHeight;
		for (int i = 0; i < CellCountHor; i++)
		{
			left = i * cellWidth;
			GlyphCollection[j * CellCountHor + i] = sf::Sprite(Fontexture, sf::IntRect(left, top, cellWidth, cellHeight));
		}
	}
}

int SpriteSheet::CellWidth() {
	return cellWidth;
}

int SpriteSheet::CellHeight() {
	return cellHeight;
}

Glyph SpriteSheet::GetGlyph(char c, sf::Vector2f pos)
{
	return Glyph(this, CharToIndex(c), pos);	// as an extra efficiency, we should add a glyph recycling factory to use here
}

void SpriteSheet::Draw(int i, sf::Vector2f pos)
{
	sf::Sprite& OneGlyph = GlyphCollection[i];
	OneGlyph.setPosition(pos);
	OneGlyph.setScale(sf::Vector2f(2, 2));
	WindowManager::Window().draw(OneGlyph);
}