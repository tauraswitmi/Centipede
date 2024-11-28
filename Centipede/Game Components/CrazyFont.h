// CrazyFont
// Charles Tiemeyer, Oct 2024

#ifndef _CrazyFont
#define _CrazyFont

#include "SpriteSheet.h"

class CrazyFont : public SpriteSheet
{
public:
	CrazyFont();

	CrazyFont(const CrazyFont&) = delete;
	CrazyFont& operator=(const CrazyFont&) = delete;
	virtual ~CrazyFont() = default;

private:
	virtual int CharToIndex(char& c);
};


#endif _CrazyFont