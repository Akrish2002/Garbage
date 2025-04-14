#!/bin/bash

# Source folders
io="src/io"
grid="src/grid"
malloc="src/malloc"
scheme="src/scheme"
variables="src/scheme/variables"
interpolation="src/scheme/interpolation"
debugger="src/debugger"

# Source files
main="main.cpp"
io_read_cpp="$io/read.cpp"
io_write_cpp="$io/write.cpp"
malloc_allocate_cpp="$malloc/allocate.cpp"
grid_grid_cpp="$grid/grid.cpp"
grid_metrics_cpp="$grid/metrics.cpp"
scheme_variables_consVar_cpp="$scheme/variables/consVar.cpp"
scheme_interpolation_MUSCL_cpp="$scheme/interpolation/MUSCL.cpp"
scheme_interpolation_fluxlimiter_cpp="$scheme/interpolation/fluxlimiter.cpp"
debugger_debug_cpp="$debugger/debug.cpp"

# Executable name
exec_name="cfd_test"

# Optional compiler flags from command line
compile_line="${1:-}"

echo "Compiling .."

# Compile command
g++ -I $interpolation -I $variables -I $scheme -I $malloc -I $io -I $grid -I $debugger $compile_line \
    -o $exec_name \
    $main \
    $io_read_cpp \
    $io_write_cpp \
    $malloc_allocate_cpp \
    $grid_grid_cpp \
    $grid_metrics_cpp \
    $scheme_interpolation_MUSCL_cpp \
    $scheme_interpolation_fluxlimiter_cpp \
    $scheme_variables_consVar_cpp \
    $debugger_debug_cpp

echo "Compiled successfully!"
