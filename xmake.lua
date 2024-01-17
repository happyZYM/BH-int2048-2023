add_rules("mode.debug", "mode.release")

target("int2048")
  set_kind("static")
  add_includedirs("$(projectdir)/include")
  add_files("src/int2048.cpp")
  set_optimize("fastest")

target("test-core")
  set_kind("binary")
  set_targetdir("$(buildir)")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/test-core.cpp")
  add_deps("int2048")

target("C1T1")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer1/1.cpp")
  add_deps("int2048")

target("C1T2")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer1/2.cpp")
  add_deps("int2048")

target("C1T3")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer1/3.cpp")
  add_deps("int2048")

target("C1T4")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer1/4.cpp")
  add_deps("int2048")

target("C1T5")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer1/5.cpp")
  add_deps("int2048")

target("C2T1")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer2/1.cpp")
  add_deps("int2048")

target("C2T2")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer2/2.cpp")
  add_deps("int2048")

target("C2T3")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_includedirs("$(projectdir)/test/deps")
  add_files("test/data/Integer2/3.cpp")
  add_deps("int2048")

target("C2T4")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_files("test/data/Integer2/4.cpp")
  add_deps("int2048")

target("C2T5")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_files("test/data/Integer2/5.cpp")
  add_deps("int2048")

target("C2T6")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_files("test/data/Integer2/6.cpp")
  add_deps("int2048")

target("C2T7")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_files("test/data/Integer2/7.cpp")
  add_deps("int2048")

target("C2T8")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")
  add_files("test/data/Integer2/8.cpp")
  add_deps("int2048")

target("C2T9")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/9.cpp")
  add_deps("int2048")

target("C2T10")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/10.cpp")
  add_deps("int2048")

target("C2T11")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/11.cpp")
  add_deps("int2048")

target("C2T12")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/12.cpp")
  add_deps("int2048")

target("C2T13")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/13.cpp")
  add_deps("int2048")

target("C2T14")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/14.cpp")
  add_deps("int2048")

target("C2T15")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/15.cpp")
  add_deps("int2048")

target("C2T16")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/16.cpp")
  add_deps("int2048")

target("C2T17")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include") 
  add_files("test/data/Integer2/17.cpp")
  add_deps("int2048")

target("C2T18")
  set_kind("binary")
  set_targetdir("$(buildir)/testcase")
  add_includedirs("$(projectdir)/include")  
  add_files("test/data/Integer2/18.cpp")
  add_deps("int2048")
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

