
function string.trim(str)
	return str:match("^[ \t]*(.-)[ \t]*$")
end

function string.escape(str)
	return (str:gsub("\\","\\\\"):gsub("\a","\\a"):gsub("\b","\\b"):gsub("\f","\\f"):gsub("\n","\\n"):gsub("\r","\\r"):gsub("\t","\\t"):gsub("\v","\\v"):gsub("\0(%d)","\\000%1"):gsub("\0","\\0"):gsub("\"","\\\""))
end

function string.unescape(str)
	local pos,endpos = 1
	while pos do
		pos,endpos = str:find("\\.", pos)
		if pos then				
			local c = str:sub(endpos,endpos)
			if c == "t" then -- tab
				c = "\t"
			elseif c == "a" then -- bell
				c = "\a"
			elseif c == "f" then -- form feed
				c = "\f"
			elseif c == "v" then -- vertical tab
				c = "\v"
			elseif c == "n" then -- new line
				c = "\n"
			elseif c == "r" then -- return
				c = "\r"
			elseif c >= "0" and c <= "9" then  -- character
				-- one or three digits?
				local d = str:byte(endpos + 1)
				if d >= 48 and d <= 57 then
					endpos += 2
				end				
				c = string.char( math.clamp(tonumber( str:sub(pos+1,endpos)) or 0,0,255) )
			elseif c == "x" then -- character hex-code
				endpos += 2 -- to hexa-character will follow
				c = string.char( math.clamp(tonumber("0x".. str:sub(pos+2,endpos)) or 0, 0,255) )			
			elseif c == "b" then -- backspace
				c = "\b"				
			end
			str = str:sub(1,pos - 1) .. c .. str:sub(endpos + 1)
			pos += 1
		end
	end
	return str
end

function string.codes(str, startPos, endPos)
	startPos = startPos or 1
	endPos = math.min(endPos or #str,#str)

	return function (str,pos)
		pos += 1
		if pos <= endPos then 
			return pos, str:byte(pos)
		else
			return nil,nil
		end
	end, str, startPos - 1
end

function math.rotate(value, min, max)
	return ((value - min) % (max - min + 1)) + min
end


function table.compare(t1,t2)
	local loop = {}
	local function _cmp(t1,t2)
		-- both tables?
		if type(t1) != "table" or type(t2) != "table" then
			return false
		end
		
		if getmetatable(t1) != getmetatable(t2) then
			return false
		end
		
		-- loop? 
		if loop[t1] then 
			return loop[t1] == t2
		end		
		loop[t1]=t2
		
		-- check if every key in t1 is present in t2
		for key,value in pairs(t1) do
			if type(value)=="table" then
				if not _cmp(value, t2[key]) then
					return false
				end
			elseif t2[key] != value  then
				return false
			end
		end
		-- check if t2 has additionals keys
		for key,value in pairs(t2) do
			if t1[key] == nil then
				--print(key,"not in t1")
				return false
			end
		end
		return true
	end
	
	return _cmp(t1,t2)
end

function table.copy(t1)
	local loop = {}
	
	
	local function _copy(t1)
		local ret = {}
		setmetatable(ret, getmetatable(t1))
		
		loop[t1]=ret
		for key, value in pairs(t1) do
			if type(value) == "table" then 
				ret[key] = loop[value] or _copy(value)				
			else
				ret[key]=value
			end
		end	
		return ret
	end
	return _copy(t1)
end

function table.debug(t, add, deep)
	local loop = {}
	function _d(t,add,deep)
		add=add or "  "
		deep=deep or 0
		if deep>10 then return end
		if type(t) != "table" then print("not a table!",t) return false end
		loop[t] = true
		
		for k,v in pairs(t) do
			print(add.."Key '"..tostring(k).."' = "..tostring(v))
			if type(v)=="table" then
				if not loop[v] then
					_d(v,add.."  ", deep+1)
				end
			end		
		end
	end
	print( tostring(t) )
	_d(t,add,deep)	
end

