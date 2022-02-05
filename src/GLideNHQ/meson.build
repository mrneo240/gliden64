# BROKEN BROKEN BROKEN
project('GLideNHQ', default_options : ['default_library=static'])
glidenhq_sources = ['TextureFilters.cpp', 'TextureFilters_2xsai.cpp', 'TextureFilters_hq2x.cpp', 'TextureFilters_hq4x.cpp', 'TextureFilters_xbrz.cpp', 'TxCache.cpp', 'TxDbg.cpp', 'TxFilter.cpp', 'TxFilterExport.cpp', 'TxHiResLoader.cpp', 'TxHiResCache.cpp', 'TxHiResNoCache.cpp', 'TxImage.cpp', 'TxQuantize.cpp', 'TxReSample.cpp', 'TxTexCache.cpp', 'TxUtil.cpp']
if 'MINGW', 'OR', 'PANDORA', 'OR', 'BCMHOST'
  # include_directories([cmake_current_source_dir, '/../osal'])
else
  # include_directories(['inc', cmake_current_source_dir, '/../osal'])
endif
# link_directories([cmake_current_source_dir, '/lib'])
if 'UNIX'
  if cmake_system_name, 'MATCHES', 'Darwin'
    # add_definitions('-DOS_MAC_OS_X')
    apple = 'ON'
  elif cmake_system_name, 'MATCHES', 'Linux'
    # add_definitions(['-DNDEBUG', '-DOS_LINUX'])
  endif
endif
if 'WIN32'
  # link_directories([cmake_current_source_dir, '/lib'])
  # add_definitions(['-DWIN32', '-DOS_WINDOWS', '-D_CRT_SECURE_NO_WARNINGS'])
endif
# Build type
if 'GLIDEN64_BUILD_TYPE', 'STREQUAL', 'Debug'
  debug_build = 'TRUE'
  # add_definitions('-DDEBUG')
endif
if '${CMAKE_CXX_COMPILER_ID}', 'STREQUAL', 'MSVC'
  # add_definitions('-D__MSC__')
endif
if '${CMAKE_CXX_COMPILER_ID}', 'STREQUAL', 'GNU', 'OR', '${CMAKE_CXX_COMPILER_ID}', 'STREQUAL', 'Clang'
  gcc_cpp11_compile_flags = '-std=c++0x -Wno-unused-result'
  if 'NOT', 'MINGW'
    pic_flags = '-fPIC'
  endif
  cmake_cxx_flags = '${CMAKE_CXX_FLAGS} ${GCC_CPP11_COMPILE_FLAGS} -static ${PIC_FLAGS} '
  cmake_c_flags = '${CMAKE_C_FLAGS} -static ${PIC_FLAGS} '
  #SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_CPP11_COMPILE_FLAGS} " )
endif
# add_definitions('-DTXFILTER_LIB')
if 'GLIDEN64_BUILD_TYPE', 'STREQUAL', 'Debug'
  build_variant = 'debug'
else
  build_variant = 'release'
endif
if 'GLIDEN64_BUILD_TYPE', 'STREQUAL', 'Debug'
  GLideNHQd_lib = static_library('GLideNHQd', glidenhq_sources)
  # set_target_properties(['GLideNHQd', 'PROPERTIES', 'COMPILE_FLAGS', '-m32', 'LINK_FLAGS', '-m32'])
  # set_target_properties(['GLideNHQd', 'PROPERTIES', 'LINK_SEARCH_START_STATIC', '1'])
  # set_target_properties(['GLideNHQd', 'PROPERTIES', 'LINK_SEARCH_END_STATIC', '1'])
  if 'MINGW', 'OR', 'BCMHOST', 'OR', 'APPLE', 'OR', 'USE_SYSTEM_LIBS'
    ZLIB_dep = dependency('ZLIB')
    PNG_dep = dependency('PNG')
    # target_link_libraries(['GLideNHQd', png_libraries, zlib_libraries, 'osald'])
  elif 'ANDROID'
    # target_link_libraries(['GLideNHQ', 'PRIVATE', android_lib_path, '/libs/${BUILD_VARIANT}/${ANDROID_ABI}/libpng.a', 'z', 'dl', 'osal'])
  else
    # target_link_libraries(['GLideNHQd', 'PRIVATE', cmake_current_source_dir, '/lib/libpng.a', cmake_current_source_dir, '/lib/libz.a', 'dl', 'osald'])
  endif
else
  GLideNHQ_lib = static_library('GLideNHQ', glidenhq_sources)
  # set_target_properties(['GLideNHQ', 'PROPERTIES', 'COMPILE_FLAGS', '-m32', 'LINK_FLAGS', '-m32'])
  #  set_target_properties(GLideNHQ PROPERTIES LINK_SEARCH_START_STATIC 1)
  #  set_target_properties(GLideNHQ PROPERTIES LINK_SEARCH_END_STATIC 1)
  #  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  #  find_library(PNGLIB libpng.a)
  if 'PANDORA'
    # target_link_libraries(['GLideNHQ', 'PRIVATE', '/mnt/utmp/codeblocks/usr/lib/libpng.a', '/mnt/utmp/codeblocks/usr/lib/libz.a', 'osal'])
  elif 'BCMHOST', 'OR', 'MINGW', 'OR', 'APPLE', 'OR', 'USE_SYSTEM_LIBS'
    ZLIB_dep = dependency('ZLIB')
    PNG_dep = dependency('PNG')
    # target_link_libraries(['GLideNHQ', png_libraries, zlib_libraries, 'osal'])
  elif 'ANDROID'
    # target_link_libraries(['GLideNHQ', 'PRIVATE', android_lib_path, '/libs/${BUILD_VARIANT}/${ANDROID_ABI}/libpng.a', 'z', 'dl', 'osal'])
  else
    # target_link_libraries(['GLideNHQ', 'PRIVATE', cmake_current_source_dir, '/lib/libpng.a', cmake_current_source_dir, '/lib/libz.a', 'dl', 'osal'])
  endif
endif
