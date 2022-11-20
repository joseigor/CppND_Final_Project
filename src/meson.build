#
#Copyright(C) EVBox Intelligence B.V.
#

executable_name = meson.project_name()

libspdlog_dep = dependency('spdlog', method: 'pkg-config', required: true)
libsdbuscpp_dep = dependency('sdbus-c++', method: 'pkg-config', required: true)

dependencies = [libspdlog_dep, libsdbuscpp_dep]

src_files = [
]

subdir('dbus')
subdir('util')

executable(executable_name,
    sources:[ 'dbus_server.cpp',src_files],
    include_directories : [include_dirs, version_inc_dir, introspection_inc_dir],
    dependencies: dependencies,
    install: true)
