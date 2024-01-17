add_rules("mode.debug", "mode.release")

target("int2048")
  set_kind("static")
  add_includedirs("$(projectdir)/include")
  add_files("src/int2048.cpp")
  set_optimize("fastest")