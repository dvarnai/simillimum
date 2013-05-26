helloworld = {}
helloworld.__index = helloworld

function helloworld.info()
   local plugin = {
  	 name = "[LUA] Hello World",
  	 author = "Zephyrus",
  	 description = "Hello World in LUA!",
  	 version = "1.0",
  	 url = "http://simillimum.net"
	}

   setmetatable(plugin, helloworld)
   return plugin
end

function helloworld:plugin_start()
	print("Hello World from [LUA] Hello World!")
end

function helloworld:plugin_end()
	print("Bye bye :(")
end

function helloworld:all_plugins_loaded()
	print("All plugins loaded")
end

function helloworld:map_start()
	print("Map started")
end