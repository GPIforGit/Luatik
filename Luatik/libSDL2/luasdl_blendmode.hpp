#pragma once

static int l_BlendMode_ComposeCustom(lua_State* L) {
	SDL_BlendFactor srcColorFactor = checkBlendFactor(L, 1);
	SDL_BlendFactor dstColorFactor = checkBlendFactor(L, 2);
	SDL_BlendOperation colorOperation = checkBlendOperation(L, 3);
	SDL_BlendFactor srcAlphaFactor = checkBlendFactor(L, 4);
	SDL_BlendFactor dstAlphaFactor = checkBlendFactor(L, 5);
	SDL_BlendOperation alphaOperation = checkBlendOperation(L, 6);
	SDL_BlendMode ret = (SDL_BlendMode)SDL_ComposeCustomBlendMode(srcColorFactor, dstColorFactor, colorOperation, srcAlphaFactor, dstAlphaFactor, alphaOperation);
	if (ret == SDL_BLENDMODE_INVALID) {
		lua_pushnil(L);
	}
	else {
		pushBlendMode(L, ret);
	}
	return 1;
}

