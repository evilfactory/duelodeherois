local c_files = os.matchfiles("**.c")

local builds = {}
local configs = {}
for k, v in pairs(c_files) do
   local filename, extension = v:match("^.+/(.+)%.(.+)$")
   filename = v:gsub("/", "_")
   table.insert(builds, filename)
   table.insert(configs, {name = filename, file = v})
end

workspace "DueloDeHerois"
   configurations(builds)
   architecture "x86_64"

project "DueloDeHerois"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   for k, v in pairs(configs) do
      filter("configurations:" .. v.name)
      files { v.file }
      defines { "DEBUG" }
      symbols "On"
   end