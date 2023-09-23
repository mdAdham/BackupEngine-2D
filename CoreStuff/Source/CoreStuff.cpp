// CoreStuff.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CoreStuff.h"


// This is an example of an exported variable
CORESTUFF_API int nCoreStuff=0;

// This is an example of an exported function.
CORESTUFF_API int fnCoreStuff(void)
{
    return 0;
}

void RenderSFMLObjects(sf::RenderWindow& window, sf::Drawable& drawable)
{
    window.draw(drawable);
}

// This is the constructor of a class that has been exported.
CCoreStuff::CCoreStuff()
{
    return;
}
