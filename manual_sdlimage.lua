animation - fehlt.

--[[
  SDL_image:  An example image loading library for use with SDL
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
--]]

--[[
	Image
	---------------------------------------------------------------------------------
		success 	= SDL.Image.Init( flags )
					  SDL.Image.Quit()
					  
	Surface
	---------------------------------------------------------------------------------
		surface 	= SDL.Surface.Load( fileOrRWops [, type] )
		success 	= SDL.Surface.SaveJPG( surface, fileOrRWops, quality )
		success 	= SDL.Surface.SavePNG( surface, fileOrRWops )
	
	Testure
	---------------------------------------------------------------------------------
		texture 	= SDL.Render.LoadTexture( renderer, fileOrRWops [, type] )
		texture 	= SDL.Texture.Load( renderer, fileOrRWops [, type] )
		
	Version
	---------------------------------------------------------------------------------
		bool 					= SDL.Version.AtLeastImage( major, minor, patch )
		major,minor,patch,num 	= SDL.Version.GetImage()
--]]

------------------------------------------------------------------------------Image
SupportedFormat:
"TGA", "CUR", "ICO", "BMP", "GIF", "JPG", "LBM", "PCX", "PNG", "PNM", "SVG", 
"TIF", "XCF", "XPM", "XV", "WEBP", "JXL", "AVIF", "EVERYTHING"

success = SDL.Image.Init( flags )
--[[
	Initialize by loading support as indicated by the flags.
	
	You may call this multiple times, which will actually require you to call
	SDL.Image.Quit just once to clean up.
	
	/param flags		SupportedFormat-value or "EVERYTHING"
	/returns success	true on success, false on failure
--]]

SDL.Image.Quit()
--[[
	This function cleans up all dynamically loaded library handles, freeing memory. 
	If support is required again it will be initialized again.
--]]

----------------------------------------------------------------------------Surface
surface = SDL.Surface.Load( fileOrRWops [, type] )
--[[
	Load file for use as an image in a new surface. 
	
	This can load all supported image files. It is best to call this outside of 
	event loops, and rather keep the loaded images around until you are really 
	done with them, as disk speed and image conversion to a surface is not that 
	speedy. Don't forget to SDL.Surface.Free the returned surface object when you 
	are through with it.
	
	/param fileOrRWops	filename or RWops object
	/param type			SupportedFormat-value, optional 
						(the file extension used as the type string)
	/returns surface	a surface object
--]]

success = SDL.Surface.SaveJPG( surface, fileOrRWops, quality )
--[[
	save a surface as JPG file
	
	/param surface		a surface object
	/param fileOrRWops	filename or RWops object
	/param quality		Quality 0-100
	/returns			true on success or false on failure
--]]

success = SDL.Surface.SavePNG( surface, fileOrRWops )
--[[
	save a surface as PNG file
	
	/param surface		a surface object
	/param fileOrRWops	filename or RWops object
	/returns			true on success or false on failure
--]]

---------------------------------------------------------------------------Renderer
texture = SDL.Render.LoadTexture( renderer, fileOrRWops [, type] )
-- texture = SDL.Texture.Load( renderer, fileOrRWops [, type] )
--[[
	Load an image directly into a render texture.
	
	/param renderer		a renderer object
	/param fileOrRWops	filename or RWops object
	/param type			SupportedFormat-value, optional 
						(the file extension used as the type string)
	/returns surface	a surface object
--]]

----------------------------------------------------------------------------Version
major,minor,patch,num = SDL.Version.Get()
--[[

	Get the version of SDL that is linked against your program.

	This function may be called safely at any time, even before SDL.Init().

	\returns major 	major version
	\returns minor	minor version
	\returns patch	patch version
	\returns num	version numbers into a numeric value: (1,2,3) -> (1203)
--]]

bool = SDL.Version.AtLeast( major, minor, patch )
--[[
	This will evaluate to true if with SDL at least major.minor.patch.

	\param major 	major version
	\param minor	minor version
	\param patch	patch version
	\returns bool	true if with SDL at least major.minor.patch
--]]
