project(
    'dbus_server',
    'cpp',
    version : '1.0.0',
    meson_version: '>=0.58.0',
    default_options: ['warning_level=3', 'c_std=gnu11', 'cpp_std=gnu++17', 'optimization=g'],
)

# flags required by Evbox coding standard
project_flags = [
    '-Walloc-zero',
    '-Walloca',
    '-Wbad-function-cast',
    '-Wcast-align',
    '-Wcast-qual',
    '-Wconversion',
    '-Wdouble-promotion',
    '-Wduplicated-branches',
    '-Wduplicated-cond',
    '-Wfloat-equal',
    '-Wimplicit-fallthrough=4',
    '-Wjump-misses-init',
    '-Wlogical-op',
    '-Wmissing-include-dirs',
    '-Wmissing-prototypes',
    '-Wnested-externs',
    '-Wnull-dereference',
    '-Wpacked',
    '-Wredundant-decls',
    '-Wshadow',
    '-Wstack-protector',
    '-Wstringop-truncation',
    '-Wswitch-default',
    '-Wswitch-enum',
    '-Wswitch',
    '-Wuninitialized',
    '-Wunsafe-loop-optimizations',
    '-Wunsuffixed-float-constants',
    '-Wunused-local-typedefs',
    '-Wunused-macros',
    '-Wwrite-strings',
    '-ggdb3'
]

# project specific flags
project_flags += [
    # SDBUS libraries expose virtual destructors
    '-Wno-non-virtual-dtor',
]

cxx = meson.get_compiler('cpp')

add_project_arguments(cxx.get_supported_arguments(project_flags), language : 'cpp')

version_arr = meson.project_version().split('.')
version_major = version_arr[0]
version_minor = version_arr[1]

if version_arr.length() > 2
    version_patch = version_arr[2].to_int()
else
    version_patch = 0
endif

vcs_version_string = meson.project_version()
message('Real version: ' + vcs_version_string)

# capture git version data
# for a way to access see include/utils/version.h
vcs_version_conf = configuration_data()
vcs_version_conf.set_quoted('VCS_TAG', vcs_version_string)
vcs_version_conf.set('VCS_TAG_MAJOR', version_major)
vcs_version_conf.set('VCS_TAG_MINOR', version_minor)
vcs_version_conf.set('VCS_TAG_PATCH', version_patch)

version_file = configure_file(output: 'vcs_version.hpp', configuration: vcs_version_conf)
version_inc_dir = include_directories('.')

# autogenerate DBus interface
subdir('introspection')

# project include files are stored in separate folder structure
subdir('include')

# source files go here
subdir('src')

install_subdir('introspection',  install_dir: '/usr/share/dbus-1/interfaces/', exclude_files: ['meson.build'] + introspection_headers, strip_directory : true)
