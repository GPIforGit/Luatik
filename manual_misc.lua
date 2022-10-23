--[[

Misc-Library

--]]

table = split( list, sep )
--[[
	Split a string into a table of elements delimited by the given separator.
	
	the seperator is alway one char, but sep can contain more chars. 
	
	for example 
	
		split("as,123;756-uio", ",;-") 
		
	will result in 
	
		{"as", "123", "756", "uio"}
	
	/param list			a string
	/param sep			a string that contains all possible seperators
						default is " ;|," 
	/returns table		return the splitted table
--]]
	
count = is( list, search, sep )
--[[
	count how many "words" from search are in list.

	/param list			a string contains all list words
	/param search		a string contains all search words
	/param sep 			a string that contains all possible seperators
						default is " ;|," 
	/returns count		how often a search word can be found in list
--]]

x = mid(v1, v2 ,v3)
--[[
	return the middle value of the three
	
	/param v1,v2,v3		any compareable value
	/returns x			the value in the middle
--]]