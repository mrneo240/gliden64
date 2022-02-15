# platform specific files
target_os = target_machine.system()
platform_flags = []
osal_sources = []
osal_includes = include_directories('.')

sdl2_dep = dependency('sdl2', native: false)

if target_os == 'linux'
  osal_sources = [ 'osal_files_unix.c', 'osal_keys_sdl.c' ]
  platform_flags += [ '-DOS_LINUX', '-DNDEBUG' ]
elif target_os == 'darwin'
  osal_sources = [ 'osal_files_unix.c', 'osal_keys_sdl.c' ]
  platform_flags += [ '-DNDEBUG' ]
elif target_os == 'windows'
  osal_sources = ['osal_files_win32.c', 'osal_keys_win.c']
else
  error( message: 'Unsupported platform: ', target_os )
endif

if get_option('buildtype') == 'debug'
  osal_lib = static_library('osald', osal_sources, dependencies : sdl2_dep)
else
  osal_lib = static_library('osal', osal_sources, dependencies : sdl2_dep)
endif

libosal_dep = declare_dependency(include_directories : osal_includes, link_with : osal_lib)
