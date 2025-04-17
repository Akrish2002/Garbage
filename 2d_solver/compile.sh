#!/bin/bash

# Source folders
io="src/io"
grid="src/grid"
malloc="src/malloc"
scheme="src/scheme"
variables="src/variables"
interpolation="src/scheme/interpolation"
debugger="src/debugger"

eigen="src/third_party/eigen-3.4.0"

# Source files
main="main.cpp"
io_read_cpp="$io/read.cpp"
io_write_cpp="$io/write.cpp"
malloc_allocate_cpp="$malloc/allocate.cpp"
grid_grid_cpp="$grid/grid.cpp"
grid_metrics_cpp="$grid/metrics.cpp"
variables_consVar_cpp="$variables/consVar.cpp"
variables_primitiveVar_cpp="$variables/primitiveVar.cpp"
variables_conversion_cpp="$variables/conversion.cpp"
scheme_interpolation_MUSCL_cpp="$scheme/interpolation/MUSCL.cpp"
scheme_interpolation_fluxlimiter_cpp="$scheme/interpolation/fluxlimiter.cpp"
debugger_debug_cpp="$debugger/debug.cpp"

eigen_cpp="$eigen"

# Executable name
exec_name="cfd_test"

# Optional compiler flags from command line
compile_line="${1:-}"

echo "Compiling .."

# Compile command
g++ -I $eigen -I $interpolation -I $variables -I $scheme -I $malloc -I $io -I $grid -I $debugger $compile_line \
    -o $exec_name \
    $main \
    $io_read_cpp \
    $io_write_cpp \
    $malloc_allocate_cpp \
    $grid_grid_cpp \
    $grid_metrics_cpp \
    $variables_consVar_cpp \
    $variables_primitiveVar_cpp \
    $variables_conversion_cpp \
    $scheme_interpolation_MUSCL_cpp \
    $scheme_interpolation_fluxlimiter_cpp \
    $debugger_debug_cpp \

echo "Compiled successfully!"
