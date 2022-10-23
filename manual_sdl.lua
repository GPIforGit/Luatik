
missing:
SDL.Window.SetHitBox( window, surface )
SDL.Event.Push - kennt nur quit!
 SDL_TEXTEDITING_EXT - event fehlt(events.h)
 SDL_JoyBatteryEvent jbattery - event fehlt (events.h)
 SDL_GameControllerPath / SDL_GameControllerPathForIndex (gamecontroller.h)
 SDL_GameControllerGetProductVersion(gamecontroller.h)
 joystick.h - fehlt auch...
 guid.h
 f-varianten fehlen - rect.h
 SDL_GetRenderer - render.h
 stdinc.h - overflow?
 SDL_GetTouchName - touch.h
 ttf.h
 SDL_GetPointDisplayIndex / SDL_GetRectDisplayIndex - video.h
 
 
 
 
 

--[[  
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

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
	Init
	---------------------------------------------------------------------------------
		success 	= SDL.Init( flags )
					  SDL.Quit()
					  
	BlendMode
	---------------------------------------------------------------------------------
		BlendMode 	= SDL.BlendMode.ComposeCustom( srcColorFactor, dstColorFactor, colorOperation, srcAlphaFactor, dstAlphaFactor, alphaOperation)
		
	Clipboard
	---------------------------------------------------------------------------------
		text 		= SDL.Clipboard.GetText()
		success 	= SDL.Clipboard.HasText()
		success 	= SDL.Clipboard.SetText( text )
		surface		= SDL.Clipboard.GetSurface()  -- return surface or nil - WARNING alpha is set to 0
		
	Data
	---------------------------------------------------------------------------------
		value 		= data:get8(pos)
		value 		= data:get16(pos)
		value 		= data:get32(pos)
		value 		= data:get64(pos)
		value 		= data:getu8(pos)
		value 		= data:getu16(pos)
		value 		= data:getu32(pos)
		value 		= data:getu64(pos)
		value 		= data:set8(pos)
		value 		= data:set16(pos)
		value 		= data:set32(pos)
		value 		= data:set64(pos)
		value 		= data:setu8(pos)
		value 		= data:setu16(pos)
		value 		= data:setu32(pos)
		value 		= data:setu64(pos)
		
	Error
	---------------------------------------------------------------------------------
					  SDL.Error.Clear()
		msg 		= SDL.Error.Get()
					  SDL.Error.Set(message)
					  
	Event
	---------------------------------------------------------------------------------
		event 		= SDL.Event.Poll()
					  SDL.Event.Pump()
		success 	= SDL.Event.Push( {event} )
		type 		= SDL.Event.Register( numevents )
		oldstate 	= SDL.Event.State( type, state )
		event 		= SDL.Event.Wait( [timeout] )
		
	Filesystem
	---------------------------------------------------------------------------------
		path 		= SDL.Filesystem.GetBasePath()
		path 		= SDL.Filesystem.GetPrefPath()
		
	GameController
	---------------------------------------------------------------------------------
		bool 		= SDL.GameController.AddMapping( string )
		count 		= SDL.GameController.AddMappingFromFile( fileOrRWops )
					  SDL.GameController.Close( GameController )
		oldstate 	= SDL.GameController.EventState( state )
	 GameController = SDL.GameController.FromPlayerIndex( index )
		bool 		= SDL.GameController.GetAttached( GameController )
		state 		= SDL.GameController.GetAxis( GameController, axis )
		state 		= SDL.GameController.GetButton( GameController, button )		
		Joystick 	= SDL.GameController.GetJoystick( GameController )
		string 		= SDL.GameController.GetMapping( GuidOrGameControllerOrJoyIndex )
		string 		= SDL.GameController.GetMappingForIndex( index )
		Name 		= SDL.GameController.GetName( GameController )
		count 		= SDL.GameController.GetNumMappings()
		count 		= SDL.GameController.GetNumTouchpads( GameController )
		count 		= SDL.GameController.GetNumTouchpadFingers( GameController, index)
		index 		= SDL.GameController.GetPlayerIndex( GameController )
		product 	= SDL.GameController.GetProduct( GameController )
		productver  = SDL.GameController.GetProductVersion( GameController )
		x, y, z 	= SDL.GameController.GetSensorData( GameController, type )
		rate 		= SDL.GameController.GetSensorDataRate( GameController, type )
		success 	= SDL.GameController.SetSensorEnable( Gamecontroller, type, bool )
		serial 		= SDL.GameController.GetSerial( GameController )
 state,x,y,pressure = SDL.GameController.GetTouchpadFinger(GameController,i,finger)
		type 		= SDL.GameController.GetType( GameControllerOrJoyIndex )
		vendor		= SDL.GameController.GetVendor( GameController )
		bool 		= SDL.GameController.HasAxis( GameController, axis )
		bool 		= SDL.GameController.HasButton( GameController, button )
		bool 		= SDL.GameController.HasLED( GameController )
		bool 		= SDL.GameController.HasRumble( GameController )
		bool 		= SDL.GameController.HasRumbleTriggers( GameController )
		bool 		= SDL.GameController.HasSensor( GameController, type )
		bool 		= SDL.GameController.Is( joystick_index )
		bool 		= SDL.GameController.IsSensorEnabled( Gamecontroller, type )
	 GameController = SDL.GameController.Open( joystick_index )
	 success 		= SDL.GameController.Rumble( GameController, low, high, ms )
	 success 		= SDL.GameController.RumbleTriggers( GameController, left, right, ms )
	 success 		= SDL.GameController.SetLED( GameController, r, g, b )
					  SDL.GameController.SetPlayerIndex( GameController, index )
					  SDL.GameController.Update()

	Gesture
	---------------------------------------------------------------------------------
	
		
	Hints
	---------------------------------------------------------------------------------
					  SDL.Hint.Clear()
		value		= SDL.Hint.Get( name )
		success 	= SDL.Hint.Set( name, value [,priority] )
		success		= SDL.Hint.Reset( name )
		
	Joystick
	---------------------------------------------------------------------------------
		index 		= SDL.Joystick.AttachVirtual( type, naxes, nbuttons, nhats )
		success 	= SDL.Joystick.Close( joystick )
		success 	= SDL.Joystick.DetachVirtual( index )
		oldstate 	= SDL.Joystick.EventState( state )
		joystick 	= SDL.Joystick.FromPlayerIndex( player_index )
		bool 		= SDL.Joystick.GetAttached( joystick )
		value 		= SDL.Joystick.GetAxis( joystick, axis )
		value 		= SDL.Joystick.GetAxisInitalState( joystick, axis )
		dx, dy 		= SDL.Joystick.GetBall( joystick, ball )
		state 		= SDL.Joystick.GetButton( joystick, button )
		guid 		= SDL.Joystick.GetGuid( indexOrJoy )
		value 		= SDL.Joystick.GetHat( joystick, hat )
		name 		= SDL.Joystick.GetName( indexOrJoy )
		count 		= SDL.Joystick.GetNum()		
		num 		= SDL.Joystick.GetNumAxes( joystick )
		num 		= SDL.Joystick.GetNumBalls( joystick )
		num 		= SDL.Joystick.GetNumButtons( joystick )
		num 		= SDL.Joystick.GetNumHats( joystick )
		player 		= SDL.Joystick.GetPlayerIndex( indexOrJoy )
		product 	= SDL.Joystick.GetProduct( indexOrJoy )
		version 	= SDL.Joystick.GetProductVersion( indexOrJoy )
		serial 		= SDL.Joystick.GetSerial( joystick )
		type 		= SDL.Joystick.GetType( indexOrJoy )
		vendor 		= SDL.Joystick.GetVendor( indexOrJoy )
		bool 		= SDL.Joystick.HasLED( joystick )
		bool 		= SDL.Joystick.HasRumble( joystick )
		bool 		= SDL.Joystick.HasRumbleTriggers( joystick )
		bool 		= SDL.Joystick.IsVirtual( index )
		joystick 	= SDL.Joystick.Open( index )
		success 	= SDL.Joystick.Rumble( joystick, low, high, ms )
		success 	= SDL.Joystick.RumbleTriggers( joystick, left, right, ms )
					  SDL.Joystick.SetPlayerIndex( joystick, index )
		success 	= SDL.Joystick.SetLED( joystick, r, g, b )
		success 	= SDL.Joystick.SetVirtualAxis( joystick, axis, value )
		success 	= SDL.Joystick.SetVirtualButton( joystick, button, value )
		success 	= SDL.Joystick.SetVirtualHat( joystick, hat, value )
					  SDL.Joystick.Update()	
					  
	Keyboard
	---------------------------------------------------------------------------------
		window 		= SDL.Keyboard.GetFocus()
		key 		= SDL.Keyboard.GetKeyFromScancode( scancode )
		name 		= SDL.Keyboard.GetKeyName( key )
		key 		= SDL.Keyboard.GetKeyFromName( name )
		value 		= SDL.Keyboard.GetKeyValue( keycode )
		modstate 	= SDL.Keyboard.GetModState()
		scancode 	= SDL.Keyboard.GetScancodeFromKey( key )
		scancode 	= SDL.Keyboard.GetScancodeFromName( name )
		name 		= SDL.Keyboard.GetScancodeName( scancode )
		value 		= SDL.Keyboard.GetScancodeValue( scancode )
		state 		= SDL.Keyboard.GetState( scancode )
		bool 		= SDL.Keyboard.HasScreenKeyboardSupport()
		bool 		= SDL.Keyboard.IsScreenKeyboardShown( window )
					  SDL.Keyboard.Reset()
					  SDL.Keyboard.SetModState(modstate)
		bool 		= SDL.TextInput.IsActive()
					  SDL.TextInput.SetRect( rect )
					  SDL.TextInput.Start()
					  SDL.TextInput.Stop()
					  
	Locale
	---------------------------------------------------------------------------------
		locales 	= SDL.Locale.GetPreferred()
		
	MessageBox
	---------------------------------------------------------------------------------
		button		= SDL.MessageBox.Show( msg )
		success		= SDL.MessageBox.ShowSimple(flag, title, msg, window)
		
	Misc
	---------------------------------------------------------------------------------
		success 	= SDL.OpenURL ( url )
		
	Mouse
	---------------------------------------------------------------------------------
		cursor 		= SDL.Cursor.Create( surface, hot_x, hot_y)
		cursor 		= SDL.Cursor.Create( SystemCursor )
					  SDL.Cursor.Free( cursor )
		cursor 		= SDL.Cursor.Get()
		cursor 		= SDL.Cursor.GetDefault()
					  SDL.Cursor.Set( cursor )
		state 		= SDL.Cursor.Show( toggle )
		success 	= SDL.Mouse.Capture ( state )
		window 		= SDL.Mouse.GetFocus()
		button,x,y	= SDL.Mouse.GetGlobalState()
		state 		= SDL.Mouse.GetRelatvieMode ()
		button,x,y	= SDL.Mouse.GetRelativeState()
		success 	= SDL.Mouse.SetRelativeMode( state )
		success 	= SDL.Mouse.WarpGlobal( x, y )
					  SDL.Mouse.WarpInWindow( win, x, y )
					  
	PixelFormat
	---------------------------------------------------------------------------------
		PixelFormat = SDL.PixelFormat.Alloc( PixelFormatEnum)
					  SDL.PixelFormat.Free( PixelFormat )
		r, g, b 	= SDL.PixelFormat.GetRGB( PixelFormat, pixel )
		r, g, b, a 	= SDL.PixelFormat.GetRGBA( PixelFormat, pixel )
		pixel 		= SDL.PixelFormat.MapRGB( PixelFormat, r, g, b )
		pixel 		= SDL.PixelFormat.MapRGBA( PixelFormat, r, g, b, a )
		
	Power
	---------------------------------------------------------------------------------
		state, sec, pct = SDL.Power.GetInfo()
		
	Rect
	---------------------------------------------------------------------------------
		bool 		= SDL.Rect.ContainsPoint( Rect, Point )
		bool 		= SDL.Rect.Empty( Rect1 )
		rect 		= SDL.Rect.EnclosePoints( points, clip )
		bool 		= SDL.Rect.Equals ( Rect1, Rect2 )
		x1,y1,x2,y2 = SDL.Rect.IntersectLine( Rect, x1, y1, x2, y2)
		intersection= SDL.Rect.Intersection ( Rect1, Rect2 )
		union 		= SDL.Rect.Union( Rect1, Rect2 )
		
	Renderer
	---------------------------------------------------------------------------------
		success 	= SDL.Render.Clear( renderer )
		success 	= SDL.Render.Copy( render, texture, srcRect, dstRect )
		success 	= SDL.Render.CopyEx( render, texture, srcRect, dstRect, angle, center, flip)
		Renderer 	= SDL.Render.Create( window [, index, flags] )
		Renderer 	= SDL.Render.CreateSoftware( surface )
		texture 	= SDL.Render.CreateTexture( renderer, format, access, w, h )
		texture 	= SDL.Render.CreateTexture( renderer, surface )
					  SDL.Render.Destroy( renderer )
		success		= SDL.Render.DrawLine( render, x1, y1, x2, y2 )
		success 	= SDL.Render.DrawLines( renderer, points )
		success 	= SDL.Render.DrawPoint( renderer, x, y )
		success 	= SDL.Render.DrawPoints( renderer, points )
		success 	= SDL.Render.DrawRect( renderer, rect )
		success 	= SDL.Render.DrawRects( renderer, rect )
		success 	= SDL.Render.FillRect( renderer, rect )
		success 	= SDL.Render.FillRects( renderer, rects )
		success 	= SDL.Render.Geometry( render, texture, vertices, indices )
		Renderer 	= SDL.Render.Get( window )
		rect 		= SDL.Render.GetClipRect( renderer )
		r, g, b,a 	= SDL.Render.GetDrawColor( renderer )				
		info		= SDL.Render.GetDriverInfo(index)
		info 		= SDL.Render.GetInfo( renderer )
		state 		= SDL.Render.GetIntegerScale( renderer )
		w, h 		= SDL.Render.GetLogicalSize( renderer )
	   scaleX,scaleY= SDL.Render.GetScale( renderer )
		texture 	= SDL.Render.GetTarget( renderer )
		num 		= SDL.Render.GetNumDrivers()
		w, h 		= SDL.Render.GetOutputSize( renderer )
		rect 		= SDL.Render.GetViewport( renderer )
		winX, winY 	= SDL.Render.LogicalToWindow( renderer, logicalX, logicalY)
					  SDL.Render.Present( renderer )
		surface 	= SDL.Render.ReadPixels( renderer, format  )
		success 	= SDL.Render.SetClipRect( renderer, rect )
		success 	= SDL.Render.SetDrawBlendMode( renderer, BlendMode )
		success 	= SDL.Render.SetDrawColor( renderer, r, g, b, a )
		success 	= SDL.Render.SetDrawColor( renderer, color )
		success 	= SDL.Render.SetIntegerScale( renderer, state )
		success 	= SDL.Render.SetLogicalSize( renderer, w, h )
		success 	= SDL.Render.SetScale( renderer, scaleX, scaleY )
		success 	= SDL.Render.SetTarget( renderer, texture )
		success 	= SDL.Render.SetViewport( renderer, rect )
		success 	= SDL.Render.SetVSync( renderer, state )
		logiX, logiY= SDL.Render.WindowToLogical( renderer, windowX, windowY )
		bool 		= SDL.Render.TargetSupported( renderer )
		Renderer 	= SDL.Surface.CreateSoftwareRenderer ( surface )
		texture 	= SDL.Texture.Create( renderer, format, w, h )
		texture 	= SDL.Texture.Create( renderer, surface )
					  SDL.Texture.Destroy( texture )
		alpha 		= SDL.Texture.GetAlphaMod( texture )
		blendMode 	= SDL.Texture.GetBlendMode( texture )
		r,g,b 		= SDL.Texture.GetColorMod( texture )		
		scaleMode 	= SDL.Texture.GetScaleMode( texture )
		data 		= SDL.Texture.GetUserData( texture )
		data, pitch = SDL.Texture.Lock( texture, rect )
		surface 	= SDL.Texture.LockToSurface( texture, rect )
	format,access,w,h=SDL.Texture.Query( texture )
		success 	= SDL.Texture.SetAlphaMod( texture, alpha )
		success 	= SDL.Texture.SetBlendMode( texture, blendmode )
		success 	= SDL.Texture.SetColorMod( texture, r, g, b )
		success 	= SDL.Texture.SetScaleMode( texture, scaleMode )
		success 	= SDL.Texture.SetUserData( texture, data )		
					  SDL.Texture.Unlock( texture )
		Renderer 	= SDL.Window.CreateRenderer( window, index [, flags] )
		Renderer 	= SDL.Window.GetRenderer( window )
		
	RW
	---------------------------------------------------------------------------------
		success		= SDL.RW.Close( RWops )
		string 		= SDL.RW.Load( File )
		RWops 		= SDL.RW.Open( file, mode )
		string 		= SDL.RW.ReadString( RWops, size )
		int 		= SDL.RW.ReadU8( RWops )
		int			= SDL.RW.ReadLEU16( RWops )
		int 		= SDL.RW.ReadBEU16( RWops )
		int 		= SDL.RW.ReadLEU32( RWops )
		int 		= SDL.RW.ReadBEU32( RWops )
		int 		= SDL.RW.ReadS8( RWops )
		int 		= SDL.RW.ReadLES16( RWops )
		int 		= SDL.RW.ReadBES16( RWops )
		int 		= SDL.RW.ReadLES32( RWops )
		int 		= SDL.RW.ReadBES32( RWops )
		int 		= SDL.RW.ReadLES64( RWops )
		int 		= SDL.RW.ReadBES64( RWops )
		number 		= SDL.RW.ReadLEFloat( RWops )
		number 		= SDL.RW.ReadBEFloat( RWops )
		number 		= SDL.RW.ReadLEDouble( RWops )
		number 		= SDL.RW.ReadBEDouble( RWops )
		written 	= SDL.RW.Save( File, string )
		pos 		= SDL.RW.Seek( RWops, offset, whence )
		size 		= SDL.RW.Size( RWops )
		pos 		= SDL.RW.Tell( RWops )
		written 	= SDL.RW.WriteString( RWops, string )
		success 	= SDL.RW.Write8( RWops, int )
		success 	= SDL.RW.WriteLE16( RWops, int )
		success 	= SDL.RW.WriteBE16( RWops, int )
		success 	= SDL.RW.WriteLE32( RWops, int )
		success 	= SDL.RW.WriteBE32( RWops, int )
		success 	= SDL.RW.WriteLE64( RWops, int )
		success 	= SDL.RW.WriteBE64( RWops, int )
		success 	= SDL.RW.WriteLEFloat( RWops, number )
		success 	= SDL.RW.WriteBEFloat( RWops, number )
		success 	= SDL.RW.WriteLEDouble( RWops, number )
		success 	= SDL.RW.WriteBEDouble( RWops, number )
		
	Sensor
	---------------------------------------------------------------------------------
					  SDL.Sensor.Close( Sensor )
		x, y, z 	= SDL.Sensor.GetData( Sensor )
		name 		= SDL.Sensor.GetName( indexOrSensor )
		num 		= SDL.Sensor.GetNum()
		Sensor 		= SDL.Sensor.Open( index )
		SensorType 	= SDL.Sensor.GetType( indexOrSensor )
					  SDL.Sensor.Update()
					  
	Surface
	---------------------------------------------------------------------------------
		success 	= SDL.Surface.Blit( Surface1, Rect, Surface2, Point)
		success 	= SDL.Surface.BlitScaled( Surfac1, Rect1, Surface2, Rect2 )
		Surface 	= SDL.Surface.Convert( Surface, format )
		surface 	= SDL.Surface.CreateRGB ( width, height, format )
		Surface 	= SDL.Surface.Duplicate( Surface )
		success 	= SDL.Surface.FillRect ( Surface, Rect, color )
					  SDL.Surface.Free( Surface )
		alpha 		= SDL.Surface.GetAlphaMod( Surface )
		BlendMode 	= SDL.Surface.GetBlendMode( Surface )
		Rect 		= SDL.Surface.GetClip( Surface )
		r, g, b 	= SDL.Surface.GetColorMod( Surface )
		key 		= SDL.Surface.GetColorKey( Surface )
		PixelFormat = SDL.Surface.GetPixelFormat( Surface )
		data 		= SDL.Surface.GetPixels( Surface )
		w, h, pitch = SDL.Surface.GetSize( Surface )
		mode 		= SDL.Surface.GetYUVConversionMode()
		mode 		= SDL.Surface.GetYUVConversionModeForResolution(w, h)
		rle 		= SDL.Surface.HasRLE( Surface )
		Surface 	= SDL.Surface.LoadBMP( fileOrRWops )
		success 	= SDL.Surface.Lock( Surface )
		success 	= SDL.Surface.SaveBMP( Surface, fileOrRWops )
		success 	= SDL.Surface.SetAlphaMod( Surface, alpha )
		success 	= SDL.Surface.SetBlendMode( Surface, BlendMode )
		intersect 	= SDL.Surface.SetClip( Surface, Rect )
		success 	= SDL.Surface.SetColorKey( Surface, flag, key )
		success 	= SDL.Surface.SetColorMod( Surface, r, g, b )
		success 	= SDL.Surface.SetRLE( Surface, flag )
					  SDL.Surface.SetYUVConversionMode( mode )
		success 	= SDL.Surface.SoftStretch( Surfac1, Rect1, Surface2, Rect2 )
					  SDL.Surface.Unlock( Surface )
					  
	Time
	---------------------------------------------------------------------------------
					  SDL.Time.Delay( ms )
		count 		= SDL.Time.GetPerformanceCounter()
		frequency  	= SDL.Time.GetPerformanceFrequency()
		time 		= SDL.Time.Get()
		ticks 		= SDL.Time.GetTicks()
	
	Touch
	---------------------------------------------------------------------------------
					  SDL.Touch.Close( touchID )
	 x,y,pressure,ID= SDL.Touch.GetFinger( touchID, index )
		count 		= SDL.Touch.GetNum()
		count 		= SDL.Touch.GetNumFingers( touchID )
		touchID 	= SDL.Touch.Open( index )
	
	Version
	---------------------------------------------------------------------------------
		bool 		= SDL.Version.AtLeast( major, minor, patch )
		major,minor,patch,num = SDL.Version.Get()
		
	Video
	---------------------------------------------------------------------------------	
		rect 		= SDL.Display.GetBounds( index )
		DisplayMode = SDL.Display.GetDesktopMode( index )
	 ddpi,hdpi,vdpi = SDL.Display.GetDPI( index )
		name 		= SDL.Display.GetName( index )
		num 		= SDL.Display.GetNum()
		opacity 	= SDL.Window.GetOpacity( window )
		orientation = SDL.Display.GetOrientation( index )
		rect 		= SDL.Display.GetUsableBounds( index )	
					  SDL.ScreenSaver.Enabled()
					  SDL.ScreenSaver.Disabled()
		bool 		= SDL.ScreenSaver.IsEnable()		
top,left,bottom,right=SDL.Window.GetBordersSize( window )
		window 		= SDL.Window.Create(title, x, y, w, h, flags)
					  SDL.Window.Destroy( window )
		success 	= SDL.Window.Flash( window, operation )
		value 		= SDL.Window.GetData( window, name )
		index 		= SDL.Window.GetDisplayIndex( window )
		flags 		= SDL.Window.GetFlags( window )
		grab 		= SDL.Window.GetGrab( window )
		window 		= SDL.Window.GetGrabbed()
		grab		= SDL.Window.GetKeyboardGrab( window )
		max_w, max_h= SDL.Window.GetMaximumSize( window )
		min_w, min_h= SDL.Window.GetMinimumSize( window )
		grab		= SDL.Window.GetMouseGrab( window )
		rect 		= SDL.Window.GetMouseRect( window, rect )
		ShapeMode [,binarization] [,color] = SDL.Window.GetShape( window )
		Surface 	= SDL.Window.GetSurface( window )
		PixelFormat = SDL.Window.GetPixelFormat( window )
		x, y 		= SDL.Window.GetPosition( window )
		w, h 		= SDL.Window.GetSize( window )
		title 		= SDL.Window.GetTitle( window )
					  SDL.Window.Hide( window )
					  SDL.Window.Maximize( window )
					  SDL.Window.Minimize( window )
		success 	= SDL.Window.ModalFor( modal_window, parent_window )
					  SDL.Window.Raise( window )
					  SDL.Window.Restore( window )
					  SDL.Window.SetAlwaysOnTop( window, state )
					  SDL.Window.SetBordered( window, state )
		oldvalue 	= SDL.Window.SetData( window, name, value )
		success 	= SDL.Window.SetFullscreen( window, flags )
					  SDL.Window.SetGrab( window, state )
					  SDL.Window.SetIcon( window, surface )
		success 	= SDL.Window.SetInputFocus( window )
					  SDL.Window.SetKeyboardGrab( window, state )
					  SDL.Window.SetMaximumSize( window, max_w, max_h )
					  SDL.Window.SetMinimumSize( window, min_w, min_h )
					  SDL.Window.SetMouseGrab( window, state )
		success 	= SDL.Window.SetMouseRect( window, rect )
		success 	= SDL.Window.SetOpacity( window, opacity )
					  SDL.Window.SetPosition( window, x, y )
					  SDL.Window.SetResizable( window, state )
		success 	= SDL.Window.SetShape( window, shape, ShapeMode [,binarization][,color] )
					  SDL.Window.SetSize( window, w, h )
					  SDL.Window.SetTitle( window, title )
					  SDL.Window.Show( window )
		success 	= SDL.Window.UpdateSurface( window )

--]]

--------------------------------------------------------------------------------Init
Init:
"TIMER", "AUDIO", "VIDEO", "JOYSTICK", "HAPTIC", "GAMECONTROLLER", "EVENTS", 
"SENSOR", "EVERYTHING"

success = SDL.Init( flags )
--[[
	Initialize the SDL library.

	"flags" may be any of the following combination together:

	- "TIMER": 			timer subsystem
	- "AUDIO": 			audio subsystem
	- "VIDEO": 			video subsystem; automatically initializes the events
						subsystem
	- "JOYSTICK": 		joystick subsystem; automatically initializes the
						events subsystem
	- "HAPTIC": 		haptic (force feedback) subsystem
	- "GAMECONTROLLER": controller subsystem; automatically
						initializes the joystick subsystem
	- "EVENTS": 		events subsystem
	- "EVERYTHING":		all of the above subsystems

	
	\param flags 		subsystem initialization flags
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]


SDL.Quit()
--[[
	Clean up all initialized subsystems.

	It is safe to call this	function even in the case of errors in initialization.
--]]

---------------------------------------------------------------------------BlendMode
BlendMode:
"NONE", "BLEND", "ADD", "MOD", "MUL", "INVALID"


BlendOperation:
"ADD", "SUBTRACT", "REV_SUBTRACT", "MINIMUM", "MAXIMUM"

BlendFactor:
"ZERO","ONE","SRC_COLOR","ONE_MINUS_SRC_COLOR","SRC_ALPHA","ONE_MINUS_SRC_ALPHA","DST_COLOR","ONE_MINUS_DST_COLOR","DST_ALPHA","ONE_MINUS_DST_ALPHA"


BlendMode		-- a string
--[[
	"NONE"			no blending
						dstRGBA = srcRGBA 
    "BLEND"			alpha blending
						dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
						dstA = srcA + (dstA * (1-srcA))
    "ADD"			additive blending
						dstRGB = (srcRGB * srcA) + dstRGB
						dstA = dstA
    "MOD"			color modulate
						dstRGB = srcRGB * dstRGB
						dstA = dstA
    "MUL"			color multiply
						dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
						dstA = (srcA * dstA) + (dstA * (1-srcA)) */
--]]


BlendMode = SDL.BlendMode.ComposeCustom( srcColorFactor, dstColorFactor, colorOperation, srcAlphaFactor, dstAlphaFactor, alphaOperation)
--[[
	Compose a custom blend mode for renderers.

	The functions SDL.Render.SetDrawBlendMode and SDL.Texture.SetBlendMode accept
	the BlendMode returned by this function if the renderer supports it.

	A blend mode controls how the pixels from a drawing operation (source) get
	combined with the pixels from the render target (destination). First, the
	components of the source and destination pixels get multiplied with their
	blend factors. Then, the blend operation takes the two products and
	calculates the result that will get stored in the render target.

	Expressed in pseudocode, it would look like this:

		dstRGB = colorOperation(srcRGB * srcColorFactor, dstRGB * dstColorFactor);
		dstA = alphaOperation(srcA * srcAlphaFactor, dstA * dstAlphaFactor);

	Where the functions `colorOperation(src, dst)` and `alphaOperation(src, dst)` 
	can return one of the following:

		- src + dst
		- src - dst
		- dst - src
		- min(src, dst)
		- max(src, dst)

	The red, green, and blue components are always multiplied with the first,
	second, and third components of the SDL_BlendFactor, respectively. The
	fourth component is not used.

	The alpha component is always multiplied with the fourth component of the
	BlendFactor. The other components are not used in the alpha
	calculation.
 
	Support for these blend modes varies for each renderer. To check if a
	specific BlendMode is supported, create a renderer and pass it to
	either SDL.Render.SetDrawBlendMode or SDL.Texture.SetBlendMode. They will
	return with an error if the blend mode is not supported.
	
	Operation
		"ADD"			dst + src: supported by all renderers
		"SUBTRACT"		dst - src : supported by D3D9, D3D11, OpenGL, OpenGLES
		"REV_SUBTRACT"	src - dst : supported by D3D9, D3D11, OpenGL, OpenGLES
		"MINIMUM"		min(dst, src) : supported by D3D11
		"MAXIMUM"		max(dst, src) : supported by D3D11
	
	Factor
		"ZERO"						0, 0, 0, 0
		"ONE"						1, 1, 1, 1
		"SRC_COLOR"					srcR, srcG, srcB, srcA
		"ONE_MINUS_SRC_COLOR"		1-srcR, 1-srcG, 1-srcB, 1-srcA
		"SRC_ALPHA"					srcA, srcA, srcA, srcA
		"ONE_MINUS_SRC_ALPHA"		1-srcA, 1-srcA, 1-srcA, 1-srcA
		"DST_COLOR"					dstR, dstG, dstB, dstA
		"ONE_MINUS_DST_COLOR"		1-dstR, 1-dstG, 1-dstB, 1-dstA
		"DST_ALPHA"					dstA, dstA, dstA, dstA
		"ONE_MINUS_DST_ALPHA"		1-dstA, 1-dstA, 1-dstA, 1-dstA

	\param srcColorFactor 	the Factor applied to the red, green, and
							blue components of the source pixels
	\param dstColorFactor 	the Factor applied to the red, green, and
							blue components of the destination pixels
	\param colorOperation 	the Operation used to combine the red,
							green, and blue components of the source and
							destination pixels
	\param srcAlphaFactor 	the Factor applied to the alpha component of
							the source pixels
	\param dstAlphaFactor 	the Factor applied to the alpha component of
							the destination pixels
	\param alphaOperation 	the Operation used to combine the alpha
							component of the source and destination pixels
	\returns BlendMode		an BlendMode that represents the chosen factors and
							operations or nil.
--]]

---------------------------------------------------------------------------Clipboard

success = SDL.Clipboard.SetText( text )
--[[
	Put UTF-8 text into the clipboard.

	\param text 		the text to store in the clipboard
	\returns success	true on success or false on failure; 
						call SDL_GetError() for more information.
--]]

text = SDL.Clipboard.GetText()
--[[
	Get UTF-8 text from the clipboard.
	
	This functions returns empty string if there was not enough memory left for
	a copy of the clipboard's content.

	\returns text	the clipboard text on success or an empty string on failure; 
					call SDL_GetError() for more information. 
--]]

success = SDL.Clipboard.HasText()
--[[
	Query whether the clipboard exists and contains a non-empty text string.

	\returns success	true if the clipboard has text, or false if it does not.
--]]

--------------------------------------------------------------------------------Data
data			-- a data object to manipulate memory directory
				-- warning there is no size-check here!

data:set8(pos, value)		-- set a value on pos (position is always in bytes!)
data:set16(pos, value)		-- set a value on pos (position is always in bytes!)
data:set32(pos, value)		-- set a value on pos (position is always in bytes!)
data:set64(pos, value)		-- set a value on pos (position is always in bytes!)

data:setu8(pos, value)		-- set a value on pos (position is always in bytes!)
data:setu16(pos, value)		-- set a value on pos (position is always in bytes!)
data:setu32(pos, value)		-- set a value on pos (position is always in bytes!)
data:setu64(pos, value)		-- set a value on pos (position is always in bytes!)

value = data:get8(pos)		-- get a value on pos (position is always in bytes!)
value = data:get16(pos)		-- get a value on pos (position is always in bytes!)
value = data:get32(pos)		-- get a value on pos (position is always in bytes!)
value = data:get64(pos)		-- get a value on pos (position is always in bytes!)

value = data:getu8(pos)		-- get a value on pos (position is always in bytes!)
value = data:getu16(pos)	-- get a value on pos (position is always in bytes!)
value = data:getu32(pos)	-- get a value on pos (position is always in bytes!)
value = data:getu64(pos)	-- get a value on pos (position is always in bytes!)

-------------------------------------------------------------------------------Error

SDL.Error.Set( message )
--[[
	Set the SDL error message for the current thread.

	Calling this function will replace any previous error message that was set.
	
	\param message	error-message - don't use %
--]]

msg = SDL.Error.Get()
--[[
	Retrieve a message about the last error that occurred on the current
	thread.

	It is possible for multiple errors to occur before calling SDL_GetError().
	Only the last error is returned.

	The message is only applicable when an SDL function has signaled an error.
	You must check the return values of SDL function calls to determine when to
	appropriately call SDL_GetError(). You shouldnot* use the results of
	SDL_GetError() to decide if an error has occurred! Sometimes SDL will set
	an error string even when reporting success.

	SDL *willnot* clear the error string for successful API calls. *Youmust*
	check return values for failure cases before you can assume the error
	string applies.

	Error strings are set per-thread, so an error set in a different thread
	will not interfere with the current thread's operation.


	\returns msg	a message with information about the specific error that 
					occurred, or an empty string if there hasn't been an error message set since the last call to SDL.Error.Clear(). The message is only applicable when an SDL function has signaled an error. You must check the return values of SDL function calls to determine when to	appropriately call SDL_GetError().
--]]

SDL.Error.Clear()
--[[
	Clear any previous error message for this thread.
--]]

-------------------------------------------------------------------------------Event
event = {
	timestamp, -- milliseconds	
	type, 
		-- "DISPLAYEVENT"			Display state change
			display, -- displayid
			event, 
				-- "ORIENTATION"	Display orientation has changed to
				orientation,
				-- "CONNECTED"		Display has been added to the system
				-- "DISCONNECTED"	Display has been removed from the system
			
		-- "WINDOWEVENT",			Window state change
			window, -- window-object
			event,	
				-- "SHOWN"			Window has been shown			
				-- "HIDDEN"			Window has been hidden
				-- "EXPOSED"		Window has been exposed and should be redrawn
				-- "MOVED"			Window has been moved to
					x,
					y,
				-- "RESIZED"		Window has been resized to
					w,
					h,
				-- "SIZE_CHANGED"	The window size has changed, either as
                -- 					a result of an API call or through the
                -- 					system or user changing the window size.
					w,
					h,
				-- "MINIMIZED"		Window has been minimized
				-- "MAXIMIZED"		Window has been maximized
				-- "RESTORED"		Window has been restored to normal size and 
				-- 					position
				-- "ENTER" 			Window has gained mouse focus
				-- "LEAVE" 			Window has lost mouse focus
				-- "FOCUS_GAINED" 	Window has gained keyboard focus	
				-- "FOCUS_LOST" 	Window has lost keyboard focus
				-- "CLOSE"			The window manager requests that the window be 
				--					closed
				-- "TAKE_FOCUS" 	Window is being offered a focus (should 	
				--					SDL.Window.SetInputFocus() on itself or a 
				--					subwindow, or ignore)
				-- "HIT_TEST"		Window had a hit test that wasn't 
				--					SDL_HITTEST_NORMAL.
				-- "ICCPROF_CHANGED" The ICC profile of the window's display has 
				--					changed.
				-- "DISPLAY_CHANGED" Window has been moved to display
					display,
		
		-- "KEYDOWN" "KEYUP"		Key pressed / released
			window, 	-- window-object
			state,		-- true or false
			repeated,		-- Non-zero if this is a key repeat
			scancode,	-- scancode
			sym,		-- key (virtual key code)
			mod			-- current key modifiers
		
		-- "KEYMAPCHANGED"			Keymap changed due to a system event such as an
                                    -- input language or keyboard layout change.
		
		-- "TEXTEDITING"			Keyboard text editing (composition) 
			window, 	-- window-object
			text,	
			start,
			length,
			
		-- "TEXTINPUT"				Keyboard text input
			window, 	-- window-object
			text,
			
		-- "MOUSEMOTION"			Mouse motion event
			window, 	-- window-object
			which,		-- The mouse instance id, or TOUCH_MOUSE
			state,		-- The current button state ("LEFT", "RIGHT"...)
			x,			-- X coordinate, relative to window
			y,			-- Y coordinate, relative to window
			xrel,		-- The relative motion in the X direction
			yrel		-- The relative motion in the Y direction
			
		-- "MOUSEBUTTONDOWN" "MOUSEBUTTONUP"
			window, 	-- window-object
			which,		-- The mouse instance id, or TOUCH_MOUSE
			button,		-- The mouse button "LEFT", "RIGHT"...
			state,		-- true or false
			clicks,		-- 1 for single-click, 2 for double-click etc.
			x,			-- X coordinate, relative to window
			y,			-- Y coordinate, relative to window
		
		-- "MOUSEWHEEL"
			window, 	-- window-object
			which,		-- The mouse instance id, or TOUCH_MOUSE
			x,			-- The amount scrolled horizontally, positive to the right 
						-- and negative to the left
			y,			-- The amount scrolled vertically, positive away from the 
						-- user and negative toward the user
			direction,	-- "NORMAL","FLIPPED". When "FLIPPED" the values in X and Y 
						-- will be opposite. Multiply by -1 to change them back
			preciseX,	-- The amount scrolled horizontally, positive to the right 
						-- and negative to the left, with float precision
			preciseY,	-- The amount scrolled vertically, positive away from the 
						-- user and negative toward the user, with float precision
		
		-- "JOYAXISMOTION"
			which,		-- The joystick object
			axis,		-- The joystick axis index
			value,		-- the axis value (range: -1.0000 to 1.0000)
		
		-- "JOYBALLEVENT"
			which,		-- The joystick object
			ball,		-- The joystick ball index
			xrel,		-- The relative motion in the X direction
			yrel,		-- The relative motion in the Y direction
			
		-- "JOYHATMOTION"
			which,		-- The joystick object
			hat,		-- The joystick hat index
			value,		-- The hat postion value "LEFT","RIGHT"...
			
		-- "JOYBUTTONDOWN" "JOYBUTTONUP"
			which,		-- The joystick object
			button,		-- The joystick button index
			state,		-- true or false
		
		-- "JOYDEVICEADDED"
			which, 		-- The joystick device index
			
		-- "JOYDEVICEREMOVED"
			which,		-- The joystick object
		
		-- "SENSORUPDATE"
			which,      -- The sensor object
			x,			-- values from the senso
			y,			-- values from the senso
			z,			-- values from the senso
		
		-- "CONTROLLERAXISMOTION"
			which,		-- the GameController object.strokeWidth
			axis,		-- a GameControllerAxis value
			value,		-- the axis value (range: -1.0000 to 1.0000)
			
		-- "CONTROLLERBUTTONDOWN" "CONTROLLERBUTTONUP"
			which,		-- the GameController object
			button,		-- a GameControllerButton value
			state,		-- true or false
			
		-- "CONTROLLERDEVICEADDED"
			which, 		-- The joystick device index
		
		-- "CONTROLLERDEVICEREMOVED" "CONTROLLERDEVICEREMAPPED"
			which,		-- the GameController object
		
		-- "CONTROLLERTOUCHPADDOWN" "CONTROLLERTOUCHPADUP" "CONTROLLERTOUCHPADMOTION"
			which,		-- the GameController object
			touchpad,	-- The index of the touchpad
			finger,		-- The index of the finger on the touchpad
			x,			-- Normalized in the range 0...1 with 0 being on the left
			y,			-- Normalized in the range 0...1 with 0 being at the top
			pressure,	-- Normalized in the range 0...1

		-- "CONTROLLERSENSORUPDATE"
			which,		-- the GameController object
			sensor,		-- a SensorType value
			x,			-- sensor data
			y,			-- sensor data
			z,			-- sensor data
		
		-- "QUIT"					User-requested quit

		-- "FINGERMOTION", "FINGERDOWN", "SDL_FINGERUP"
			touchId,	-- The touch device id
			fingerId,	-- the finger id
			x,			-- Normalized in the range 0...1
			y,			-- Normalized in the range 0...1
			dx,			-- Normalized in the range -1...1
			dy,			-- Normalized in the range -1...1
			pressure	-- Normalized in the range 0...1
			window,		-- a window object
		
		-- "MULTIGESTURE"
			touchId,	-- The touch device id
			dTheta,		-- the amount that the fingers rotated during this motion.
			dDist,		-- the amount that the fingers pinched during this motion.
			x,			-- the normalized x coordinate of the gesture. (0..1)
			y,			-- the normalized y coordinate of the gesture. (0..1)
			numFingers,	-- the number of fingers used in the gesture.

		-- "DOLLARGESTURE", "DOLLARRECORD"
			touchId,	-- The touch device id
			gestureId,
			numFingers,
			error,
			x,			-- Normalized center of gesture
			y,			-- Normalized center of gesture
		
		-- "RENDER_TARGETS_RESET"
			-- The render targets have been reset and their contents need to be updated
		
		-- "SDL_RENDER_DEVICE_RESET"
			-- The device has been reset and all textures need to be recreated
			
		-- "LOCALECHANGED"
			-- The user's locale preferences have changed.
			
		
		-- userevent - integer
			window, 	-- window-object
			code,		-- userdefinied code
			data1,
			data2,
			
			

				
		-- "DROPBEGIN" "DROPFILE" "DROPCOMPLETE"
			window, -- window-object
			file, -- filename
					
}

SDL.Event.Pump()
--[[
	Pump the event loop, gathering events from the input devices.

	This function updates the event queue and internal input device state.

	SDL.Event.Pump() gathers all the pending input information from devices and
	places it in the event queue. Without calls to SDL.Event.Pump() no events
	would ever be placed on the queue. Often the need for calls to
	SDL.Event.Pump() is hidden from the user since SDL.Event.Poll() and
	SDL.Event.Wait() implicitly call SDL.Event.Pump(). However, if you are not
	polling or waiting for events (e.g. you are filtering them), then you must
	call SDL.Event.Pump() to force an event queue update.
--]]

event = SDL.Event.Poll()
--[[
	Poll for currently pending events.
 
	The next event is removed from the queue and stored	in the table.

	As this function may implicitly call SDL.Event.Pump(), you can only call
	this function in the thread that set the video mode.
 
	SDL.Event.Poll() is the favored way of receiving system events since it can
	be done from the main loop and does not suspend the main loop while waiting
	on an event to be posted.
	
	/returns event	event-table or empty-table if no event is available
--]]

event = SDL.Event.Wait( [timeout] )
--[[
	Wait indefinitely or until the specified timeout (in milliseconds) for the 
	next available event.

	The next event is removed from the queue and stored	in the table.
	
	/param timeout	the maximum number of milliseconds to wait for the next
					available event (optional)
	/returns event	event-table or empty-table if no event is available
--]]
 
success = SDL.Event.Push( {event} )
--[[
	Add an event to the event queue.
	
	Note: Pushing device input events onto the queue doesn't modify the state
	of the device within SDL.
	
	For pushing application-specific events, please use SDL.Event.Register() to
	get an event type that does not conflict with other code that also wants
	its own custom event types.
	
	\param event 		the event-table to be added to the queue
	\returns success	true on success or false on failure; 
						call SDL_GetError() for more information.
--]]

oldstate = SDL.Event.State( type, state )
--[[
	Set the state of processing events by type.
	
	"state" may be any of the following:
 
	- "QUERY":				returns the current processing state
	- "IGNORE"/"DISABLE" 	the event will automatically be dropped
							from the event queue and will not be filtered
	- "ENABLE": 			the event will be processed normally
	
	\param type 		the type of event: see event-table
	\param state 		how to process the event
	\returns oldstate	"DISABLE" or "ENABLE", representing the processing state
						of the event before this function makes any changes to it.
--]]

type = SDL.Event.Register( numevents )
--[[
	Allocate a set of user-defined events, and return the beginning event
	number for that set of events.

	Calling this function with "numevents" <= 0 is an error and will return -1.

	\param numevents	the number of events to be allocated
	\returns type		the beginning event number, or -1 if there are not enough
						user-defined events left.
--]]

--------------------------------------------------------------------------Filesystem
path = SDL.Filesystem.GetBasePath()
--[[
	Get the directory where the application was run from.
	
	This is not necessarily a fast call, so you should call this once near
	startup and save the string if you need it.
	
	The returned path is guaranteed to end with a path separator ('\' on
	Windows, '/' on most other platforms).
	
	\returns path	an absolute path in UTF-8 encoding to the application data
					directory.
--]]

path = SDL.Filesystem.GetPrefPath()
--[[
	Get the user-and-app-specific path where files can be written.
	
	Get the "pref dir". This is meant to be where users can write personal
	files (preferences and save games, etc) that are specific to your
	application. This directory is unique per user, per application.

	This function will decide the appropriate location in the native
	filesystem, create the directory if necessary, and return a string of the
	absolute path to the directory in UTF-8 encoding.
	
	You should assume the path returned by this function is the only safe place
	to write files (and that SDL_GetBasePath(), while it might be writable, or
	even the parent of the returned path, isn't where you should be writing
	things).
	
	Both the org and app strings may become part of a directory name, so please
	follow these rules:
	
	- Try to use the same org string (_including case-sensitivity_) for all
		your applications that use this function.
	- Always use a unique app string for each one, and make sure it never
		changes for an app once you've decided on it.
	- Unicode characters are legal, as long as it's UTF-8 encoded, but...
	- ...only use letters, numbers, and spaces. Avoid punctuation like "Game
		Name 2: Bad Guy's Revenge!" ... "Game Name 2" is sufficient.
		
	The returned path is guaranteed to end with a path separator ('\' on
	Windows, '/' on most other platforms).
	
	\param org 		the name of your organization
	\param app		the name of your application
	\returns path	a UTF-8 string of the user directory in platform-dependent
					notation. nil if there's a problem (creating directory failed,
					etc.).	
--]]

----------------------------------------------------------------------GameController
GameControllerType:
"UNKNOWN", "XBOX360", "XBOXONE", "PS3", "PS4", "NINTENDO_SWITCH_PRO", "VIRTUAL", 
"PS5","AMAZON_LUNA", "GOOGLE_STADIA"

GameControllerAxis:
"INVALID", "LEFTX", "LEFTY", "RIGHTX", "RIGHTY", "TRIGGERLEFT", "TRIGGERRIGHT"

GameControllerButton:
"INVALID", "A", "B", "X", "Y", "BACK", "GUIDE", "START", "LEFTSTICK", "RIGHTSTICK", 
"LEFTSHOULDER", "RIGHTSHOULDER", "DPAD_UP", "DPAD_DOWN", "DPAD_LEFT", "DPAD_RIGHT", 
"MISC1", "PADDLE1", "PADDLE2", "PADDLE3", "PADDLE4", "TOUCHPAD"

count = SDL.GameController.AddMappingFromFile( fileOrRWops )
--[[
	Load a set of Game Controller mappings from a seekable SDL data stream.

	You can call this function several times, if needed, to load different
	database files.

	If a new mapping is loaded for an already known controller GUID, the later
	version will overwrite the one currently loaded.

	Mappings not belonging to the current platform or with no platform field
	specified will be ignored (i.e. mappings for Linux will be ignored in
	Windows, etc).

	This function will load the text database entirely in memory before
	processing it, so take this into consideration if you are in a memory
	constrained environment.

	\param fileOrRWops	file with mappings or a RWops object
	\returns count		the number of mappings added or nil on error
--]]

bool = SDL.GameController.AddMapping( string )
--[[
	Add support for controllers that SDL is unaware of or to cause an existing
	controller to have a different binding.

	The mapping string has the format "GUID,name,mapping", where GUID is the
	string value from SDL.Joystick.GetGUID(), name is the human readable
	string for the device and mappings are controller mappings to joystick
	ones. Under Windows there is a reserved GUID of "xinput" that covers all
	XInput devices. The mapping format for joystick is: {| |bX |a joystick
	button, index X |- |hX.Y |hat X with value Y |- |aX |axis X of the joystick
	|} Buttons can be used as a controller axes and vice versa.

	This string shows an example of a valid mapping for a controller:
		"341a3608000000000000504944564944,Afterglow PS3 Controller,a:b1,b:b2,y:b3,x:b0,start:b9,guide:b12,back:b8,dpup:h0.1,dpleft:h0.8,dpdown:h0.4,dpright:h0.2,leftshoulder:b4,rightshoulder:b5,leftstick:b10,rightstick:b11,leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:b6,righttrigger:b7"

	\param string		the mapping string
	\returns bool 		true on success or false on failure
--]]

count = SDL.GameController.GetNumMappings()
--[[
	Get the number of mappings installed.

	\returns count		the number of mappings.
--]]

string = SDL.GameController.GetMappingForIndex( index )
--[[
	Get the mapping at a particular index.

	\param index		index from zero to SDL.Controller.GetNumMappings()-1
	\returns string 	the mapping string.
--]]

string = SDL.GameController.GetMapping( GuidOrGameControllerOrJoyIndex )
--[[
	Get the game controller mapping string
	\param GuidOrGameControllerOrJoyIndex
						the GUID, the GameController or 
						index from zero to SDL.Joystick.GetNum()-1
--]]

bool = SDL.GameController.Is( joystick_index )
--[[
	Check if the given joystick is supported by the game controller interface.

	`joystick_index` is the same as the `device_index` passed to
	SDL.Joystick.Open().

	\param joystick_index	the device_index of a device, up to SDL.Joysticks.GetNum()
	\returns bool			true if the given joystick is supported or false
--]]

GameController = SDL.GameController.Open( joystick_index )
--[[
	Open a game controller for use.
	
	The index passed as an argument refers to the N'th game controller on the
	system. This index is not the value which will identify this controller in
	future controller events. The joystick's instance id will be used there instead.

	\param joystick_index	the device_index of a device, up to SDL.Joysticks.GetNum()
	\returns GameController	a gamecontroller object or nil
--]]

GameController = SDL.GameController.FromPlayerIndex( index )
--[[
	Get the SDL_GameController associated with a player index.
	
	Please note that the player index is _not_ the device index, nor is it the instance id!
	
	\param player_index 	the player index
	\returns GAMECONTROLLER	the GameController associated with a player index.
--]]

Name = SDL.GameController.GetName( GameController )
--[[
	Get the implementation-dependent name for an opened game controller.

	\param gamecontroller 	a game controller object
	\returns name			the implementation dependent name for the game controller
--]]

type = SDL.GameController.GetType( GameControllerOrJoyIndex )
--[[
	Get the type of this currently opened controller

	\param GameControllerOrJoyIndex 
							the game controller object or 
							the device_index of a device, up to SDL.Joysticks.GetNum()
	\returns type			the controller type
--]]

index = SDL.GameController.GetPlayerIndex( GameController )
--[[
	Get the player index of an opened game controller.

	For XInput controllers this returns the XInput user index.

	\param gamecontroller 	the game controller object
	\returns index 			the player index for controller
--]]

SDL.GameController.SetPlayerIndex( GameController, player_index )
--[[
	Set the player index of an opened game controller.

	\param gamecontroller 	the game controller object to adjust.
	\param player_index 	Player index to assign to this controller or -1 to
							clear the player index and turn off player LEDs.
--]]

vendor = SDL.GameController.GetVendor( GameController )
--[[
	Get the USB vendor ID of an opened controller, if available.

	If the vendor ID isn't available this function returns 0.

	\param gamecontroller 	the game controller object to query.
	\return vendor			the USB vendor ID, or zero if unavailable.
--]]

product = SDL.GameController.GetProduct( GameController )
--[[
	Get the USB product ID of an opened controller, if available.

	If the product ID isn't available this function returns 0.

	\param gamecontroller 	the game controller object to query.
	\return product			the USB product ID, or zero if unavailable.
--]]

productversion = SDL.GameController.GetProductVersion( GameController )
--[[
	Get the USB product version ID of an opened controller, if available.

	If the product version ID isn't available this function returns 0.

	\param gamecontroller 	the game controller object to query.
	\return productversion	the USB product version ID, or zero if unavailable.
--]]

serial = SDL.GameController.GetSerial( GameController )
--[[
	Get the serial number of an opened controller, if available.

	Returns the serial number of the controller, or NULL if it is not
	available.

	\param gamecontroller 	the game controller object to query.	
	\return serial			the serial number, or nil if unavailable.
--]]

bool = SDL.GameController.GetAttached( GameController )
--[[
	Check if a controller has been opened and is currently connected.

	\param gamecontroller 	a game controller identifier previously returned by
							SDL.GameController.Open()
	\returns bool			true if the controller has been opened and is currently
							connected, or false if not.
--]]

Joystick = SDL.GameController.GetJoystick( GameController )
--[[
	Get the Joystick ID from a Game Controller.

	This function will give you a SDL_Joystick object, which allows you to use
	the SDL.Joystick functions with a GameController object. This would be
	useful for getting a joystick's position at any given time, even if it
	hasn't moved (moving it would produce an event, which would have the axis'
	value).

	The Joystick returned is owned by the GameController. You should not
	call SDL.Joystick.Close() on it, for example, since doing so will likely
	cause SDL to crash.

	\param gamecontroller	the game controller object that you want to get a
							joystick from
	\returns Joystick		a Joystick object
--]]

oldstate = SDL.GameController.EventState( state )
--[[
	Query or change current state of Game Controller events.
 
	If controller events are disabled, you must call SDL.GameController.Update()
	yourself and check the state of the controller when you want controller
	information.
	
	\param state 			can be one of "QUERY", "IGNORE", "ENABLE"
	\returns oldstate		the current state
--]]

SDL.GameController.Update()
--[[
	Manually pump game controller updates if not using the loop.

	This function is called automatically by the event loop if events are
	enabled. Under such circumstances, it will not be necessary to call this
	function.
--]]

bool = SDL.GameController.HasAxis( GameController, axis )
--[[
	Query whether a game controller has a given axis.

	This merely reports whether the controller's mapping defined this axis, as
	that is all the information SDL has about the physical device.

	\param gamecontroller 	a game controller
	\param axis 			a GameControllerAxis value
	\returns success		true if the controller has this axis, false otherwise.
--]]

state = SDL.GameController.GetAxis( GameController, axis )

--[[
	Get the current state of an axis control on a game controller.
	
	The state is a value ranging from -1.0000 to 1.0000. Triggers, however, range
    from 0.0000 to 1.0000 (they never return a negative value).

	\param gamecontroller 	a game controller
	\param axis 			a GameControllerAxis value
	\returns axis 			state -1.0000 to 1.0000
--]]

bool = SDL.GameController.HasButton( GameController, button )
--[[
	Query whether a game controller has a given button.

	This merely reports whether the controller's mapping defined this button,
	as that is all the information SDL has about the physical device.

	\param gamecontroller 	a game controller
	\param button 			a GameControllerButton value
	\returns bool			true if the controller has this button, false otherwise.
--]]

state = SDL.GameController.GetButton( GameController, button )
--[[
	Get the current state of a button on a game controller.

	\param gamecontroller 	a game controller
	\param button 			a GameControllerButton value
	\returns state			true for pressed state or false for not pressed state	
--]]

count = SDL.GameController.GetNumTouchpads( GameController )
--[[
	Get the number of touchpads on a game controller.
	
	\param gamecontroller 	a game controller
	\returns count			number of touchpads
--]]

count = SDL.GameController.GetNumTouchpadFingers( GameController, index)
--[[
	Get the number of supported simultaneous fingers on a touchpad on a game
	controller.
	
	\param gamecontroller 	a game controller
	\param index			which touchpad
	\returns count			number of fingers
--]]

state,x,y,pressure = SDL.GameController.GetTouchpadFinger( GameController, index, finger )
--[[
	Get the current state of a finger on a touchpad on a game controller.
	\param gamecontroller 	a game controller
	\param index			which touchpad
	\param finger			which finger
	\returns state			true for pressed or false
	\returns x 				x-coordinate 0.000 to 1.000
	\returns y				y-coordinate 0.000 to 1.000
	\returns pressure		pressure 0.000 to 1.000
--]]

bool = SDL.GameController.HasSensor( GameController, type )
--[[
	Return whether a game controller has a particular sensor.

	\param gamecontroller 	The controller to query
	\param type 			The type of sensor to query
	\returns bool			true if the sensor exists, false otherwise
--]]

success = SDL.GameController.SetSensorEnable( GameController, type, bool )
--[[
	Set whether data reporting for a game controller sensor is enabled.

	\param gamecontroller 	The controller to update
	\param type 			The type of sensor to enable/disable
	\param bool 			Whether data reporting should be enabled
	\returns bool			true if the sensor exists, false otherwise
--]]

bool = SDL.GameController.IsSensorEnabled( GameController, type )
--[[
	Query whether sensor data reporting is enabled for a game controller.

	\param gamecontroller 	The controller to query
	\param type 			The type of sensor to query
	\returns bool			true if the sensor is enabled, false otherwise.
--]]

rate = SDL.GameController.GetSensorDataRate( GameController, type )
--[[
	Get the data rate (number of events per second) of a game controller sensor.

	\param gamecontroller 	The controller to query
	\param type 			The type of sensor to query
	\return rate			the data rate, or 0.0 if it is not available.
--]]

x, y, z = SDL.GameController.GetSensorData( GameController, type )
--[[
	Get the current state of a game controller sensor.

	The number of values and interpretation of the data is sensor dependent.
	See sensor for the details for each type of sensor.

	\param gamecontroller 	The controller to query
	\param type 			The type of sensor to query
	\returns x				Sensor data
	\returns y				Sensor data
	\returns z				Sensor data
--]]

success = SDL.GameController.Rumble( GameController, low, high, ms )
--[[
	Start a rumble effect on a game controller.

	Each call to this function cancels any previous rumble effect, and calling
	it with 0 intensity stops any rumbling.

	\param gamecontroller 	The controller to vibrate
	\param low				The intensity of low frequency (left) rumble motor,
							from 0.0000 to 1.0000
	\param high				The intensity of high frequency (right) rumble motor, 
							from 0.0000 to 1.0000
	\param ms 				The duration of the rumble effect, in milliseconds
	\returns success		true on success or false on failure
--]]

success = SDL.GameController.RumbleTriggers( GameController, left, right, ms )
--[[
	Start a rumble effect in the game controller's triggers.

	Each call to this function cancels any previous trigger rumble effect, and
	calling it with 0 intensity stops any rumbling.

	Note that this is rumbling of the _triggers_ and not the game controller as
	a whole. The first controller to offer this feature was the PlayStation 5's
	DualShock 5.

	\param gamecontroller 	The controller to vibrate
	\param low				The intensity of left rumble trigger motor,
							from 0.0000 to 1.0000
	\param high				The intensity of right rumble  trigger motor, 
							from 0.0000 to 1.0000
	\param ms 				The duration of the rumble effect, in milliseconds
	\returns success		true on success or false on failure
--]]

bool = SDL.GameController.HasLED( GameController )
--[[
	Query whether a game controller has an LED.

	\param gamecontroller 	The controller to query
	\returns bool			true, or false if this controller does not have a LED
--]]

bool = SDL.GameController.HasRumble( GameController )
--[[
	Query whether a game controller has rumble support.

	\param gamecontroller 	The controller to query
	\returns bool			true, or false if it does not have rumble support
--]]

bool = SDL.GameController.HasRumbleTriggers( GameController )
--[[
	Query whether a game controller has rumble support on triggers.

	\param gamecontroller 	The controller to query
	\returns bool			true, or false if it doesn't have trigger rumble support
--]]

success = SDL.GameController.SetLED( GameController, r, g, b )
--[[
	Update a game controller's LED color.

	\param gamecontroller 	The controller to update
	\param r				The intensity of the red LED
	\param g				The intensity of the green LED
	\param b				The intensity of the blue LED
	\returns success		true or false 
--]]

SDL.GameController.Close( GameController )
--[[
	Close a game controller previously opened with SDL_GameControllerOpen().

	\param gamecontroller 	a game controller identifier previously returned by
							SDL.GameController.Open()
--]]


-----------------------------------------------------------------------------Gesture
--[[
Dollar Gestures
===========================================================================
SDL provides an implementation of the $1 gesture recognition system. This allows for 
recording, saving, loading, and performing single stroke gestures.

Gestures can be performed with any number of fingers (the centroid of the fingers 
must follow the path of the gesture), but the number of fingers must be constant (a 
finger cannot go down in the middle of a gesture). The path of a gesture is 
considered the path from the time when the final finger went down, to the first time 
any finger comes up. 

Dollar gestures are assigned an Id based on a hash function. This is guaranteed to 
remain constant for a given gesture. There is a (small) chance that two different 
gestures will be assigned the same ID. In this case, simply re-recording one of the 
gestures should result in a different ID.

Recording:
----------
To begin recording on a touch device call:
SDL.Gesture.Record(touchId), where touchId is the id of the touch device you wish to 
record on, or -1 to record on all connected devices.

Recording terminates as soon as a finger comes up. Recording is acknowledged by an 
"DOLLARRECORD" event.
A "DOLLARRECORD" event is a dgesture with the following fields:

* event.touchId   - the Id of the touch used to record the gesture.
* event.gestureId - the unique id of the recorded gesture.

Performing:
-----------
As long as there is a dollar gesture assigned to a touch, every finger-up event will 
also cause an "DOLLARGESTURE" event with the following fields:

* event.touchId    - the Id of the touch which performed the gesture.
* event.gestureId  - the unique id of the closest gesture to the performed stroke.
* event.error      - the difference between the gesture template and the actual performed gesture. Lower error is a better match.
* event.numFingers - the number of fingers used to draw the stroke.

Most programs will want to define an appropriate error threshold and check to be 
sure that the error of a gesture is not abnormally high (an indicator that no 
gesture was performed).

Saving:
-------
To save a template, call SDL.Gesture.SaveTemplate( gestureId, file) where gestureId 
is the id of the gesture you want to save, and file where the gesture will be stored.

To save all currently loaded templates, call SDL.Gesture.SaveAllTemplates(file) 
where file where the gesture will be stored.

Both functions return the number of gestures successfully saved.

Loading:
--------
To load templates from a file, call SDL.Gesture.LoadTemplates(touchId,file) where 
touchId is the id of the touch to load to (or -1 to load to all touch devices), and 
file is a save file. 

SDL.Gesture.LoadTemplates() returns the number of templates successfully loaded.

===========================================================================
Multi Gestures
===========================================================================
SDL provides simple support for pinch/rotate/swipe gestures. 
Every time a finger is moved an "MULTIGESTURE" event is sent with the following 
fields:

* event.touchId - the Id of the touch on which the gesture was performed.
* event.x       - the normalized x coordinate of the gesture. (0..1)
* event.y       - the normalized y coordinate of the gesture. (0..1)
* event.dTheta  - the amount that the fingers rotated during this motion.
* event.dDist   - the amount that the fingers pinched during this motion.
* event.numFingers - the number of fingers used in the gesture.
--]]

-------------------------------------------------------------------------------Hints
-- Note too many hints - please see the original SDL-documentation

success = SDL.Hint.Set( name, value [,priority] )
--[[
	Set a hint with a specific / normal priority.
	
	The priority controls the behavior when setting a hint that already has a
	value. Hints will replace existing hints of their priority and lower.
	Environment variables are considered to have override priority.
	
	\param name 		the hint to set
	\param value 		the value of the hint variable
	\param priority 	"DEFAULT", "NORMAL, "OVERRIDE" level for the hint (optional)
	\returns success	true if the hint was set, false otherwise.	
--]]

value = SDL.Hint.Get( name )
--[[
	Get the value of a hint.

	\param name 	the hint to query
	\returns value	the string value of a hint or nil if the hint isn't set.
--]]

SDL.Hint.Clear()
--[[
	Clear all hints.
	
	This function is automatically called during SDL.Quit().
--]]

success		= SDL.Hint.Reset( name )
--[[
	Reset a hint to the default value.

	This will reset a hint to the value of the environment variable, or nil if
	the environment isn't set.

	\param name 		the hint to set
	\returns 			true if the hint was set, false otherwise.
--]]


----------------------------------------------------------------------------Joystick
JoystickType:
"UNKNOWN", "GAMECONTROLLER", "WHEEL", "ARCADE_STICK", "FLIGHT_STICK", "DANCE_PAD", 
"GUITAR",  "DRUM_KIT",  "ARCADE_PAD",  "THROTTLE"

JoystickPower:
"UNKNOWN", "EMPTY", "LOW", "MEDIUM", "FULL", "WIRED", "MAX"

JoystickHat:
"CENTERED", "UP", "RIGHT", "DOWN", "LEFT"

count = SDL.Joystick.GetNum()
--[[
	Count the number of joysticks attached to the system.

	\returns count		the number of attached joysticks on success or nil 
						on failure
--]]

name = SDL.Joystick.GetName( indexOrJoy )
--[[
	Get the implementation dependent name of a joystick.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns name 		the name of the selected joystick. If no name can be found, 
						this function returns ""
--]]

player = SDL.Joystick.GetPlayerIndex( indexOrJoy )
--[[
	Get the player index of a joystick, or -1 if it's not available
	
	For XInput controllers this returns the XInput user index. Many joysticks
	will not be able to supply this information.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns player		player index or -1
--]]

guid = SDL.Joystick.GetGuid( indexOrJoy )
--[[
	Get the implementation-dependent GUID for the joystick.

	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns guid		the GUID of the selected joystick.
--]]

vendor = SDL.Joystick.GetVendor( indexOrJoy )
--[[
	Get the USB vendor ID of a joystick, if available.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns vendor		the USB vendor ID of the selected joystick or zero
--]]

product = SDL.Joystick.GetProduct( indexOrJoy )
--[[
	Get the USB product ID of a joystick, if available.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns product	the USB product ID of the selected joystick or zero
--]]

version = SDL.Joystick.GetProductVersion( indexOrJoy )
--[[
	Get the product version of a joystick, if available.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns version	the product version of the selected joystick or zero
--]]

type = SDL.Joystick.GetType( indexOrJoy )
--[[
	Get the type of a joystick, if available.
	
	\param indexOrJoy	Joystick object obtained from SDL.Joystick.Open()
						or  the index of the joystick to query (the N'th joystick
						on the system)
	\returns type		the JoystickType of the selected joystick.
--]]

joystick = SDL.Joystick.Open( index )
--[[
	Open a joystick for use.

	\param indexOrJoy	the index of the joystick to query (the N'th joystick on the system)
	\returns joystick	a joystick object or nil if an error occurred
--]]

joystick = SDL.Joystick.FromPlayerIndex( player_index )
--[[
	Get the Joystick associated with a player index.

	\param player_index 	the player index to get the SDL_Joystick for
	\returns joystick		a Joystick on success or nil on failure
--]]

index = SDL.Joystick.AttachVirtual( type, naxes, nbuttons, nhats )
--[[
	Attach a new virtual joystick.

	\param type			a JoystickType values
	\param naxes		count of axes
	\param nbuttons		count of buttons
	\param nhats		count of hats.
	\returns index		the joystick's device index, or nil if an error occurred.
--]]

success = SDL.Joystick.DetachVirtual( index )
--[[
	Detach a virtual joystick.

	\param index		device_index a value previously returned from
						SDL.Joystick.AttachVirtual()
	\returns success	true on success, or false if an error occurred.
--]]

bool = SDL.Joystick.IsVirtual( index )
--[[
	Query whether or not the joystick at a given device index is virtual.

	\param index		device_index a value previously returned from
						SDL.Joystick.AttachVirtual()
	\returns bool		true if the joystick is virtual, false otherwise.
--]]

success = SDL.Joystick.SetVirtualAxis( joystick, axis, value )
--[[
	Set values on an opened, virtual-joystick's axis.

	Please note that values set here will not be applied until the next call to
	SDL.Joystick.Update, which can either be called directly, or can be called
	indirectly through various other SDL APIs, including, but not limited to
	the following: SDL.Event.Poll, SDL.Event.Pump, SDL.Event.Wait.

	\param joystick 	the virtual joystick on which to set state.
	\param axis 		the specific axis on the virtual joystick to set.
	\param value 		the new value for the specified axis.
	\returns success 	true on success, false on error.
--]]

success = SDL.Joystick.SetVirtualButton( joystick, button, value )
--[[
	Set values on an opened, virtual-joystick's button.
	
	Please note that values set here will not be applied until the next call to
	SDL.Joystick.Update, which can either be called directly, or can be called
	indirectly through various other SDL APIs, including, but not limited to
	the following: SDL.Event.Poll, SDL.Event.Pump, SDL.Event.Wait.

	\param joystick 	the virtual joystick on which to set state.
	\param button 		the specific button on the virtual joystick to set.
	\param value 		the new value for the specified button.
	\returns success 	true on success, false on error.
--]]

success = SDL.Joystick.SetVirtualHat( joystick, hat, value )
--[[
	Set values on an opened, virtual-joystick's hat.
	
	Please note that values set here will not be applied until the next call to
	SDL.Joystick.Update, which can either be called directly, or can be called
	indirectly through various other SDL APIs, including, but not limited to
	the following: SDL.Event.Poll, SDL.Event.Pump, SDL.Event.Wait.

	\param joystick 	the virtual joystick on which to set state.
	\param hat	 		the specific hat on the virtual joystick to set.
	\param value 		the new value for the specified hat.
	\returns success 	true on success, false on error.
--]]

SDL.Joystick.SetPlayerIndex( joystick, index )
--[[
	Set the player index of an opened joystick.

	\param joystick 	the SDL_Joystick obtained from SDL.Joystick.Open()
	\param index 		the player index to set.
--]]

serial = SDL.Joystick.GetSerial( joystick )
--[[
	Get the serial number of an opened joystick, if available.

	Returns the serial string of the joystick, or "" if it is not available.

	\param joystick 	the Joystick obtained from SDL.Joystick.Open()
	\returns serial		the serial string of the selected joystick, or ""
--]]

bool = SDL.Joystick.GetAttached( joystick )
--[[
	Get the status of a specified joystick.

	\param joystick 	the joystick to query
	\returns bool		true if the joystick has been opened, false if it has not
--]]

num = SDL.Joystick.GetNumAxes( joystick )
--[[ 
	Get the number of general axis controls on a joystick.

	Often, the directional pad on a game controller will either look like 4
	separate buttons or a POV hat, and not axes, but all of this is up to the
	device and platform.

 	\param joystick 	the Joystick obtained from SDL.Joystick.Open()
	\returns num		number of axes on success or nil
--]]

num = SDL.Joystick.GetNumBalls( joystick )
--[[
	Get the number of trackballs on a joystick.
 
	Joystick trackballs have only relative motion events associated with them
	and their state cannot be polled.

	Most joysticks do not have trackballs.
 
  	\param joystick 	the Joystick obtained from SDL.Joystick.Open()
	\returns num		number of balls on success or nil
--]]

num = SDL.Joystick.GetNumHats( joystick )
--[[
	Get the number of POV hats on a joystick.

  	\param joystick 	the Joystick obtained from SDL.Joystick.Open()
	\returns num		number of hats on success or nil
--]]

num = SDL.Joystick.GetNumButtons( joystick )
--[[
	Get the number of buttons on a joystick.

  	\param joystick 	the Joystick obtained from SDL.Joystick.Open()
	\returns num		number of buttons on success or nil
--]]

SDL.Joystick.Update()
--[[
	Update the current state of the open joysticks.

	This is called automatically by the event loop if any joystick events are
	enabled.
--]]

oldstate = SDL.Joystick.EventState( state )
--[[
	Enable/disable joystick event polling.
 
	If joystick events are disabled, you must call SDL.Joystick.Update()
	yourself and manually check the state of the joystick when you want
	joystick information.

	It is recommended that you leave joystick event handling enabled.

	**WARNING**: Calling this function may delete all events currently in SDL's
	event queue.

	\param state 		can be one of "QUERY", "IGNORE", or "ENABLE"
	\returns oldstate   "DISABLE", "ENABLE" or nil on error
--]]

value = SDL.Joystick.GetAxis( joystick, axis )
--[[
	Get the current state of an axis control on a joystick.

	SDL makes no promises about what part of the joystick any given axis refers
	to. Your game should have some sort of configuration UI to let users
	specify what each axis should be bound to. Alternately, SDL's higher-level
	Game Controller API makes a great effort to apply order to this lower-level
	interface, so you know that a specific axis is the "left thumb stick," etc.

	The value returned by SDL.Joystick.GetAxis() is a number between -1.00000 and 
	1.00000 representing the current position of the axis. It may be necessary
	to impose certain tolerances on these values to account for jitter.
 
	\param joystick 	a Joystick object containing joystick information
	\param axis 		the axis to query; the axis indices start at index 0
	\returns valkue 	a number between -1.00000 and 1.00000
--]]

value = SDL.Joystick.GetAxisInitalState( joystick, axis )
--[[
	Get the initial state of an axis control on a joystick.
	
	\param joystick 	a Joystick object containing joystick information
	\param axis 		the axis to query; the axis indices start at index 0
	\returns valkue 	a number between -1.00000 and 1.00000 or nil
--]]

value = SDL.Joystick.GetHat( joystick, hat )
--[[
	Get the current state of a POV hat on a joystick.

	The returned value will be a combination of the following positions:
	"CENTERED", "UP", "RIGHT", "DOWN", "LEFT"
		
	\param joystick 	a Joystick object containing joystick information
	\param hat 			the hat to query; the hat indices start at index 0
	\returns value		the current hat position.
--]]

dx, dy = SDL.Joystick.GetBall( joystick, ball )
--[[
	Get the ball axis change since the last poll.

	Trackballs can only return relative motion since the last call to
	SDL.Joystick.GetBall().

	Most joysticks do not have trackballs.

	\param joystick 	a Joystick object containing joystick information
	\param ball 		the ball to query; the ball indices start at index 0
	\returns dx			the difference in the x axis position since the last poll
	\returns dy 		the difference in the y axis position since the last poll
--]]

state = SDL.Joystick.GetButton( joystick, button )
--[[
	Get the current state of a button on a joystick.
	
	\param joystick 	a Joystick object containing joystick information
	\param button 		the button to query; the button indices start at index 0
	\returns state		true or false
--]]

success = SDL.Joystick.Rumble( joystick, low, high, ms )
--[[
	 Start a rumble effect.

	Each call to this function cancels any previous rumble effect, and calling
	it with 0.0 intensity stops any rumbling.
 
	\param joystick 	The joystick to vibrate
	\param low			The intensity of the low frequency (left) rumble motor, 
						from 0.00000 to 1.00000
	\param high			The intensity of the high frequency (right) rumble motor,
						from 0.00000 to 1.00000
	\param ms 			The duration of the rumble effect, in milliseconds
	\returns success	true, or false if rumble isn't supported on this joystick
--]]
	
success = SDL.Joystick.RumbleTriggers( joystick, left, right, ms )
--[[
	Start a rumble effect in the joystick's triggers

	Each call to this function cancels any previous trigger rumble effect, and
	calling it with 0.0 intensity stops any rumbling.

	Note that this function is for _trigger_ rumble; the first joystick to
	support this was the PlayStation 5's DualShock 5 controller. If you want
	the (more common) whole-controller rumble, use SDL.Joystick.Rumble()
	instead.

	\param joystick 	The joystick to vibrate
	\param left			The intensity of the left trigger rumble motor, 
						from 0.00000 to 1.00000
	\param right		The intensity of the right trigger rumble motor,
						from 0.00000 to 1.00000
	\param ms 			The duration of the rumble effect, in milliseconds
	\returns			true, or false if trigger rumble isn't supported on 
						this joystick
--]]

bool = SDL.Joystick.HasLED( joystick )
--[[
	Query whether a joystick has an LED.

	An example of a joystick LED is the light on the back of a PlayStation 4's
	DualShock 4 controller.

	\param joystick 	The joystick to query
	\returns bool		true if the joystick has a modifiable LED, false otherwise.
--]]

bool = SDL.Joystick.HasRumble( joystick )
--[[
	Query whether a joystick has rumble support.

	\param joystick 	The joystick to query
	\returns bool		true if the joystick has rumble, false otherwise.
--]]

bool = SDL.Joystick.HasRumbleTriggers( joystick )
--[[
	Query whether a joystick has rumble support on triggers.

	\param joystick 	The joystick to query
	\returns bool		true if the joystick has trigger rumble, false otherwise.
--]]

success = SDL.Joystick.SetLED( joystick, r, g, b )
--[[
	Update a joystick's LED color.

	An example of a joystick LED is the light on the back of a PlayStation 4's
	DualShock 4 controller.

	\param joystick 	The joystick to update
	\param r 			The intensity of the red LED
	\param g			The intensity of the green LED
	\param b			The intensity of the blue LED
	\returns success	true on success, false if this joystick does not have a 
						modifiable LED
--]]

success = SDL.Joystick.Close( joystick )
--[[
	Close a joystick previously opened with SDL_JoystickOpen().

	\param joystick 	The joystick device to close
--]]

----------------------------------------------------------------------------Keyboard
Keycode:
"UNKNOWN", "RETURN", "ESCAPE", "BACKSPACE", "TAB", "SPACE", "EXCLAIM", "QUOTEDBL", 
"HASH", "PERCENT", "DOLLAR", "AMPERSAND", "QUOTE", "LEFTPAREN", "ASTERISK", "PLUS", 
"COMMA", "MINUS", "PERIOD", "SLASH", "0", "1", "2", "3", "4", "5", "6", "7", "8", 
"9", "COLON", "SEMICOLON", "LESS", "EQUALS", "GREATER", "QUESTION", "AT", 
"LEFTBRACKET", "BACKSLASH", "RIGHTBRACKET", "CARET", "UNDERSCORE", "BACKQUOTE", "a", 
"b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", 
"s", "t", "u", "v", "w", "x", "y", "z", "CAPSLOCK", "F1", "F2", "F3", "F4", "F5", 
"F6", "F7", "F8", "F9", "F10", "F11", "F12", "PRINTSCREEN", "SCROLLLOCK", "PAUSE", 
"INSERT", "HOME", "PAGEUP", "DELETE", "END", "PAGEDOWN", "RIGHT", "LEFT", "DOWN", 
"UP", "NUMLOCKCLEAR", "KP_DIVIDE", "KP_MULTIPLY", "KP_MINUS", "KP_PLUS", "KP_ENTER", 
"KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7", "KP_8", "KP_9", "KP_0", 
"KP_PERIOD", "APPLICATION", "POWER", "KP_EQUALS", "F13", "F14", "F15", "F16", "F17", 
"F18", "F19", "F20", "F21", "F22", "F23", "F24", "EXECUTE", "HELP", "MENU", "SELECT",
"STOP", "AGAIN", "UNDO", "CUT", "COPY", "PASTE", "FIND", "MUTE", "VOLUMEUP", 
"VOLUMEDOWN", "KP_COMMA", "KP_EQUALSAS400", "ALTERASE", "SYSREQ", "CANCEL", "CLEAR", 
"PRIOR", "RETURN2", "SEPARATOR", "OUT", "OPER", "CLEARAGAIN", "CRSEL", "EXSEL", 
"KP_00", "KP_000", "THOUSANDSSEPARATOR", "DECIMALSEPARATOR", "CURRENCYUNIT", 
"CURRENCYSUBUNIT", "KP_LEFTPAREN", "KP_RIGHTPAREN", "KP_LEFTBRACE", "KP_RIGHTBRACE", 
"KP_TAB", "KP_BACKSPACE", "KP_A", "KP_B", "KP_C", "KP_D", "KP_E", "KP_F", "KP_XOR", 
"KP_POWER", "KP_PERCENT", "KP_LESS", "KP_GREATER", "KP_AMPERSAND", "KP_DBLAMPERSAND",
"KP_VERTICALBAR", "KP_DBLVERTICALBAR", "KP_COLON", "KP_HASH", "KP_SPACE", "KP_AT", 
"KP_EXCLAM", "KP_MEMSTORE", "KP_MEMRECALL", "KP_MEMCLEAR", "KP_MEMADD", 
"KP_MEMSUBTRACT", "KP_MEMMULTIPLY", "KP_MEMDIVIDE", "KP_PLUSMINUS", "KP_CLEAR", 
"KP_CLEARENTRY", "KP_BINARY", "KP_OCTAL", "KP_DECIMAL", "KP_HEXADECIMAL", "LCTRL", 
"LSHIFT", "LALT", "LGUI", "RCTRL", "RSHIFT", "RALT", "RGUI", "MODE", "AUDIONEXT", 
"AUDIOPREV", "AUDIOSTOP", "AUDIOPLAY", "AUDIOMUTE", "MEDIASELECT", "WWW", "MAIL", 
"CALCULATOR", "COMPUTER", "AC_SEARCH", "AC_HOME", "AC_BACK", "AC_FORWARD", "AC_STOP",
"AC_REFRESH", "AC_BOOKMARKS", "BRIGHTNESSDOWN", "BRIGHTNESSUP", "DISPLAYSWITCH", 
"KBDILLUMTOGGLE", "KBDILLUMDOWN", "KBDILLUMUP", "EJECT", "SLEEP", "APP1", "APP2", 
"AUDIOREWIND", "AUDIOFASTFORWARD"

Keymod:
"NONE", "LSHIFT", "RSHIFT", "LCTRL", "RCTRL", "LALT", "RALT", "LGUI", "RGUI", "NUM", "CAPS", "MODE", "SCROLL", "CTRL", "SHIFT", "ALT", "GUI", "RESERVED"

Scancode:
"UNKNOWN", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
"P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", 
"7", "8", "9", "0", "RETURN", "ESCAPE", "BACKSPACE", "TAB", "SPACE", "MINUS", 
"EQUALS", "LEFTBRACKET", "RIGHTBRACKET", "BACKSLASH", "NONUSHASH", "SEMICOLON", 
"APOSTROPHE", "GRAVE", "COMMA", "PERIOD", "SLASH", "CAPSLOCK", "F1", "F2", "F3", 
"F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PRINTSCREEN", "SCROLLLOCK",
"PAUSE", "INSERT", "HOME", "PAGEUP", "DELETE", "END", "PAGEDOWN", "RIGHT", "LEFT", 
"DOWN", "UP", "NUMLOCKCLEAR", "KP_DIVIDE", "KP_MULTIPLY", "KP_MINUS", "KP_PLUS", 
"KP_ENTER", "KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7", "KP_8", "KP_9", 
"KP_0", "KP_PERIOD", "NONUSBACKSLASH", "APPLICATION", "POWER", "KP_EQUALS", "F13", 
"F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", 
"EXECUTE", "HELP", "MENU", "SELECT", "STOP", "AGAIN", "UNDO", "CUT", "COPY", "PASTE",
"FIND", "MUTE", "VOLUMEUP", "VOLUMEDOWN", "KP_COMMA", "KP_EQUALSAS400", 
"INTERNATIONAL1", "INTERNATIONAL2", "INTERNATIONAL3", "INTERNATIONAL4", 
"INTERNATIONAL5", "INTERNATIONAL6", "INTERNATIONAL7", "INTERNATIONAL8", 
"INTERNATIONAL9", "LANG1", "LANG2", "LANG3", "LANG4", "LANG5", "LANG6", "LANG7", 
"LANG8", "LANG9", "ALTERASE", "SYSREQ", "CANCEL", "CLEAR", "PRIOR", "RETURN2", 
"SEPARATOR", "OUT", "OPER", "CLEARAGAIN", "CRSEL", "EXSEL", "KP_00", "KP_000", 
"THOUSANDSSEPARATOR", "DECIMALSEPARATOR", "CURRENCYUNIT", "CURRENCYSUBUNIT", 
"KP_LEFTPAREN", "KP_RIGHTPAREN", "KP_LEFTBRACE", "KP_RIGHTBRACE", "KP_TAB", 
"KP_BACKSPACE", "KP_A", "KP_B", "KP_C", "KP_D", "KP_E", "KP_F", "KP_XOR", "KP_POWER",
"KP_PERCENT", "KP_LESS", "KP_GREATER", "KP_AMPERSAND", "KP_DBLAMPERSAND", 
"KP_VERTICALBAR", "KP_DBLVERTICALBAR", "KP_COLON", "KP_HASH", "KP_SPACE", "KP_AT", 
"KP_EXCLAM", "KP_MEMSTORE", "KP_MEMRECALL", "KP_MEMCLEAR", "KP_MEMADD", 
"KP_MEMSUBTRACT", "KP_MEMMULTIPLY", "KP_MEMDIVIDE", "KP_PLUSMINUS", "KP_CLEAR", 
"KP_CLEARENTRY", "KP_BINARY", "KP_OCTAL", "KP_DECIMAL", "KP_HEXADECIMAL", "LCTRL", 
"LSHIFT", "LALT", "LGUI", "RCTRL", "RSHIFT", "RALT", "RGUI", "MODE", "AUDIONEXT", 
"AUDIOPREV", "AUDIOSTOP", "AUDIOPLAY", "AUDIOMUTE", "MEDIASELECT", "WWW", "MAIL", 
"CALCULATOR", "COMPUTER", "AC_SEARCH", "AC_HOME", "AC_BACK", "AC_FORWARD", "AC_STOP",
"AC_REFRESH", "AC_BOOKMARKS", "BRIGHTNESSDOWN", "BRIGHTNESSUP", "DISPLAYSWITCH", 
"KBDILLUMTOGGLE", "KBDILLUMDOWN", "KBDILLUMUP", "EJECT", "SLEEP", "APP1", "APP2", 
"AUDIOREWIND", "AUDIOFASTFORWARD", "NUM_SCANCODES"

value = SDL.Keyboard.GetScancodeValue( scancode )
--[[
	Get the integer value of a scancode
	
	Every SDL.Keyboard function will return a scancode string (if possible).
	When you need the integer value, you can convert it with this function.
	
	\param scancode		a scancode string or integer
--]]

value = SDL.Keyboard.GetKeyValue( keycode )
--[[
	Get the integer value of a keycode
	
	Every SDL.Keyboard function will return a keycode string (if possible).
	When you need the integer value, you can convert it with this function.
	
	\param keycode		a keycode string or integer
--]]

window = SDL.Keyboard.GetFocus()
--[[
	Query the window which currently has keyboard focus.

	\returns the 		window with keyboard focus.
--]]

state = SDL.Keyboard.GetState( scancode )
--[[
	Get the current state of a key
	
	Use SDL.Events.Pump() to update the state.
	
	This function gives you the current state after all events have been
	processed, so if a key or button has been pressed and released before you
	process events, then the pressed state will never show up in the
	SDL.Keyboard.GetState() calls.
	
	Note: This function doesn't take into account whether shift has been pressed or 
	not.
	
	\param scancode		a scancode string or integer
	\returns state		true or false
--]]

modstate = SDL.Keyboard.GetModState()
--[[
	Get the current key modifier state for the keyboard.

	\returns modstate	a combination of the keymod values
--]]

SDL.Keyboard.Reset()
--[[
	Clear the state of the keyboard

	This function will generate key up events for all pressed keys.
--]]

SDL.Keyboard.SetModState(modstate)
--[[
	Set the current key modifier state for the keyboard.

	The inverse of SDL.Keyboard.GetModState(), SDL.Keyboard.SetModState() allows you 
	to impose modifier key states on your application. Simply pass your desired 
	modifier states into `modstate`. This value may be a combination of Keymod 
	values.

	This does not change the keyboard state, only the key modifier flags that
	SDL reports.

	\param modstate 	the desired Keymod for the keyboard
--]]

key = SDL.Keyboard.GetKeyFromScancode( scancode )
--[[
	Get the key code corresponding to the given scancode according to the
	current keyboard layout.

	\param scancode 	the desired Scancode to query
	\returns key		the Keycode that corresponds to the given Scancode.
--]]

scancode = SDL.Keyboard.GetScancodeFromKey( key )
--[[
	Get the scancode corresponding to the given key code according to the
	current keyboard layout.
	
	\param key 			the desired Keycode to query
	\returns scancode	the Scancode that corresponds to the given Keycode.
--]]

name = SDL.Keyboard.GetScancodeName( scancode )
--[[
	Get a human-readable name for a scancode.

	**Warning**: The returned name is by design not stable across platforms,
	e.g. the name for "LGUI" is "Left GUI" under Linux but "Left Windows" under 
	Microsoft Windows, and some scancodes like "NONUSBACKSLASH" don't have any name 
	at all. There are even scancodes that share names, e.g. "RETURN" and "RETURN2" 
	(both called "Return"). This function is therefore unsuitable for creating a 
	stable cross-platform two-way mapping between strings and scancodes.

	\param scancode 	the desired Scancode to query
	\returns name		the name for the scancode. If the scancode doesn't have a
						name this function returns an empty string ("").
--]]

scancode = SDL.Keyboard.GetScancodeFromName( name )
--[[
	Get a scancode from a human-readable name.

	\param name 		the human-readable scancode name
	\returns scancode	the Scancode, or "UNKNOWN" if the name wasn't recognized 
--]]

name = SDL.Keyboard.GetKeyName( key )
--[[
	Get a human-readable name for a key.
	
	\param key 			the desired Keycode to query
	\returns name 		a UTF-8 string. If the key doesn't have a name, this 
						function returns an empty string ("").
--]]

key = SDL.Keyboard.GetKeyFromName( name )
--[[
	 Get a key code from a human-readable name.

	\param name 		the human-readable key name
	\returns key 		key code, or "UNKNOWN" if the name wasn't recognized
--]]

SDL.TextInput.Start()
--[[
	Start accepting Unicode text input events.

	This function will start accepting Unicode text input events in the focused
	window, and start emitting "TEXTINPUT" and "TEXTEDITING" events. Please use 
	this function in pair with SDL.TextInput.Stop().

	On some platforms using this function activates the screen keyboard.
--]]

bool = SDL.TextInput.IsActive()
--[[
	Check whether or not Unicode text input events are enabled.
 
	\returns bool		true if text input events are enabled else false.
--]]

SDL.TextInput.Stop()
--[[
	Stop receiving any text input events.
--]]

SDL.TextInput.SetRect( rect )
--[[
	Set the rectangle used to type Unicode text inputs.

	\param rect 		the Rect object representing the rectangle to receive
						text (ignored if nill)
--]]

bool = SDL.Keyboard.HasScreenKeyboardSupport()
--[[
	Check whether the platform has screen keyboard support.

	\returns bool		true if the platform has some screen keyboard support or
						false if not.
--]]

bool = SDL.Keyboard.IsScreenKeyboardShown( window )
--[[
	Check whether the screen keyboard is shown for given window.

	\param window 		the window for which screen keyboard should be queried
	\returns bool		true if screen keyboard is shown or false if not.
--]]

------------------------------------------------------------------------------Locale
Locale = {
	language,		-- A language name, like "en" for English.
	country			-- A country, like "US" for America. Can be "".
}

locales = SDL.Locale.GetPreferred()
--[[
	Report the user's preferred locale.

	This returns an table of Locale tables.
 
	Returned language strings are in the format xx, where 'xx' is an ISO-639
	language specifier (such as "en" for English, "de" for German, etc). Country 
	strings are in the format YY, where "YY" is an ISO-3166 country code (such as 
	"US" for the United States, "CA" for Canada, etc). Country might be "" if 
	there's no specific guidance on them (so you might get { "en", "US" } for 
	American English, but { "en", "" } means "English language, generically"). 
	Language strings are never NULL, except to terminate the array.
 
	Please note that not all of these strings are 2 characters; some are three
	or more.

	The returned list of locales are in the order of the user's preference. For 
	example, a German citizen that is fluent in US English and knows enough Japanese 
	to navigate around Tokyo might have a list like: { "de", "en_US", "jp", "" }. 
	Someone from England might prefer British English (where "color" is spelled 
	"colour", etc), but will settle for anything like it: { "en_GB", "en", "" }.
 
	This function returns nil on error, including when the platform does not
	supply this information at all.

	This might be a "slow" call that has to query the operating system. It's
	best to ask for this once and save the results. However, this list can
	change, usually because the user has changed a system preference outside of
	your program; SDL will send an "LOCALECHANGED" event in this case, if
	possible, and you can call this function again to get an updated copy of
	preferred locales.

	\return locales		table of locales. Will return nil on error.
--]]

--------------------------------------------------------------------------MessageBox
MessageBox:
"ERROR", "WARNING", "INFORMATION", "BUTTONS_LEFT_TO_RIGHT", "BUTTONS_RIGHT_TO_LEFT"
		
MessageBoxButton:
"RETURNKEY", "ESCAPEKEY"


MessageBoxData = {
	window,				-- window object or nil
	flags,				-- Icon-Type "ERROR", "WARNING", "INFORMATION"
	title,				-- Title string
	message,			-- Message string
	buttons = {			-- table with all buttons
		{	
			flags,		-- "RETURNKEY" Marks the default button when return is hit
						-- "ESCAPEKEY" Marks the default button when escape is hit
			buttonid,	-- User defined button id 
						-- (value returned via SDL.MessageBox.Show)
			Text		-- The UTF-8 button text 
		},
		...				-- additional buttons
	},
}

button = SDL.MessageBox.Show( msg )
--[[
	Create a modal message box.
	
	This function may be called at any time, even before SDL.Init().

	\param msg 		the MessageBoxData table with title, text and other options
	\returns button	selected buttonid or nil on failure.
					call SDL.Error.Get() for more information.	
--]]

success = SDL.MessageBox.ShowSimple(flag, title, msg, window)
--[[
	Display a simple modal message box.
	
	`flags` may be any of the following:
		"ERROR"  		error dialog
		"WARNING"  		warning dialog
		"INFORMATION" 	informational dialog
		
	This function may be called at any time, even before SDL.Init().	

	\param flags		"ERROR", "WARNING", "INFORMATION"
	\param title 		UTF-8 title text
	\param message 		UTF-8 message text
	\param window 		the window-object, or nil for no parent
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.		
--]]

--------------------------------------------------------------------------------Misc
success = SDL.OpenURL ( url )
--[[
	Open a URL/URI in the browser or other appropriate external application.

	Open a URL in a separate, system-provided application. How this works will
	vary wildly depending on the platform. This will likely launch what makes
	sense to handle a specific URL's protocol (a web browser for `http://`,
	etc), but it might also be able to launch file managers for directories and
	other things.

	What happens when you open a URL varies wildly as well: your game window
	may lose focus (and may or may not lose focus if your game was fullscreen
	or grabbing input at the time). On mobile devices, your app will likely
	move to the background or your process might be paused. Any given platform
	may or may not handle a given URL.

	If this is unimplemented (or simply unavailable) for a platform, this will
	fail with an error. A successful result does not mean the URL loaded, just
	that we launched _something_ to handle it (or at least believe we did).

	\param url 			A valid URL/URI to open. Use `file:///full/path/to/file` 
						for local files, if supported.
	\returns success 	true on success, or false on error
--]]


-------------------------------------------------------------------------------Mouse
SystemCursor:
"ARROW", "IBEAM", "WAIT", "CROSSHAIR", "WAITARROW", "SIZENWSE", "SIZENESW", "SIZEWE",
"SIZENS", "SIZEALL", "NO", "HAND"

MouseWheel:
"NORMAL", "FLIPPED"

MouseButton:
"NONE", "LEFT", "RIGHT", "MIDDLE", "X1", "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9", "X10", "X11", "X12", "X13"

window = SDL.Mouse.GetFocus()
--[[
	Get the window which currently has mouse focus.

	\returns window		the window with mouse focus.
--]]

button, x, y = SDL.Mouse.GetState()
--[[
	Retrieve the current state of the mouse.

	The current button state is returned as a string and `x` and `y` are set to 
	the mouse cursor position relative to the focus window. 
	
	\returns button		combination of "LEFT" "RIGHT" "MIDDLE", ...
	\returns x 			the x coordinate of the mouse cursor position 
						relative to the focus window
	\returns y 			the y coordinate of the mouse cursor position 
						relative to the focus window
--]]

button, x, y = SDL.Mouse.GetGlobalState()
--[[
	Get the current state of the mouse in relation to the desktop.

	This works similarly to SDL.Mouse.GetState(), but the coordinates will be
	reported relative to the top-left of the desktop. This can be useful if you
	need to track the mouse outside of a specific window and SDL.Mouse.Capture()
	doesn't fit your needs. For example, it could be useful if you need to
	track the mouse while dragging a window, where coordinates relative to a
	window might not be in sync at all times.
	
	Note: SDL.Mouse.GetState() returns the mouse position as SDL understands it
	from the last pump of the event queue. This function, however, queries the
	OS for the current mouse position, and as such, might be a slightly less
	efficient function. Unless you know what you're doing and have a good
	reason to use this function, you probably want SDL.Mouse.GetState() instead.
	
	\returns button		combination of "LEFT" "RIGHT" "MIDDLE", ...
	\returns x 			the x coordinate of the mouse cursor position 
						relative to the desktop
	\returns y 			the y coordinate of the mouse cursor position 
						relative to the desktop
--]]

button, x, y = SDL.Mouse.GetRelativeState()
--[[
	Retrieve the relative state of the mouse.
	`x` and `y` are set to the mouse deltas since the last call to SDL.Mouse.GetRelativeState() or since event initialization. 

	\returns button		combination of "LEFT" "RIGHT" "MIDDLE", ...
	\returns x			the last recorded x coordinate of the mouse
	\returns y			the last recorded y coordinate of the mouse
--]]	

SDL.Mouse.WarpInWindow( win, x, y )
-- SDL.Window.WarpMouseIn( win, x, y )
--[[
	Move the mouse cursor to the given position within the window.
 
	This function generates a mouse motion event.

	Note that this function will appear to succeed, but not actually move the
	mouse when used over Microsoft Remote Desktop.

	\param window 		the window to move the mouse into, or nil for the current
						mouse focus
	\param x 			the x coordinate within the window
	\param y 			the y coordinate within the window
--]]

success = SDL.Mouse.WarpGlobal( x, y )
--[[
	Move the mouse to the given position in global screen space.

	This function generates a mouse motion event.

	A failure of this function usually means that it is unsupported by a platform.

	Note that this function will appear to succeed, but not actually move the
	mouse when used over Microsoft Remote Desktop.

	\param x 			the x coordinate
	\param y 			the y coordinate
	\returns success	true on success or false on failure
--]]
	
success = SDL.Mouse.SetRelativeMode( state )
--[[
	Set relative mouse mode.

	While the mouse is in relative mode, the cursor is hidden, and the driver
	will try to report continuous motion in the current window. Only relative
	motion events will be delivered, the mouse position will not change.

	Note that this function will not be able to provide continuous relative
	motion when used over Microsoft Remote Desktop, instead motion is limited
	to the bounds of the screen.

	This function will flush any pending mouse motion.

	\param enabled 		true to enable relative mode, false to disable.
	\returns success	true on success or false on failure
--]]

state = SDL.Mouse.GetRelatvieMode ()
--[[
	Query whether relative mouse mode is enabled.

	\returns state		true if relative mode is enabled or false otherwise.
--]]

success = SDL.Mouse.Capture ( state )
--[[ 
	 Capture the mouse and to track input outside an SDL window.

	Capturing enables your app to obtain mouse events globally, instead of just
	within your window. Not all video targets support this function. When
	capturing is enabled, the current window will get all mouse events, but
	unlike relative mode, no change is made to the cursor and it is not
	restrained to your window.
 
	This function may also deny mouse input to other windows--both those in
	your application and others on the system--so you should use this function
	sparingly, and in small bursts. For example, you might want to track the
	mouse while the user is dragging something, until the user releases a mouse
	button. It is not recommended that you capture the mouse for long periods
	of time, such as the entire time your app is running. For that, you should
	probably use SDL.Mouse.SetRelativeMode() or SDL.Window.SetGrab(), depending
	on your goals.

	While captured, mouse events still report coordinates relative to the
	current (foreground) window, but those coordinates may be outside the
	bounds of the window (including negative values). Capturing is only allowed
	for the foreground window. If the window loses focus while capturing, the
	capture will be disabled automatically.

	While capturing is enabled, the current window will have the
	"MOUSE_CAPTURE" flag set.

	\param state		true to enable capturing, false to disable.
	\returns success	true on success or false if not supported
--]]

cursor = SDL.Cursor.Create( surface, hot_x, hot_y)
cursor = SDL.Cursor.Create( SystemCursor )
--[[
	Create a color cursor.

	\param surface 		an Surface object representing the cursor image
	\param hot_x 		the x position of the cursor hot spot
	\param hot_y 		the y position of the cursor hot spot
	\returns cursor 	the new cursor on success or nil on failure
--]]

SDL.Cursor.Set( cursor )
--[[
	Set the active cursor.

	This function sets the currently active cursor to the specified one. If the
	cursor is currently visible, the change will be immediately represented on
	the display. SDL.Cursor.Set(nil) can be used to force cursor redraw, if
	this is desired for any reason.

	\param cursor 		a cursor to make active	
--]]

cursor = SDL.Cursor.Get()
--[[
	Get the active cursor.

	This function returns to the current cursor which is owned by the library. 
	It is not necessary to free the cursor with SDL.Cursor.Free().

	\returns cursor 	the active cursor or nil if there is no mouse.
--]]

cursor = SDL.Cursor.GetDefault()
--[[
	Get the default cursor.

	\returns cursor		the default cursor on success or nil on failure.
--]]

SDL.Cursor.Free( cursor )
--[[
	Free a previously-created cursor.

	Use this function to free cursor resources created with SDL.Cursor.Create().

	\param cursor 		the cursor to free
--]]

state = SDL.Cursor.Show( toggle )
--[[
	Toggle whether or not the cursor is shown.

	The cursor starts off displayed but can be turned off. Passing "ENABLE"
	displays the cursor and passing "DISABLE" hides it.

	The current state of the mouse cursor can be queried by passing
	"SDL_QUERY"; either "DISABLE" or "ENABLE" will be returned.

	\param toggle 		"ENABLE" to show the cursor, "DISABLE" to hide it,
						"QUERY" to query the current state without changing it.
	\returns state		"ENABLE" if the cursor is shown, or "DISABLE" if the
						cursor is hidden, or nil on failure
--]]

-------------------------------------------------------------------------PixelFormat
PixelFormatEnum:
 "UNKNOWN", "INDEX1LSB", "INDEX1MSB", "INDEX4LSB", "INDEX4MSB", "INDEX8", "RGB332", 
 "XRGB4444", "RGB444", "XBGR4444", "BGR444", "XRGB1555", "RGB555", "XBGR1555", 
 "BGR555", "ARGB4444", "RGBA4444", "ABGR4444", "BGRA4444", "ARGB1555", "RGBA5551", 
 "ABGR1555", "BGRA5551", "RGB565", "BGR565", "RGB24", "BGR24", "XRGB8888", "RGB888", 
 "RGBX8888", "XBGR8888", "BGR888", "BGRX8888", "ARGB8888", "RGBA8888", "ABGR8888", 
 "BGRA8888", "ARGB2101010", "RGBA32", "ARGB32", "BGRA32", "ABGR32", "YV12", "IYUV", 
 "YUY2", "UYVY", "YVYU", "NV12", "NV21", "EXTERNAL_OES"
 
color = {
	r,			-- red 0 - 255
	g, 			-- green 0 - 255
	b,			-- blue 0 - 255
	a			-- alpha 0-255
}

PixelFormat		-- PixelFormat object

PixelFormat = SDL.PixelFormat.Alloc( PixelFormatEnum)
--[[
	Create an PixelFormat object corresponding to a pixel format.

	\param PixelFormatEnum	one of the PixelFormatEnum values
	\returns PixelFormat	the new PixelFormat object or nil on failure; 
							call SDL.Error.Get() for more information.
--]]

SDL.PixelFormat.Free( PixelFormat )
--[[
	Free an PixelFormat object allocated by SDL.PixelFormat.Alloc().

	\param PixelFormat	the PixelFormat object to free
--]]

pixel = SDL.PixelFormat.MapRGB( PixelFormat, r, g, b )
--[[
	Map an RGB triple to an opaque pixel value for a given pixel format.

	This function maps the RGB color value to the specified pixel format and
	returns the pixel value best approximating the given RGB color value for
	the given pixel format.


	If the specified pixel format has an alpha component it will be returned as
	all 1 bits (fully opaque).


	\param PixelFormat	an PixelFormat object describing the pixel format
	\param r 			the red component of the pixel in the range 0-255
	\param g 			the green component of the pixel in the range 0-255
	\param b 			the blue component of the pixel in the range 0-255
	\returns pixel		a pixel value
--]]

pixel = SDL.PixelFormat.MapRGBA( PixelFormat, r, g, b, a )
--[[
	Map an RGBA quadruple to a pixel value for a given pixel format.

	This function maps the RGBA color value to the specified pixel format and
	returns the pixel value best approximating the given RGBA color value for
	the given pixel format.

	If the specified pixel format has no alpha component the alpha value will
	be ignored (as it will be in formats with a palette).


	\param PixelFormat 	an PixelFormat object describing the pixel format
	\param r 			the red component of the pixel in the range 0-255
	\param g 			the green component of the pixel in the range 0-255
	\param b 			the blue component of the pixel in the range 0-255
	\param a 			the alpha component of the pixel in the range 0-255
	\returns pixel		a pixel value
--]]

r, g, b = SDL.PixelFormat.GetRGB( PixelFormat, pixel )
--[[
	Get RGB values from a pixel in the specified format.

	This function uses the entire 8-bit [0..255] range when converting color
	components from pixel formats with less than 8-bits per RGB component
	(e.g., a completely white pixel in 16-bit RGB565 format would return [0xff,
	0xff, 0xff] not [0xf8, 0xfc, 0xf8]).

	\param PixelFormat 	an PixelFormat object describing the pixel format
	\param pixel 		a pixel value
	\returns r 			the red component
	\returns g 			the green component
	\returns b 			the blue component

--]]

r, g, b, a = SDL.PixelFormat.GetRGBA( PixelFormat, pixel )
--[[
	Get RGBA values from a pixel in the specified format.

	This function uses the entire 8-bit [0..255] range when converting color
	components from pixel formats with less than 8-bits per RGB component
	(e.g., a completely white pixel in 16-bit RGB565 format would return [0xff,
	0xff, 0xff] not [0xf8, 0xfc, 0xf8]).

	If the surface has no alpha component, the alpha will be returned as 0xff
	(100% opaque).

	\param PixelFormat 	an PixelFormat object describing the pixel format
	\param pixel 		a pixel value
	\returns r 			the red component
	\returns g 			the green component
	\returns b 			the blue component
	\returns a 			the alpha component
--]]

-------------------------------------------------------------------------------Power
PowerState:
"UNKNOWN", "ON_BATTERY", "NO_BATTERY", "CHARGING", "CHARGED"


state, sec, pct = SDL.Power.GetInfo()
--[[
	Get the current power supply details.
	
	It's possible a platform can only report battery percentage or time left
	but not both.
	
	\returns state	"UNKNOWN", "ON_BATTERY", "NO_BATTERY", "CHARGING", "CHARGED"
	\returns secs 	seconds of battery life left, will return -1 if we can't 		
					determine a value, or we're not running on a battery
	\returns pct 	percentage of battery life left, between 0 and 100, will 
					return -1 if we can't determine a value, or we're not running
					on a battery
--]]

--------------------------------------------------------------------------------Rect
Point = {
	x,				-- integer
	f,
}
FPoint = {
	x,				-- number
	y,
}
Rect = {
	x,				-- integer
	y,
	w,				-- width
	h				-- height
}
FRect = {
	x,				-- number
	y,
	w,				-- width
	h				-- height
}

bool = SDL.Rect.ContainsPoint( Rect, Point )
--[[
	Returns true if point resides inside a rectangle.
--]]

bool = SDL.Rect.Empty( Rect1 )
--[[
	Returns true if the rectangle has no area.
--]]

bool = SDL.Rect.Equals ( Rect1, Rect2 )
--[[
	Returns true if the two rectangles are equal.
--]]

intersection = SDL.Rect.Intersection ( Rect1, Rect2 )
--[[
	Calculate the intersection of two rectangles.
	
	\param Rect1			an Rect table representing the first rectangle
	\param Rect2 			an Rect table representing the second rectangle
	\returns intersection 	an Rect table filled in with the intersection of
							rectangles 1 and 2 or nil
--]]

union = SDL.Rect.Union( Rect1, Rect2 )
--[[
	Calculate the union of two rectangles.

	\param Rect1 			an Rect table representing the first rectangle
	\param Rect2  			an Rect table representing the second rectangle
	\returns union			an Rect table filled in with the union of 	
							rectangles 1 and 2						
--]]

x1, y1, x2, y2 = SDL.Rect.IntersectLine( Rect, x1, y1, x2, y2)
--[[
	Calculate the intersection of a rectangle and line segment.
	
	This function is used to clip a line segment to a rectangle. A line segment
	contained entirely within the rectangle will remain unchanged. A line segment 
	that crosses the rectangle at either or	both ends will be clipped to the 
	boundary of the rectangle and the new coordinates will be returned.
	
	\param rect 	an Rect table representing the rectangle to intersect
	\param X1 		starting X-coordinate of the line
	\param Y1 		starting Y-coordinate of the line
	\param X2 		ending X-coordinate of the line
	\param Y2 		ending Y-coordinate of the line
	\returns X1 	starting X-coordinate of the line or nil
	\returns Y1 	starting Y-coordinate of the line or nil
	\returns X2 	ending X-coordinate of the line or nil
	\returns Y2 	ending Y-coordinate of the line or nil
--]]

rect = SDL.Rect.EnclosePoints( points, clip )
--[[
	Calculate a minimal rectangle enclosing a set of points.

	If `clip` is not nil then only points inside of the clipping rectangle are
	considered.

	\param points 	an table of Point tables representing points to be enclosed
	\param clip 	an Rect table used for clipping or nil to enclose all points
	\returns rect	an Rect table filled in with the minimal enclosing rectangle
--]]

----------------------------------------------------------------------------Renderer
Renderer:
"SOFTWARE", "ACCELERATED", "PRESENTVSYNC", "TARGETTEXTURE"

ScaleMode:
"NEAREST", "LINEAR", "BEST"

TextureAccess:
"STATIC", "STREAMING", "TARGET"

TextureModulate:
"NONE", "COLOR", "ALPHA"

RenderFlip:
"NONE", "HORIZONTAL", "VERTICAL"

Renderer 		-- a Renderer object
Texture			-- a Texture object

RendererInfo = {
	name,				-- The name of the renderer
	flags,				-- Flags
							-- "SOFTWARE" 		The renderer is a software fallback 
							-- "ACCELERATED"	The renderer uses hardware
							-- "PRESENTVSYNC"	Present is synchronized with the 	
												-- refresh rate
							-- "TARGETTEXTURE"	The renderer supports rendering to 
												-- texture
	texture_formats		-- table with PixelFormatEnums
	max_texture_width	-- The maximum texture width
	max_texture_height	-- The maximum texture height
}

num = SDL.Render.GetNumDrivers()
--[[
	Get the number of 2D rendering drivers available for the current display.

	A render driver is a set of code that handles rendering and texture
	management on a particular display. Normally there is only one, but some
	drivers may have several available with different capabilities.

	There may be none if SDL was compiled without render support.

	\returns num		a number >= 0 on success or a negative code on failure
--]]

info = SDL.Render.GetDriverInfo(index)
--[[
	Get info about a specific 2D rendering driver for the current display.

	\param index 	the index of the driver to query information about
	\returns info 	an RendererInfo table with information on the rendering driver,
					or nil on failure
--]]

Renderer = SDL.Render.Create( window [, index, flags] )
-- Renderer = SDL.Window.CreateRenderer( window, index, flags )
--[[
	Create a 2D rendering context for a window.

	\param window 		the window where rendering is displayed
	\param index 		the index of the rendering driver to initialize, 
						or -1 to initialize the first one supporting the 
						requested flags, default -1
	\param flags 		"SOFTWARE", "ACCELERATED", "PRESENTVSYNC", "TARGETTEXTURE"
						default "ACCELERATED PRESENTVSYNC"
	\returns Renderer	a valid rendering context or nil
--]]

Renderer = SDL.Render.CreateSoftware( surface )
-- Renderer = SDL.Surface.CreateSoftwareRenderer ( surface )
--[[
	Create a 2D software rendering context for a surface.

	SDL.Render.Create() can _also_ create a software renderer, but they are 
	intended to be used with an Window object as the final destination and not an 
	Surface object.

	\param surface 		the SDL_Surface structure representing the surface where
						rendering is done
	\returns Renderer	a valid rendering context or nil if there was an error
--]]

Renderer = SDL.Render.Get( window )
-- Renderer = SDL.Window.GetRenderer( window )
--[[
	Get the renderer associated with a window.

	\param window 		the window to query
	\returns Renderer	the rendering context on success or nil
--]]

info = SDL.Render.GetInfo( renderer )
--[[
	Get information about a rendering context.

	\param renderer 	the rendering object
	\returns info 		an RendererInfo table 
--]]

w, h = SDL.Render.GetOutputSize( renderer )
--[[
	Get the output size in pixels of a rendering context.

	Due to high-dpi displays, you might end up with a rendering context that
	has more pixels than the window that contains it, so use this instead of
	SDL.Window.GetSize() to decide how much drawing area you have.

	\param renderer 	the rendering context
	\returns w 			the width
	\returns h 			the height
--]]

texture = SDL.Render.CreateTexture( renderer, format, access, w, h )
-- texture = SDL.Texture.Create( renderer, format, w, h )
texture = SDL.Render.CreateTexture( renderer, surface )
-- texture = SDL.Texture.Create( renderer, surface )
--[[
	---- format - Version ----

	Create a texture for a rendering context.

	You can set the texture scaling method by setting hint "RENDER_SCALE_QUALITY" 
	before creating the texture.

	\param renderer 	the rendering context
	\param format 		PixelFormatEnum or PixelFormat object
	\param access 		one of the values:
						"STATIC" 	Changes rarely, not lockable
						"STREAMING"	Changes frequently, lockable
						"TARGET"	Texture can be used as a render target
	\param w 			the width of the texture in pixels
	\param h 			the height of the texture in pixels
	\returns texture 	the created texture object or nil 

	---- surface - Version ----
	Create a texture from an existing surface.

	The surface is not modified or freed by this function.

	The TextureAccess hint for the created texture is "STATIC".

	The pixel format of the created texture may be different from the pixel
	format of the surface. Use SDL.Texture.Query() to query the pixel format of
	the texture.

	\param renderer 		the rendering context
	\param surface 			the Surface object containing pixel data used to fill
							the texture
	\returns texture		the created texture or nil on failure
--]]

format, access, w, h = SDL.Texture.Query( texture )
--[[
	Query the attributes of a texture.
 
	\param texture 			the texture to query
	\returns format 		PixelFormatEnum; the actual format may differ, but 
							pixel transfers will use this format
	\returns access			"STATIC", "STREAMING" or "TARGET"
	\returns w 				the width of the texture in pixels
	\returns h 				the height of the texture in pixels
--]]

success = SDL.Texture.SetColorMod( texture, r, g, b )
--[[
	Set an additional color value multiplied into render copy operations.

	When this texture is rendered, during the copy operation each source color
	channel is modulated by the appropriate color value according to the
	following formula:

		srcC = srcC * (color / 255)

	Color modulation is not always supported by the renderer; it will return false
	if color modulation is not supported.
 
	\param texture 		the texture to update
	\param r 			the red color value multiplied into copy operations
	\param g 			the green color value multiplied into copy operations
	\param b 			the blue color value multiplied into copy operations
	\returns success	true on success or false on failure
--]]
 
r,g,b = SDL.Texture.GetColorMod( texture )
--[[
	Get the additional color value multiplied into render copy operations.
	
	\param texture 		the texture to update
	\returns r 			the red color value multiplied into copy operations
	\returns g 			the green color value multiplied into copy operations
	\returns b 			the blue color value multiplied into copy operations
--]]
 
success = SDL.Texture.SetAlphaMod( texture, alpha )
--[[
	Set an additional alpha value multiplied into render copy operations.

	When this texture is rendered, during the copy operation the source alpha
	value is modulated by this alpha value according to the following formula:

		srcA = srcA * (alpha / 255)

	Alpha modulation is not always supported by the renderer; it will return false
	if alpha modulation is not supported.

	\param texture 		the texture to update
	\param alpha 		the source alpha value multiplied into copy operations
	\returns success	true on success or false on failure
--]]

alpha = SDL.Texture.GetAlphaMod( texture )
--[[
	Get the additional alpha value multiplied into render copy operations.

	\param texture 		the texture to update
	\returns alpha 		the source alpha value multiplied into copy operations
--]]

success = SDL.Texture.SetBlendMode( texture, blendmode )
--[[
	Set the blend mode for a texture, used by SDL_RenderCopy().

	If the blend mode is not supported, the closest supported mode is chosen
	and this function returns false.

	\param texture 		the texture to update
	\param blendMode 	the BlendMode to use for texture blending
	\returns success	true on success or false on failure
--]]

blendMode = SDL.Texture.GetBlendMode( texture )
--[[
	Get the blend mode used for texture copy operations.
 
	\param texture 		the texture to query
	\returns blendMode 	the current SDL_BlendMode
--]]

success = SDL.Texture.SetScaleMode( texture, scaleMode )
--[[
	Set the scale mode used for texture scale operations.
 
	If the scale mode is not supported, the closest supported mode is chosen.

	\param texture 		The texture to update.
	\param scaleMode 	the ScaleMode
							"NEAREST"	nearest pixel sampling
							"LINEAR"	linear filtering
							"BEST"		anisotropic filtering
	\returns success	true on success, or false if the texture is not valid
--]]

scaleMode = SDL.Texture.GetScaleMode( texture )
--[[
	Get the scale mode used for texture scale operations.
 
	\param texture 		the texture to query.
	\returns scaleMode 	"NEAREST", "LINEAR", "BEST"
--]]

success = SDL.Texture.SetUserData( texture, data )
--[[
	Associate a user-specified data with a texture.

	\param texture 		the texture to update.
	\param userdata 	the value to associate with the texture.
	\returns success 	true on success, or false if the texture is not valid.
--]]

data = SDL.Texture.GetUserData( texture )
--[[
	Get the user-specified pointer associated with a texture

	\param texture 		the texture to query.
	\return data		the value associated with the texture
--]]

data, pitch = SDL.Texture.Lock( texture, rect )
--[[
	Lock a portion of the texture for **write-only** pixel access.

	As an optimization, the pixels made available for editing don't necessarily
	contain the old texture data. This is a write-only operation, and if you
	need to keep a copy of the texture data you should do that at the
	application level.

	You must use SDL.Texture.Unlock() to unlock the pixels and apply any changes.
 
	\param texture 		the texture to lock for access, which was created with
						"STREAMING"
	\param rect 		an Rect table representing the area to lock for access;
						nil to lock the entire texture
	\returns data 		this is filled in with a Data object to the locked pixels,
						appropriately offset by the locked area
	\returns pitch 		this is filled in with the pitch of the locked pixels; 
						the pitch is the length of one row in bytes
--]]

surface = SDL.Texture.LockToSurface( texture, rect )
--[[
	Lock a portion of the texture for **write-only** pixel access, and expose
	it as a SDL surface object.

	Besides providing an SDL_Surface instead of raw pixel data, this function
	operates like SDL.Texture.Lock.

	As an optimization, the pixels made available for editing don't necessarily
	contain the old texture data. This is a write-only operation, and if you
	need to keep a copy of the texture data you should do that at the
	application level.

	You must use SDL.Texture.Unlock() to unlock the pixels and apply any changes.

	The returned surface is freed internally after calling SDL.Texture.Unlock()
	or SDL.Texture.Destroy(). The caller should not free it.

	\param texture 		the texture to lock for access, which was created with
						"STREAMING"
	\param rect 		an Rect table representing the area to lock for access;
						nil to lock the entire texture
	\returns surface	an SDL surface representing the locked area
--]]

SDL.Texture.Unlock( texture )
--[[
	Unlock a texture, uploading the changes to video memory, if needed.

	**Warning**: Please note that SDL.Texture.Lock() is intended to be
	write-only; it will not guarantee the previous contents of the texture will
	be provided. You must fully initialize any area of a texture that you lock
	before unlocking it, as the pixels might otherwise be uninitialized memory.

	Which is to say: locking and immediately unlocking a texture can result in
	corrupted textures, depending on the renderer in use.

	\param texture 		a texture locked by SDL.Texture.Lock()
--]]

bool = SDL.Render.TargetSupported( renderer )
--[[
	Determine whether a renderer supports the use of render targets.

	\param renderer 	the renderer that will be checked
	\returns bool		true if supported or false if not.
--]]

success = SDL.Render.SetTarget( renderer, texture )
--[[
	Set a texture as the current rendering target.

	Before using this function, you should check the 
	SDL.Render.TargetSupported to see if render targets are supported.

	The default render target is the window for which the renderer was created.
	To stop rendering to a texture and render to the window again, call this
	function with a nil `texture`.
 
	\param renderer 	the rendering context
	\param texture 		the targeted texture, which must be created with the
						"TARGET" flag, or nil to render to the window instead 
						of a texture.
	\returns success	true on success or false on failure
--]]

texture = SDL.Render.GetTarget( renderer )
--[[
	Get the current render target.

	The default render target is the window for which the renderer was created,
	and is reported a nil here.

	\param renderer 	the rendering context
	\returns texture	the current render target or nil for the default render 
						target.
--]]

success = SDL.Render.SetLogicalSize( renderer, w, h )
--[[
	Set a device independent resolution for rendering.

	This function uses the viewport and scaling functionality to allow a fixed
	logical resolution for rendering, regardless of the actual output
	resolution. If the actual output resolution doesn't have the same aspect
	ratio the output rendering will be centered within the output display.

	If the output display is a window, mouse and touch events in the window
	will be filtered and scaled so they seem to arrive within the logical
	resolution. The hint "MOUSE_RELATIVE_SCALING" hint controls whether
	relative motion events are also scaled.

	If this function results in scaling or subpixel drawing by the rendering
	backend, it will be handled using the appropriate quality hints.

	\param renderer 	the renderer for which resolution should be set
	\param w 			the width of the logical resolution
	\param h 			the height of the logical resolution
	\returns success	true on success or false on failure
--]]

w, h = SDL.Render.GetLogicalSize( renderer )
--[[
	Get device independent resolution for rendering.

	This may return 0 for `w` and `h` if the Renderer has never had its
	logical size set by SDL_RenderSetLogicalSize() and never had a render
	target set.

	\param renderer 	a rendering context
	\returns w 			the width
	\returns h 			the height
--]]
 
success = SDL.Render.SetIntegerScale( renderer, state )
--[[
	Set whether to force integer scales for resolution-independent rendering.

	This function restricts the logical viewport to integer values - that is,
	when a resolution is between two multiples of a logical size, the viewport
	size is rounded down to the lower multiple.

	\param renderer 	the renderer for which integer scaling should be set
	\param state 		enable or disable the integer scaling for rendering
	\returns success	true on success or false on failure
--]]

state = SDL.Render.GetIntegerScale( renderer )
--[[
	Get whether integer scales are forced for resolution-independent rendering.
 
	\param renderer 	the renderer from which integer scaling should be queried
	\returns 			true if integer scales are forced or false if not and on
						failure	
--]]

success = SDL.Render.SetViewport( renderer, rect )
--[[
	Set the drawing area for rendering on the current target.

	When the window is resized, the viewport is reset to fill the entire new
	window size.

	\param renderer 	the rendering context
	\param rect 		the Rect table representing the drawing area, or nil
						to set the viewport to the entire target
	\returns success	true on success or false on failure
--]]

rect = SDL.Render.GetViewport( renderer )
--[[
	Get the drawing area for the current target.

	\param renderer 	the rendering context
	\returns rect 		an Rect table filled in with the current drawing area
--]]

success = SDL.Render.SetClipRect( renderer, rect )
--[[
	Set the clip rectangle for rendering on the specified target.

	\param renderer 	the rendering context for which clip rectangle should be
						set
	\param rect 		an Rect table representing the clip area, relative to
						the viewport, or nil to disable clipping
	\returns success	true on success or false on failure
--]]

rect = SDL.Render.GetClipRect( renderer )
--[[
	Get the clip rectangle for the current target.

	\param renderer 	the rendering context from which clip rectangle should be
						queried
	\returns rect 		an Rect table filled in with the current clipping area
						or nil if clipping is disabled
--]]

success = SDL.Render.SetScale( renderer, scaleX, scaleY )
--[[
	Set the drawing scale for rendering on the current target.

	The drawing coordinates are scaled by the x/y scaling factors before they
	are used by the renderer. This allows resolution independent drawing with a
	single coordinate system.

	If this results in scaling or subpixel drawing by the rendering backend, it
	will be handled using the appropriate quality hints. For best results use
	integer scaling factors.

	\param renderer 	a rendering context
	\param scaleX 		the horizontal scaling factor
	\param scaleY 		the vertical scaling factor
	\returns success	true on success or false on failure
--]]

scaleX, scaleY = SDL.Render.GetScale( renderer )
--[[
	Get the drawing scale for the current target.

	\param renderer 	the renderer from which drawing scale should be queried
	\returns scaleX 	the horizontal scaling factor
	\returns scaleY 	the vertical scaling factor
--]]

logicalX, logicalY = SDL.Render.WindowToLogical( renderer, windowX, windowY )
--[[
	Get logical coordinates of point in renderer when given real coordinates of
	point in window.

	Logical coordinates will differ from real coordinates when render is scaled
	and logical renderer size set

	\param renderer 	the renderer from which the logical coordinates should be
						calcualted
	\param windowX 		the real X coordinate in the window
	\param windowY 		the real Y coordinate in the window
	\returns logicalX 	the logical x coordinate
	\returns logicalY 	the logical y coordinate
--]]

windowX, windowY = SDL.Render.LogicalToWindow( renderer, logicalX, logicalY)
--[[
	Get real coordinates of point in window when given logical coordinates of 
	point in renderer.

	Logical coordinates will differ from real coordinates when render is scaled 
	and logical renderer size set
 
	\param renderer 	the renderer from which the window coordinates should be 
						calculated
	\param logicalX		the logical x coordinate
	\param logicalY 	the logical y coordinate
	\param windowX 		the real X coordinate in the window
	\param windowY		the real Y coordinate in the window
--]]

success = SDL.Render.SetDrawColor( renderer, r, g, b, a )
success = SDL.Render.SetDrawColor( renderer, color )
--[[
	Set the color used for drawing operations (Rect, Line and Clear).

	Set the color for drawing or filling rectangles, lines, and points, and for
	SDL.Render.Clear().

	\param renderer 	the rendering context
	\param color		a color table
	\param r 			the red value used to draw on the rendering target
	\param g 			the green value used to draw on the rendering target
	\param b 			the blue value used to draw on the rendering target
	\param a 			the alpha value used to draw on the rendering target; 
						usually 255. Use SDL.Render.SetDrawBlendMode to
						specify how the alpha channel is used
	\returns success	true on success or false on failure
--]]

r, g, b,a = SDL.Render.GetDrawColor( renderer )
--[[
	Get the color used for drawing operations (Rect, Line and Clear).

	\param renderer 	the rendering context
	\param r 			the red value used to draw on the rendering target
	\param g 			the green value used to draw on the rendering target
	\param b 			the blue value used to draw on the rendering target
	\param a 			the alpha value used to draw on the rendering target
--]]

success = SDL.Render.SetDrawBlendMode( renderer, BlendMode )
--[[
	Set the blend mode used for drawing operations (Fill and Line).

	If the blend mode is not supported, the closest supported mode is chosen.

	\param renderer 	the rendering context
	\param blendMode 	the BlendMode to use for blending
	\returns success	true on success or false on failure
--]]

success = SDL.Render.Clear( renderer )
--[[
	Clear the current rendering target with the drawing color.

	This function clears the entire rendering target, ignoring the viewport and
	the clip rectangle.

	\param renderer 	the rendering context
	\returns success	true on success or false on failure
--]]

success = SDL.Render.DrawPoint( renderer, x, y )
--[[
	Draw a point on the current rendering target.

	\param renderer 	the rendering context
	\param x 			the x coordinate of the point
	\param y			the y coordinate of the point
	\returns success	true on success or false on failure
--]]

success = SDL.Render.DrawPoints( renderer, points )
--[[
	Draw multiple points on the current rendering target.

	\param renderer 	the rendering context
	\param points 		an table of Point tables that represent the points to draw
	\returns success	true on success or false on failure
--]]

success = SDL.Render.DrawLine( render, x1, y1, x2, y2 )
--[[
	Draw a line on the current rendering target.

	SDL.Render.DrawLine() draws the line to include both end points. 
 
	\param renderer 	the rendering context
	\param x1 			the x coordinate of the start point
	\param y1 			the y coordinate of the start point
	\param x2 			the x coordinate of the end point
	\param y2 			the y coordinate of the end point
	\returns success	true on success or false on failure
--]]

success = SDL.Render.DrawLines( renderer, points )
--[[
	Draw a series of connected lines on the current rendering target.

	\param renderer 	the rendering context
	\param points 		a table of Point tables representing points along the lines
	\returns success	true on success or fail on failure
--]]

success = SDL.Render.DrawRect( renderer, rect )
--[[
	Draw a rectangle on the current rendering target.

	\param renderer 	the rendering context
	\param rect 		a Rect table the rectangle to draw, 
						or nil to outline the entire rendering target
	\returns success	true on success or false failure
--]]

success = SDL.Render.DrawRects( renderer, rect )
--[[
	Draw some number of rectangles on the current rendering target.

	\param renderer 	the rendering context
	\param rects 		a table of Rect tables representing the rectangles to
						be drawn
	\returns success	true on success or false failure
--]]

success = SDL.Render.FillRect( renderer, rect )
--[[
	Fill a rectangle on the current rendering target with the drawing color.

	\param renderer 	the rendering context
	\param rect 		a Rect structure table the rectangle to draw, 
						or nil for the entire rendering target
	\returns success	true on success or false failure
--]]

success = SDL.Render.FillRects( renderer, rects )
--[[
	Fill some number of rectangles on the current rendering target with the
	drawing color.

	\param renderer 	the rendering context
	\param rects 		an table of Rect tables representing the rectangles to
						be filled
	\returns success	true on success or false failure
--]]

success = SDL.Render.Copy( render, texture, srcRect, dstRect )
--[[
	Copy a portion of the texture to the current rendering target.

	The texture is blended with the destination based on its blend mode set
	ith SDL.Texture.SetBlendMode().

	The texture color is affected based on its color modulation set by
	SDL.Texture.SetColorMod().

	The texture alpha is affected based on its alpha modulation set by
	SDL.Texture.SetAlphaMod().

	\param renderer 	the rendering context
	\param texture 		the source texture
	\param srcrect 		the source Rect table or nil for the entire texture
	\param dstrect 		the destination Rect table or nil for the entire
						rendering target; the texture will be stretched to fill
						the given rectangle
	\returns success	true on success or false on failure
--]]

success = SDL.Render.CopyEx( render, texture, srcRect, dstRect, angle, center, flip)
--[[
	Copy a portion of the texture to the current rendering, with optional
	rotation and flipping.

	Copy a portion of the texture to the current rendering target, optionally
	rotating it by angle around the given center and also flipping it
	top-bottom and/or left-right.

	The texture is blended with the destination based on its blend mode set
	with SDL.Texture.SetBlendMode().

	The texture color is affected based on its color modulation set by
	SDL.Texture.SetColorMod().

	The texture alpha is affected based on its alpha modulation set by
	SDL.Texture.SetAlphaMod().

	\param renderer 	the rendering context
	\param texture 		the source texture
	\param srcrect 		the source Rect table or nil for the entire texture
	\param dstrect 		the destination Rect table or nil for the entire
						rendering target
	\param angle 		an angle in degrees that indicates the rotation that 
						will be applied to dstrect, rotating it in a clockwise 
						direction
	\param center 		a point indicating the point around which dstrect will
						be rotated (if nil, rotation will be done around 
						`dstrect.w / 2`, `dstrect.h / 2`)
	\param flip 		a RendererFlip value stating which flipping actions should
						be performed on the texture
						"NONE", "HORIZONTAL", "VERTICAL"
	\returns success	true on success or fail on failure
--]]

success = SDL.Render.Geometry( render, texture, vertices, indices )
--[[
	Render a list of triangles, optionally using a texture and indices into the
	vertex array Color and alpha modulation is done per vertex
	(SDL.Texture.SetColorMod and SDL.Texture.SetAlphaMod are ignored).

	\param texture 		The SDL texture to use or nil
	\param vertices 	table of Vertices
						SDL.VERTEX(x,y,r,g,b,a[,tex_x,tex_y])
						{
							position;       -- position SDL.POINT(x,y)
							color;          -- color SDL.COLOR(R,G,B,A)
							tex_coord;      -- position SDL.POINT(x,y)
											-- Normalized texture coordinates
						}
	\param indices		An table of integer indices into the 'vertices' table,
						each triangles need 3 indices. 1 is the first point in
						vertices
						if nil all vertices will be rendered in sequential
						order.
	\returns success	true on success, or false if the operation is not supported
--]]

surface = SDL.Render.ReadPixels( renderer, format  )
--[[
	Read pixels from the current rendering target to an surface.
	
	**WARNING**: This is a very slow operation, and should not be used
	frequently.
	
	\param renderer 	the rendering context
	\param format 		PixelFormatEnum or PixelFormat object
	\returns			the surface object or nil
--]]

SDL.Render.Present( renderer )
--[[
	Update the screen with any rendering performed since the previous call.

	SDL's rendering functions operate on a backbuffer; that is, calling a
	rendering function such as SDL.Render.DrawLine() does not directly put a
	line on the screen, but rather updates the backbuffer. As such, you compose
	your entire scene and *present* the composed backbuffer to the screen as a
	complete picture.

	Therefore, when using SDL's rendering API, one does all drawing intended
	for the frame, and then calls this function once per frame to present the
	final drawing to the user.

	The backbuffer should be considered invalidated after each present; do not
	assume that previous contents will exist between frames. You are strongly
	encouraged to call SDL.Render.Clear() to initialize the backbuffer before
	starting each new frame's drawing, even if you plan to overwrite every
	pixel.

	\param renderer		the rendering context
--]]

SDL.Texture.Destroy( texture )
--[[
	Destroy the specified texture.

	\param texture 		the texture to destroy
--]]

SDL.Render.Destroy( renderer )
--[[
	Destroy the rendering context for a window and free associated textures.

	\param renderer 	the rendering context
--]]

success = SDL.Render.SetVSync( renderer, state )
--[[
	Toggle VSync of the given renderer.

	\param renderer 	The renderer to toggle
	\param vsync 		true for on, false for off. All other values are reserved
--]]

----------------------------------------------------------------------------------RW
RWSeek:
"SET", "CUR", "END"

RWMode:
"READ", "CREATE", "APPEND", "OPEN"

RWops = SDL.RW.Open( file, mode )
--[[
	Reading from and/or writing to a named file.

	Available `mode` strings:
	"READ"				Open a file for reading. The file must exist.
	"OPEN"				Open a file for update both reading and writing. 
						The file must exist.
	"CREATE"			Create an empty file for both reading and writing. 
						If a file with the same name already exists its content is 
						erased and the file is treated as a new empty file.
	"APPEND"			Open a file for reading and appending. All writing
						operations are performed at the end of the file, protecting 
						the previous content to be overwritten. You can reposition 
						the internal pointer to anywhere in the file for reading, 
						but writing operations will move it back to the end of file. 
						The file is created if it does not exist.

	\param file 		a UTF-8 string representing the filename to open
	\param mode 		"READ", "OPEN", "CREATE" or "APPEND"
	\returns RWops		RWops object that is created, or nil on failure
--]]

size = SDL.RW.Size( RWops )
--[[
	 Get the size of the data stream in an RWops.

	\param RWops		the RWops to get the size of the data stream from
	\returns size		the size of the data stream in the RWops on success,  
						nil on failure
--]]

pos = SDL.RW.Seek( RWops, offset, whence )
--[[
	Seek within an SDL_RWops data stream.

	This function seeks to byte `offset`, relative to `whence`.

	`whence` may be any of the following values:
 
	- "SET": seek from the beginning of data
	- "CUR": seek relative to current read point
	- "END": seek relative to the end of data

	If this stream can not seek, it will return nil.
 
	\param RWops		RWops object
	\param offset 		an offset in bytes, relative to **whence** location; 
						can be negative
	\param whence 		any of "SET", "CUR", "END"
	\returns pos		the final offset in the data stream after the seek or 
						nil on error.
--]]

pos = SDL.RW.Tell( RWops )
--[[
	Determine the current read/write offset in an SDL_RWops data stream.
	
	\param RWops		RWops object
	\returns pos		the final offset in the data stream after the seek or 
						nil on error.
--]]

string = SDL.RW.ReadString( RWops, size )
--[[
	Read a string with a fixed size
	
	The string can contain NULL charakters and may be shorter than requested.
	
	\param RWops		RWops object
	\param size			a size in bytes
	\returns string		readed data
--]]

written = SDL.RW.WriteString( RWops, string )
--[[
	Write a string with a fixed size
	
	The string can contain NULL charakters.
	
	\param RWops		RWops object
	\param string		the string to write
	\returns written	the number of bytes written
--]]

success = SDL.RW.Close( RWops )
--[[
	Close and free an RWops object.
	
	Note that if this fails to flush the stream to disk, this function reports
	an error, but the RWops is still invalid once this function returns.
	
	\param RWops		RWops object
	\returns success	true on success or false on failure
--]]

string = SDL.RW.Load( File )
--[[
	Load all the data from a file
	
	\param file 		the path to read all available data from
	\returns string		the file data
--]]

written = SDL.RW.Save( File, string )
--[[
	Save a string to a file
	
	\param				the path to save all available data to
	\param string		the data to save
	\returns written	the number of bytes written
--]]

int = SDL.RW.ReadU8( RWops )
int = SDL.RW.ReadLEU16( RWops )
int = SDL.RW.ReadBEU16( RWops )
int = SDL.RW.ReadLEU32( RWops )
int = SDL.RW.ReadBEU32( RWops )
int = SDL.RW.ReadS8( RWops )
int = SDL.RW.ReadLES16( RWops )
int = SDL.RW.ReadBES16( RWops )
int = SDL.RW.ReadLES32( RWops )
int = SDL.RW.ReadBES32( RWops )
int = SDL.RW.ReadLES64( RWops )
int = SDL.RW.ReadBES64( RWops )
number = SDL.RW.ReadLEFloat( RWops )
number = SDL.RW.ReadBEFloat( RWops )
number = SDL.RW.ReadLEDouble( RWops )
number = SDL.RW.ReadBEDouble( RWops )
--[[
	Use this function to read a bits from a RWops
	
	SDL byteswaps the data only if necessary, so the data returned will be in
	the native byte order.
	
	LE 		little-endian
	BE		big-endian
	U		unsigned
	S		signed
	
	For Win/X64 use SDL.RW.ReadLES64() for integer and SDL.RW.ReadLEDouble().

	\param RWops		RWops object
	\returns int/number	the requested value
	
--]]

success = SDL.RW.Write8( RWops, int )
success = SDL.RW.WriteLE16( RWops, int )
success = SDL.RW.WriteBE16( RWops, int )
success = SDL.RW.WriteLE32( RWops, int )
success = SDL.RW.WriteBE32( RWops, int )
success = SDL.RW.WriteLE64( RWops, int )
success = SDL.RW.WriteBE64( RWops, int )
success = SDL.RW.WriteLEFloat( RWops, number )
success = SDL.RW.WriteBEFloat( RWops, number )
success = SDL.RW.WriteLEDouble( RWops, number )
success = SDL.RW.WriteBEDouble( RWops, number )
--[[
	 Use this function to write bits to a RWops
	 
	SDL byteswaps the data only if necessary, so the data returned will be in
	the native byte order.
	
	LE 		little-endian
	BE		big-endian
	U		unsigned
	S		signed
	
	For Win/X64 use SDL.RW.WriteLES64() for integer and SDL.RW.WriteLEDouble().
	\param RWops		RWops object
	\param int/number	the requested value
	\returns success	true on success or false on failure
--]]


------------------------------------------------------------------------------Sensor
SensorType:
"INVALID", "UNKNOWN", "ACCEL", "GYRO"

SDL.Sensor.GRAVITY
--[[
	Accelerometer sensor

	The accelerometer returns the current acceleration in SI meters per
	second squared. This measurement includes the force of gravity, so
	a device at rest will have an value of SDL.Sensor.GRAVITY away
	from the center of the earth.

	For phones held in portrait mode and game controllers held in front of you,
	the axes are defined as follows:
		 -X ... +X : left ... right
		 -Y ... +Y : bottom ... top
		 -Z ... +Z : farther ... closer

	The axis data is not changed when the phone is rotated.
--]]

--[[
	Gyroscope sensor

	The gyroscope returns the current rate of rotation in radians per second.
	The rotation is positive in the counter-clockwise direction. That is,
	an observer looking from a positive location on one of the axes would
	see positive rotation on that axis when it appeared to be rotating
	counter-clockwise.

	For phones held in portrait mode and game controllers held in front of you,
	the axes are defined as follows:
		-X ... +X : left ... right
		-Y ... +Y : bottom ... top
		-Z ... +Z : farther ... closer
 
	The axis data is not changed when the phone or controller is rotated.
--]]

num = SDL.Sensor.GetNum()
--[[
	Count the number of sensors attached to the system right now.

	\returns the number of sensors detected.
--]]

name = SDL.Sensor.GetName( indexOrSensor )
--[[
	Get the implementation dependent name of a sensor.

	\param indexOrSensor	The sensor index to obtain name from or
							the Sensor object to query from SDL.Sensor.Open
	\returns name			the sensor name
--]]

SensorType = SDL.Sensor.GetType( indexOrSensor )
--[[
	Get the type of a sensor.
	
	\param indexOrSensor	The sensor index to obtain name from or
							the Sensor object to query from SDL.Sensor.Open
	\returns SensorType		The SensorType
--]]


Sensor = SDL.Sensor.Open( index )
--[[
	Open a sensor for use.

	\param index	 		The sensor index to open						
	\returns Sensor			a Sensor object or nil
..]]

x, y, z = SDL.Sensor.GetData( Sensor )
--[[
	Get the current state of an opened sensor.

	The number of values and interpretation of the data is sensor dependent.

	\param sensor 			The Sensor object to query
	\returns x 				current sensor state or nil
	\returns y 				current sensor state or nil
	\returns z 				current sensor state or nil
--]]

SDL.Sensor.Close( Sensor )
--[[
	Close a sensor previously opened with SDL.Sensor.Open().

	\param sensor 			The Sensor object to close
--]]

SDL.Sensor.Update()
--[[
	Update the current state of the open sensors.

	This is called automatically by the event loop if sensor events are
	enabled.
--]]

-----------------------------------------------------------------------------Surface
Conversion:
"JPEG","BT601","BT709","AUTOMATIC"

Surface			-- a Surface Object

PixelFormat = SDL.Surface.GetPixelFormat( Surface )
--[[
	Returns the PixelFormat object from the Surface
	
	\param Surface			a Surface object
	\returns PixelFormat	a PixelFormat object
--]]

w, h, pitch = SDL.Surface.GetSize( Surface )
--[[
	Returns the size of the surface object.

	\param Surface			a Surface object
	\returns w				with of the surface
	\returns h				height of the surface
	\returns pitch			real line width in bytes
--]]

data = SDL.Surface.GetPixels( Surface )
--[[
	Returns a data object which contains the pixel data
	
	\param Surface			a Surface object
	\returns data			a data object
--]]

surface = SDL.Surface.CreateRGB ( width, height, format )
--[[
	Allocate a new RGB surface with a specific pixel format.
	
	By default surfaces with an alpha mask are set up for blending as with:
	SDL.Surface.SetBlendMode(surface, "BLEND")
	
	\param width 		the width of the surface
	\param height 		the height of the surface
	\param format 		the PixelFormatEnum or PixelFormat object for the new 
						surface's pixel format.
	\returns surface	the new Surface object that is created or nil if it fails;
						call SDL.Error.Get() for more information.
--]]
	
SDL.Surface.Free( Surface )
--[[
	Free an RGB surface.

	It is safe to pass nil to this function.
	
	\param surface 		the Surface object to free.
--]]

success = SDL.Surface.Lock( Surface )
--[[
	Set up a surface for directly accessing the pixels.

	Between calls to SDL.Surface.Lock() / SDL.Surface.Unlock(), you can write to
	and read from surface:GetPixels(), using the pixel format stored in
	surface:GetPixelFormat(). Once you are done accessing the surface, you should
	use SDL.Surface.Unlock() to release it.

	\param surface 		the Surface object to be locked
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

SDL.Surface.Unlock( Surface )
--[[
	Release a surface after directly accessing the pixels.

	\param surface 		the Surface onject to be unlocked
--]]

Surface = SDL.Surface.LoadBMP( fileOrRWops )
--[[
	Load a BMP image
	
	\param fileOrRWops	filename of the BMP image or a RWops object
	\returns Surface	the resulting surface or nil it there was an error.
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.SaveBMP( Surface, fileOrRWops )
--[[	
	Save a surface to BMP image
	
	Surfaces with a 24-bit, 32-bit and paletted 8-bit format get saved in the
	BMP directly. Other RGB formats with 8-bit or higher get converted to a
	24-bit surface or, if they have an alpha mask or a colorkey, to a 32-bit
	surface before they are saved. YUV and paletted 1-bit and 4-bit formats are
	not supported.	

	\param surface 		the Surface object containing the image to be saved
	\param fileOrRWops	a file name or a RWops object
	\returns success	true on success or false on failure;
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.SetRLE( Surface, flag )
--[[
	Set the RLE acceleration hint for a surface.

	If RLE is enabled, color key and alpha blending blits are much faster, but
	the surface must be locked before directly accessing the pixels.

	\param surface 		the Surface object to optimize
	\param flag 		0 to disable, non-zero to enable RLE acceleration
	\returns success	true on success or fales on failure;
						call SDL.Error.Get() for more information.
--]]

rle = SDL.Surface.HasRLE( Surface )
--[[
	Returns whether the surface is RLE enabled

	It is safe to pass a nil here; it will return false.

	\param surface 		the Surface object to query
	\returns success	true if the surface is RLE enabled, false otherwise.
--]]

success = SDL.Surface.SetColorKey( Surface, flag, key )
--[[
	Set the color key (transparent pixel) in a surface.

	The color key defines a pixel value that will be treated as transparent in
	a blit. For example, one can use this to specify that cyan pixels should be
	considered transparent, and therefore not rendered.

	It is a pixel of the format used by the surface, as generated by
	SDL.PixelFormat.MapRGB().

	RLE acceleration can substantially speed up blitting of images with large
	horizontal runs of transparent pixels. See SDL.Surface.SetRLE() for details.

	\param surface 		the Surface object to update
	\param flag 		true to enable color key, false to disable color key
	\param key 			the transparent pixel
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

key = SDL.Surface.GetColorKey( Surface )
--[[
	Get the color key (transparent pixel) for a surface.
	
	The color key is a pixel of the format used by the surface, as generated by
	SDL.PixelFormat.MapRGB().
	
	If the surface doesn't have color key enabled this function returns nil.

	\param surface 		the Surface object to query
	\returns key 		the transparent pixel or nil
--]]

success = SDL.Surface.SetColorMod( Surface, r, g, b )
--[[
	Set an additional color value multiplied into blit operations.

	When this surface is blitted, during the blit operation each source color
	channel is modulated by the appropriate color value according to the
	following formula:

	srcC = srcC * (color / 255)
	
	\param surface 		the Surface object to update
	\param r 			the red color value multiplied into blit operations
	\param g 			the green color value multiplied into blit operations
	\param b 			the blue color value multiplied into blit operations
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

r, g, b = SDL.Surface.GetColorMod( Surface )
--[[
	Get the additional color value multiplied into blit operations.
	
	\param surface 		the Surface object to query
	\returns r 			the red color value multiplied into blit operations or nil
	\returns g 			the green color value multiplied into blit operations or nil
	\returns b 			the blue color value multiplied into blit operations or nil
--]]

success = SDL.Surface.SetAlphaMod( Surface, alpha )
--[[
	Set an additional alpha value used in blit operations.

	When this surface is blitted, during the blit operation the source alpha
	value is modulated by this alpha value according to the following formula:

	`srcA = srcA * (alpha / 255)`

	\param surface 		the Surface object to update
	\param alpha 		the alpha value multiplied into blit operations
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

alpha = SDL.Surface.GetAlphaMod( Surface )
--[[
	Get the additional alpha value used in blit operations.

	\param surface 		the Surface object to query
	\returns alpha 		the alpha value multiplied into blit operations or nil
--]]

success = SDL.Surface.SetBlendMode( Surface, BlendMode )
--[[
	Set the blend mode used for blit operations.

	To copy a surface to another surface (or texture) without blending with the
	existing data, the blendmode of the SOURCE surface should be set to
	"NONE".
	
	\param surface 		the Surface object to update
	\param blendMode 	the BlendMode to use for blit blending
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

BlendMode = SDL.Surface.GetBlendMode( Surface )
--[[
	Get the blend mode used for blit operations.

	\param surface 		the Surface object to query
	\param blendMode 	the current BlendMode or nil
--]]

intersect = SDL.Surface.SetClip( Surface, Rect )
--[[
	Set the clipping rectangle for a surface.

	When `surface` is the destination of a blit, only the area within the clip
	rectangle is drawn into.

	Note that blits are automatically clipped to the edges of the source and
	destination surfaces.

	\param surface 		the Surface object to be clipped
	\param rect 		the Rect table 0representing the clipping rectangle, or
						nil to disable clipping
	\returns intersect	true if the rectangle intersects the surface, otherwise
						false and blits will be completely clipped.
--]]

Rect = SDL.Surface.GetClip( Surface )
--[[
	Get the clipping rectangle for a surface.

	When `surface` is the destination of a blit, only the area within the clip
	rectangle is drawn into.

	\param surface 		the Surface object representing the surface to be clipped
	\param rect 		an Rect table filled in with the clipping rectangle for
						the surface
--]]

Surface = SDL.Surface.Duplicate( Surface )
--[[
	Creates a new surface identical to the existing surface.

	The returned surface should be freed with SDL.Surface.Free().

	\param Surface 		the surface to duplicate.
	\returns Surface 	a copy of the surface, or nil on failure; 
						call SDL.Error.Get() for more information.
--]]

Surface = SDL.Surface.Convert( Surface, format )
--[[
	Copy an existing surface to a new surface of the specified format.

	This function is used to optimize images for faster *repeat* blitting. This
	is accomplished by converting the original and storing the result as a new
	surface. The new, optimized surface can then be used as the source for
	future blits, making them faster.

	\param Surface		the existing Surface object to convert
	\param format 		the PixelFormat object or PixelFormatEnum that the new 
						surface is optimized for
	\returns Surface	the new Surface object that is created or nil if it fails;
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.FillRect ( Surface, Rect, color )
--[[
	Perform a fast fill of a rectangle with a specific color.

	`color` should be a pixel of the format used by the surface, and can be
	generated by SDL.PixelFormat.MapRGB() or SDL.PixelFormat.MapRGBA(). 
	If the color value contains an alpha component then the destination is simply 
	filled with that alpha information, no blending takes place.

	If there is a clip rectangle set on the destination (set via
	SDL.Surface.SetClip()), then this function will fill based on the intersection
	of the clip rectangle and `rect`.

	\param Surface		the Surface object that is the drawing target
	\param rect 		the Rect table representing the rectangle to fill, or
						nil to fill the entire surface
	\param color 		the color to fill with
	\returns success	true on success or false on failure; 
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.Blit( Surface1, Rect, Surface2, Point)
--[[
	Performs a fast blit from the source surface to the destination surface.
	
	The blit function should not be called on a locked surface.

	The blit semantics for surfaces with and without blending and colorkey
	are defined as follows:
	
	RGBA->RGB:
	  Source surface blend mode set to "BLEND":
		alpha-blend (using the source alpha-channel and per-surface alpha)
		SDL_SRCCOLORKEY ignored.
	  Source surface blend mode set to "NONE":
		copy RGB.
		if SRCCOLORKEY set, only copy the pixels matching the
		RGB values of the source color key, ignoring alpha in the comparison.

	RGB->RGBA:
	  Source surface blend mode set to "BLEND":
		alpha-blend (using the source per-surface alpha)
	  Source surface blend mode set to "NONE":
		copy RGB, set destination alpha to source per-surface alpha value.
	  both:
		if SRCCOLORKEY set, only copy the pixels matching the source color key.

	RGBA->RGBA:
	  Source surface blend mode set to "BLEND":
		alpha-blend (using the source alpha-channel and per-surface alpha)
		SDL_SRCCOLORKEY ignored.
	  Source surface blend mode set to "NONE":
		copy all of RGBA to the destination.
		if SRCCOLORKEY set, only copy the pixels matching the
		RGB values of the source color key, ignoring alpha in the comparison.

	RGB->RGB:
	  Source surface blend mode set to "BLEND":
		alpha-blend (using the source per-surface alpha)
	  Source surface blend mode set to "NONE":
		copy RGB.
	  both:
		if SRCCOLORKEY set, only copy the pixels matching the source color key.
	
	\param Surface1		the Surface object to be copied from
	\param Rect 		the Rect table representing the rectangle to be copied, 
						or nil to copy the entire surface
	\param Surface2		the Surface object that is the blit target
	\param Point 		the Point table representing the destination coordinate
						that is copied into
	\returns success 	true on success or false on failure;
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.BlitScaled( Surfac1, Rect1, Surface2, Rect2 )
--[[
	Perform a scaled surface copy to a destination surface.
	
	\param Surface1		the Surface object to be copied from
	\param Rect1 		the Rect table representing the rectangle to be copied, 
						or nil to copy the entire surface
	\param Surface2		the Surface object that is the blit target
	\param Rect2 		the Rect object representing the rectangle that is
						copied into
	\returns success 	true on success or false on failure;
						call SDL.Error.Get() for more information.
--]]

success = SDL.Surface.SoftStretch( Surfac1, Rect1, Surface2, Rect2 )
--[[
	Perform bilinear scaling between two surfaces of the same format, 32BPP.
	
	\param Surface1		the Surface object to be copied from
	\param Rect1 		the Rect table representing the rectangle to be copied, 
						or nil to copy the entire surface
	\param Surface2		the Surface object that is the blit target
	\param Rect2 		the Rect object representing the rectangle that is
						copied into
	\returns success 	true on success or false on failure;
--]]

SDL.Surface.SetYUVConversionMode( mode )
--[[
	Set the YUV conversion mode
	
	\param mode
		"JPEG"		Full range JPEG 
		"BT601"		BT.601 (the default) 
		"BT709"		BT.709
		"AUTOMATIC"	BT.601 for SD content, BT.709 for HD content
--]]

mode = SDL.Surface.GetYUVConversionMode()
--[[
	Get the YUV conversion mode
	
	\returns mode
--]]

mode = SDL.Surface.GetYUVConversionModeForResolution(w, h)
--[[
	Get the YUV conversion mode, returning the correct mode for the resolution
	when the current conversion mode is "AUTOMATIC"

	\param w		width
	\param h 		height
	\returns mode
--]]

-------------------------------------------------------------------------------Time

ticks = SDL.Time.GetTicks()
--[[
	Get the number of milliseconds since SDL library initialization.
	
	\returns ticks	an unsigned 64-bit value representing the number of
					milliseconds since the SDL library initialized.
--]]

count = SDL.Time.GetPerformanceCounter()
--[[
	Get the current value of the high resolution counter.

	This function is typically used for profiling.

	The counter values are only meaningful relative to each other. Differences
	between values can be converted to times by using
	SDL.Time.GetPerformanceFrequency().

	\returns the current counter value.
--]]

frequency  = SDL.Time.GetPerformanceFrequency()
--[[
	Get the count per second of the high resolution counter.
	
	\returns a platform-specific count per second.
--]]

time = SDL.Time.Get()
--[[
	Get the number of seconds since SDL library initialization.
	same as 
	
		SDL.Time.GetPerformanceCounter() / SDL.Time.GetPerformanceFrequency()
--]]

SDL.Time.Delay( ms )
--[[
	Wait a specified number of milliseconds before returning.

	This function waits a specified number of milliseconds before returning. It
	waits at least the specified time, but possibly longer due to OS
	scheduling.

	\param ms 		the number of milliseconds to delay
--]]

------------------------------------------------------------------------------Touch
TouchDeviceType
"INVALID", "DIRECT", "INDIRECT_ABSOLUTE", "INDIRECT_RELATIVE"

count = SDL.Touch.GetNum()
--[[
	Get the number of registered touch devices.

	On some platforms SDL first sees the touch device if it was actually used.
	Therefore SDL.Touch.GetNum() may return 0 although devices are available. 
	After using all devices at least once the number will be correct.

	\returns count	the number of registered touch devices.
--]]

touchID = SDL.Touch.Open( index )
--[[
	Get the touch ID with the given index.

	\param index 		the touch device index
	\returns touchID	the touch ID with the given index on success or nil
--]]

SDL.Touch.Close( touchID )
--[[
	Close a touch device
	
	\param touchID 		the ID of a touch device
--]]

count = SDL.Touch.GetNumFingers( touchID )
--[[

	Get the number of active fingers for a given touch device.

	\param touchID 		the ID of a touch device
	\returns count 		the number of active fingers for a given touch device on 
						success or 0 on failure
--]]

x, y, pressure, id = SDL.Touch.GetFinger( touchID, index )
--[[
	Get the finger object for specified touch device ID and finger index.

	The returned resource is owned by SDL and should not be deallocated.

	\param touchID 		the ID of the requested touch device
	\param index 		the index of the requested finger
	\returns x 			touch data value
	\returns y 			touch data value
	\returns pressure 	touch data value
	\returns id			FingerID (needed for events!)
--]]

----------------------------------------------------------------------------Version
major,minor,patch,num = SDL.Version.Get()
--[[

	Get the version of SDL that is linked against your program.

	This function may be called safely at any time, even before SDL.Init().

	\returns major 	major version
	\returns minor	minor version
	\returns patch	patch version
	\returns num		version numbers into a numeric value: (1,2,3) -> (1203)
--]]

bool = SDL.Version.AtLeast( major, minor, patch )
--[[
	This will evaluate to true if with SDL at least major.minor.patch.

	\param major 	major version
	\param minor	minor version
	\param patch	patch version
	\returns bool	true if with SDL at least major.minor.patch
--]]

------------------------------------------------------------------------------Video
Window:
"NONE", "SHOWN", "HIDDEN", "BORDERLESS", "RESIZABLE", "MINIMIZED", "MAXIMIZED", 
"MOUSE_GRABBED", "INPUT_FOCUS", "MOUSE_FOCUS", "FULLSCREEN_DESKTOP", "FOREIGN", 
"ALLOW_HIGHDPI", "MOUSE_CAPTURE", "ALWAYS_ON_TOP", "SKIP_TASKBAR", "UTILITY", 
"TOOLTIP", "POPUP_MENU", "KEYBOARD_GRABBED", "INPUT_GRABBED", "SHAPED"

WindowFullscreen:
"WINDOW",  "FULLSCREEN_DESKTOP"

WindowPos:
"UNDEFINED", "UNDEFINED_DISPLAY0", "UNDEFINED_DISPLAY1", "UNDEFINED_DISPLAY2", 
"UNDEFINED_DISPLAY3", "UNDEFINED_DISPLAY4", "UNDEFINED_DISPLAY5", 
"UNDEFINED_DISPLAY6", "UNDEFINED_DISPLAY7", "UNDEFINED_DISPLAY8", 
"UNDEFINED_DISPLAY9", "CENTERED", "CENTERED_DISPLAY0", "CENTERED_DISPLAY1", 
"CENTERED_DISPLAY2", "CENTERED_DISPLAY3", "CENTERED_DISPLAY4", "CENTERED_DISPLAY5", 
"CENTERED_DISPLAY6", "CENTERED_DISPLAY7", "CENTERED_DISPLAY8", "CENTERED_DISPLAY9"

WindowEventID:
"SHOWN", "HIDDEN", "EXPOSED", "MOVED", "RESIZED", "SIZE_CHANGED", "MINIMIZED", 
"MAXIMIZED", "RESTORED", "ENTER", "LEAVE", "FOCUS_GAINED", "FOCUS_LOST", "CLOSE", 
"TAKE_FOCUS", "HIT_TEST", "ICCPROF_CHANGED", "DISPLAY_CHANGED", NULL,NULL }

DisplayEventID:
"ORIENTATION", "CONNECTED", "DISCONNECTED"

DisplayOrientation:
"UNKNOWN", "LANDSCAPE", "LANDSCAPE_FLIPPED", "PORTRAIT", "PORTRAIT_FLIPPED"

FlashOperation:
"CANCEL", "BRIEFLY", "UNTIL_FOCUSED"

ShapeMode:
"DEFAULT", "BINARIZE", "REVERSEBINARIZE", "COLOR"

num = SDL.Display.GetNum()
--[[
	Get the number of available video displays.

	\returns num	a number >= 1 on success or a negative error code on failure; 
					call SDL.Error.Get() for more information.
--]]

name = SDL.Display.GetName( index )
--[[
	Get the name of a display in UTF-8 encoding.
	
	\param index 	the index of display from which the name should be queried
	\returns name	the name of a display or nil for an invalid display index or
					failure; call SDL.Error.Get() for more information.
--]]

rect = SDL.Display.GetBounds( index )
--[[
	Get the desktop area represented by a display.

	The primary display (Index zero) is always located at 0,0.
	
	\param index 	the index of display from which the name should be queried
	\returns rect	the Rect table filled in with the display bounds or nil
--]]

rect = SDL.Display.GetUsableBounds( index )
--[[
	Get the usable desktop area represented by a display.

	The primary display (Index zero) is always located at 0,0.
 
	This is the same area as SDL.Display.GetBounds() reports, but with portions
	reserved by the system removed. For example, on Apple's macOS, this
	subtracts the area occupied by the menu bar and dock.

	Setting a window to be fullscreen generally bypasses these unusable areas,
	so these are good guidelines for the maximum space available to a
	non-fullscreen window.

	\param index 	the index of display from which the name should be queried
	\returns rect	the Rect table filled in with the display bounds or nil
--]]

ddpi, hdpi, vdpi = SDL.Display.GetDPI( index )
--[[
	Get the dots/pixels-per-inch for a display.

	A failure of this function usually means that either no DPI information is
	available or the Index is out of range.

	\param index 	the index of display from which the name should be queried
	\returns ddpi 	the diagonal DPI of the display
	\returns hdpi 	the horizontal DPI of the display
	\returns vdpi	the vertical DPI of the display
--]]

orientation = SDL.Display.GetOrientation( index )
--[[
	Get the orientation of a display.
	\param index 	the index of display from which the name should be queried
	\returns orientation
		"UNKNOWN"			The display orientation can't be determined
		"LANDSCAPE"			The display is in landscape mode, with the right side 
							up, relative to portrait mode
		"LANDSCAPE_FLIPPED" The display is in landscape mode, with the left side 
							up, relative to portrait mode
		"PORTRAIT"          The display is in portrait mode
		"PORTRAIT_FLIPPED"	The display is in portrait mode, upside down
--]]

DisplayMode = SDL.Display.GetDesktopMode( index )
--[[
	Get information about the desktop's display mode.
	
	\param index 			the index of display from which the name should be 
							queried
	\returns DisplayMode	a table with this content:
		{
			format,			-- PixelFormatEnum
			w,				-- width, in screen coordinates
			h,				-- height, in screen coordinates
			refresh_rate	-- refresh rate (or zero for unspecified)
		}	
--]]

index = SDL.Window.GetDisplayIndex( window )
--[[
	Get the index of the display associated with a window.

	\param window 		the window object to query
	\returns index		the index of the display containing the center of the 
						window on success or nil; 
--]]

PixelFormat = SDL.Window.GetPixelFormat( window )
--[[
	Get the PixelFormat object of the given window.
	
	\param window 			the window object to query
	\returns PixelFormat	the PixelFormatEnum of the window or nil
--]]

window = SDL.Window.Create(title, x, y, w, h [, flags])
--[[
	Create a window with the specified position, dimensions, and flags.

	"flags" may be any of the following combination together:
 
		"FULLSCREEN_DESKTOP"	fullscreen window at desktop resolution
		"SHOWN"					window is visible (default)
		"HIDDEN"				window is not visible
		"BORDERLESS"			no window decoration
		"RESIZABLE"				window can be resized
		"MINIMIZED"				window is minimized
		"MAXIMIZED"				window is maximized
		"INPUT_GRABBED"			window has grabbed input focus
		"ALLOW_HIGHDPI"			window should be created in high-DPI mode if
								supported
		"ALWAYS_ON_TOP"			window should always be above others
		"SKIP_TASKBAR"			window should not be added to the taskbar
		"UTILITY"				window should be treated as a utility window
		"TOOLTIP"				window should be treated as a tooltip
		"POPUP_MENU"			window should be treated as a popup menu
		"KEYBOARD_GRABBED"		window has grabbed keyboard input
		"SHAPED"				window that can be shaped
		
 
	If the window is created with the "ALLOW_HIGHDPI" flag, its size
	in pixels may differ from its size in screen coordinates on platforms with
	high-DPI support (e.g. iOS and macOS). Use SDL.Window.GetSize() to query the
	client area's size in screen coordinates, and SDL.Render.GetOutputSize() to query the drawable size in pixels.

	If the window is set fullscreen, the width and height parameters "w" and
	"h" will not be used. However, invalid size parameters (e.g. too large) may
	still fail. Window size is actually limited to 16384 x 16384 for all
	platforms at window creation.

	\param title 		the title of the window, in UTF-8 encoding
	\param x 			the x position of the window, "CENTERED" or "UNDEFINED"
	\param y 			the y position of the window, "CENTERED" or "UNDEFINED"
	\param w 			the width of the window, in screen coordinates
	\param h			the height of the window, in screen coordinates
	\param flags 		see above, default "SHOWN"
	\returns window 	the window that was created or nil on failure
--]]

success = SDL.Window.SetShape( window, shape, ShapeMode [,binarization][,color] )
--[[
	Set the shape and parameters of a shaped window.
	
	\param window 		The shaped window whose parameters should be set.
	\param shape 		A surface encoding the desired shape for the window.
	\param ShapeMode	a ShapeMode value
	\param binarization	A cutoff alpha value for binarization
	\param color		a color key
	\returns success	true on success, false on failure
--]]

ShapeMode [,binarization] [,color] = SDL.Window.GetShape( window )
--[[
	Get the shape and parameters of a shaped window.
	
	\param window 			The shaped window whose parameters should be set.
	\returns ShapeMode		a ShapeMode value
	\returns binarization	A cutoff alpha value for binarization
	\returns color			a color key
--]]	
	
flags = SDL.Window.GetFlags( window )
--[[
	Get the window flags.

	\param window 		the window object to query
	\returns flags		WindowFlags associated with window
--]]

SDL.Window.SetTitle( window, title )
--[[
	Set the title of a window.

	This string is expected to be in UTF-8 encoding.

	\param window 		the window to change
	\param title 		the desired window title in UTF-8 format
--]]

title = SDL.Window.GetTitle( window )
--[[
	Get the title of a window.

	\param 				window the window to query
	\returns title		the title of the window in UTF-8 format or "" 
--]]

SDL.Window.SetIcon( window, surface )
--[[
	 Set the icon for a window.

	\param window 		the window to change
	\param icon 		an Surface object containing the icon for the window
--]]

oldvalue = SDL.Window.SetData( window, name, value )
--[[
	Associate an value with a window.
 
	name is case-sensitive.

	\param window 		the window to associate with the pointer
	\param name 		the name of the value
	\param value 		the value
	\returns oldvalue 	the previous value associated with `name`.
--]]

value = SDL.Window.GetData( window, name )
--[[
	Retrieve the value associated with a window.

	\param window 		the window to query
	\param name 		the name of the pointer
	\returns value 		the value associated with `name`
--]]

SDL.Window.SetPosition( window, x, y )
--[[
	Set the position of a window.
 
	The window coordinate origin is the upper left of the display.

	\param window 		the window to reposition
	\param x 			the x coordinate of the window in screen coordinates, or
						"CENTERED" or "UNDEFINED"
	\param y 			the y coordinate of the window in screen coordinates, or
						"CENTERED" or "UNDEFINED"
--]]

x, y = SDL.Window.GetPosition( window )
--[[
	get the position of a window.
 
	\param window 		the window to reposition
	\returns x 			the x coordinate of the window in screen coordinates
	\returns y 			the y coordinate of the window in screen coordinates
--]]

SDL.Window.SetSize( window, w, h )
--[[
	Set the size of a window's client area.

	The window size in screen coordinates may differ from the size in pixels,
	if the window was created with "ALLOW_HIGHDPI" on a platform with high-dpi 
	support (e.g. iOS or macOS). SDL.Render.GetOutputSize() to get the real 
	client area size in pixels.
 
	\param window 		the window to change
	\param w 			the width of the window in pixels, in screen coordinates
	\param h 			the height of the window in pixels, in screen coordinates
--]]

w, h = SDL.Window.GetSize( window )
--[[
	Get the size of a window's client area.

	The window size in screen coordinates may differ from the size in pixels,
	if the window was created with "ALLOW_HIGHDPI" on a platform with high-dpi 
	support (e.g. iOS or macOS). SDL.Render.GetOutputSize() to get the real 
	client area size in pixels.
 
	\param window 		the window to change
	\returns w 			the width of the window in pixels, in screen coordinates
	\returns h 			the height of the window in pixels, in screen coordinates
--]]

top, left, bottom, right = SDL.Window.GetBordersSize( window )
--[[
	Get the size of a window's borders (decorations) around the client area.

	Note: This function may fail on systems where the window has not yet been
	decorated by the display server (for example, immediately after calling
	SDL.Window.Create). It is recommended that you wait at least until the
	window has been presented and composited, so that the window system has a
	chance to decorate the window and provide the border dimensions to SDL.

	\param window 		the window to query the size values of the border
						(decorations) from
	\returns top		the size of the top border
	\returns left 		the size of the left border
	\returns bottom		the size of the bottom border
	\returns right 		the size of the right border
--]]

SDL.Window.SetMinimumSize( window, min_w, min_h )
--[[
	Set the minimum size of a window's client area.

	\param window 		the window to change
	\param min_w 		the minimum width of the window in pixels
	\param min_h		the minimum height of the window in pixels
--]]

min_w, min_h = SDL.Window.GetMinimumSize( window )
--[[
	Get the minimum size of a window's client area.

	\param window 		the window to change
	\returns min_w 		the minimum width of the window in pixels
	\returns min_h		the minimum height of the window in pixels
--]]

SDL.Window.SetMaximumSize( window, max_w, max_h )
--[[
	Set the maximum size of a window's client area.

	\param window 		the window to change
	\param max_w 		the maximum width of the window in pixels
	\param max_h		the maximum height of the window in pixels
--]]

max_w, max_h = SDL.Window.GetMaximumSize( window )
--[[
	Get the maximum size of a window's client area.

	\param window 		the window to change
	\returns max_w 		the maximum width of the window in pixels
	\returns max_h		the maximum height of the window in pixels
--]]

SDL.Window.SetBordered( window, state )
--[[
	Set the border state of a window.

	This will add or remove the window's "BORDERLESS" flag and add
	or remove the border from the actual window. This is a no-op if the
	window's border already matches the requested state.

	\param window 		the window of which to change the border state
	\param state 		false to remove border, true to add border
--]]

SDL.Window.SetResizable( window, state )
--[[
	Set the user-resizable state of a window.

	This will add or remove the window's "RESIZABLE" flag and
	allow/disallow user resizing of the window. This is a no-op if the window's
	resizable state already matches the requested state.
 
	\param window 		the window of which to change the resizable state
	\param state		true to allow resizing, false to disallow
--]]

SDL.Window.SetAlwaysOnTop( window, state )
--[[
	Set the window to always be above the others.

	This will add or remove the window's "ALWAYS_ON_TOP"` flag. This
	will bring the window to the front and keep the window above the rest.

	\param window 		The window of which to change the always on top state
	\param state		true to set the window always on top, false to disable
--]]

SDL.Window.Show( window )
--[[
	Show a window.
 
	\param window 		the window to show
--]]

SDL.Window.Hide( window )
--[[
	Hide a window.
 
	\param window 		the window to hide
--]]

SDL.Window.Raise( window )
--[[
	Raise a window above other windows and set the input focus.

	\param window 		the window to raise
--]]

SDL.Window.Maximize( window )
--[[
	Make a window as large as possible.

	\param window 		the window to maximize
--]]

SDL.Window.Minimize( window )
--[[
	Minimize a window to an iconic representation.

	\param window 		the window to minimize
--]]
	
SDL.Window.Restore( window )
--[[
	Restore the size and position of a minimized or maximized window.
	
	\param window 		the window to restore
--]]

success = SDL.Window.SetFullscreen( window, flags )
--[[
	Set a window's fullscreen state.

	"flags" may be "FULLSCREEN_DESKTOP" for "fake" fullscreen
	that takes the size of the desktop; and "WINDOW" for windowed mode.
 
	\param window 		the window to change
	\param flags 		"FULLSCREEN_DESKTOP" or "WINDOW"
	\returns success	true on success or false on failure; 
--]]

Surface = SDL.Window.GetSurface( window )
--[[
	Get the surface object associated with the window.

	A new surface will be created with the optimal format for the window, if
	necessary. This surface will be freed when the window is destroyed. Do not
	free this surface.

	This surface will be invalidated if the window is resized. After resizing a
	window this function must be called again to return a valid surface.

	You may not combine this with 3D or the rendering API on this window.

	This function is affected by hint "FRAMEBUFFER_ACCELERATION".

	\param window 		the window to query
	\returns Surface	the surface associated with the window, or nil on failure
--]]

success = SDL.Window.UpdateSurface( window )
--[[
	Copy the window surface to the screen.
	
	This is the function you use to reflect any changes to the surface on the 
	screen.

	\param window 		the window to update
	\returns success	true on success or faile on failure; 
--]]

SDL.Window.SetGrab( window, state )
--[[
	Set a window's input grab mode.

	When input is grabbed, the mouse is confined to the window. This function
	will also grab the keyboard if hint "GRAB_KEYBOARD" is set. To grab the
	keyboard without also grabbing the mouse, use SDL.Window.SetKeyboardGrab().

	If the caller enables a grab while another window is currently grabbed, the
	other window loses its grab in favor of the caller's window.

	\param window		the window for which the input grab mode should be set
	\param state 		true to grab input or false to release input
--]]

SDL.Window.SetKeyboardGrab( window, state )
--[[
	Set a window's keyboard grab mode.

	Keyboard grab enables capture of system keyboard shortcuts like Alt+Tab or
	the Meta/Super key. Note that not all system keyboard shortcuts can be
	captured by applications (one example is Ctrl+Alt+Del on Windows).

	This is primarily intended for specialized applications such as VNC clients
	or VM frontends. Normal games should not use keyboard grab.
 
	When keyboard grab is enabled, SDL will continue to handle Alt+Tab when the
	window is full-screen to ensure the user is not trapped in your
	application. If you have a custom keyboard shortcut to exit fullscreen
	mode, you may suppress this behavior with hint "ALLOW_ALT_TAB_WHILE_GRABBED`.
 
	If the caller enables a grab while another window is currently grabbed, the
	other window loses its grab in favor of the caller's window.
 
	\param window 		The window for which the keyboard grab mode should be set.
	\param state		This is true to grab keyboard, and false to release.
--]]

SDL.Window.SetMouseGrab( window, state )
--[[
	Set a window's mouse grab mode.

	Mouse grab confines the mouse cursor to the window.

	\param window 		The window for which the mouse grab mode should be set.
	\param state		This is true to grab mouse, and false to release.
--]]


grab = SDL.Window.GetGrab( window )
--[[
	Get a window's input grab mode.

	\param window 		the window to query
	\returns grab		true if input is grabbed, false otherwise.
--]]

grab = SDL.Window.GetKeyboardGrab( window )
--[[
	Get a window's keyboard grab mode.

	\param window 		the window to query
	\returns grab		true if keyboard is grabbed, false otherwise.
--]]

grab = SDL.Window.GetMouseGrab( window )
--[[
	Get a window's mouse grab mode.

	\param window 		the window to query
	\returns grab		true if mouse is grabbed, false otherwise.
--]]

window = SDL.Window.GetGrabbed()
--[[
	Get the window that currently has an input grab enabled.

	\returns window		the window if input is grabbed or nil otherwise.
--]]

success = SDL.Window.SetMouseRect( window, rect )
--[[
	Confines the cursor to the specified area of a window.

	Note that this does NOT grab the cursor, it only defines the area a cursor
	is restricted to when the window has mouse focus.

	\param window 		The window that will be associated with the barrier.
	\param rect 		A rectangle area in window-relative coordinates. 
						If nil the barrier for the specified window will be 
						destroyed.
	\returns success	true on success or false on failure
--]]

rect = SDL.Window.GetMouseRect( window, rect )
--[[
	Get the mouse confinement rectangle of a window.

	\param window 		The window to query
	\returns rect		the mouse confinement rectangle of a window, 
						or nil if there isn't one.
--]]

success = SDL.Window.SetOpacity( window, opacity )
--[[
	Set the opacity for a window.

	The parameter "opacity"` will be clamped internally between 
	0.0 (transparent) and 1.0 (opaque).

	\param window 		the window which will be made transparent or opaque
	\param opacity 		the opacity value (0.0 - transparent, 1.0 - opaque)
	\returns success	true on success or false on failure
--]]

opacity = SDL.Window.GetOpacity( window )
--[[
	Get the opacity of a window.

	If transparency isn't supported on this platform, opacity will be reported
	as 1.0 without error.

	\param window 		the window to get the current opacity value from
	\return opacity 	0.0 - transparent, 1.0 - opaque
--]]

success = SDL.Window.ModalFor( modal_window, parent_window )
--[[
	Set the window as a modal for another window.

	\param modal_window		the window that should be set modal
	\param parent_window	the parent window for the modal window
	\returns success		true on success or false on failure
--]]

success = SDL.Window.SetInputFocus( window )
--[[
	Explicitly set input focus to the window.

	You almost certainly want SDL.Window.Raise() instead of this function. Use
	this with caution, as you might give focus to a window that is completely
	obscured by other windows.

	\param window 		the window that should get the input focus
	\returns success	true on success or false on failure
--]]

success = SDL.Window.Flash( window, operation )
--[[
	Request a window to demand attention from the user.

	\param window 		the window to be flashed
	\param operation 	the flash operation "CANCEL", "BRIEFLY", "UNTIL_FOCUSED"
	\returns success	true on success or false on failure
--]]
	
SDL.Window.Destroy( window )
--[[
	Destroy a window.

	\param window 		the window to destroy
--]]

bool = SDL.ScreenSaver.IsEnable()
--[[
	Check whether the screensaver is currently enabled.

	The screensaver is disabled by default since.

	The default can also be changed using hint "ALLOW_SCREENSAVER".

	\returns 		true if the screensaver is enabled, false if it is disabled.
--]]

SDL.ScreenSaver.Enabled()
--[[
	Allow the screen to be blanked by a screen saver.
--]]

SDL.ScreenSaver.Disabled()
--[[
	Prevent the screen from being blanked by a screen saver.
--]]
	



	
	
