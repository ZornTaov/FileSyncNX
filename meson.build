project('FileSyncNX', ['c', 'cpp'],
    version: '1.0.0',
    default_options: [ 'buildtype=release', 'strip=true', 'b_ndebug=if-release', 'cpp_std=c++17' ],
)

add_global_arguments('-DWINDOW_NAME="FileSyncNX"', language : 'cpp')
add_project_link_arguments(['-lstdc++fs'], language : 'cpp')
subdir('borealis/library')

FileSyncNX_files = files(
    'src/FSNXapp.cpp'
)

FileSyncNX = executable(
    'FileSyncNX',
    [ FileSyncNX_files, borealis_files ],
    dependencies : borealis_dependencies,
    install: true,
    include_directories: [ borealis_include, include_directories('include')],
    cpp_args: [ '-g', '-O2', '-DBOREALIS_RESOURCES="./resources/"' ]
)
