
fs = import('fs')

xml_files = [
#    file name,                      adaptor,
    ['com.cppnd.calculator.xml',            'IComCppndCalculator.hpp'],
]

introspection_headers = []

foreach tuple: xml_files
    run_command(find_program('sdbus-c++-xml2cpp'), '--adaptor=' + tuple[1], tuple[0], check: true)
    assert(fs.exists(tuple[1]), 'File ' + tuple[1] + ' was not generated!')
    introspection_headers += tuple[1]
endforeach

introspection_inc_dir = include_directories('.')
