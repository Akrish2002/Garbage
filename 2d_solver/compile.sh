#!/bin/bash

# Source folders
debugger="src/debugger"
grid="src/grid"
io="src/io"
malloc="src/malloc"
scheme="src/scheme"
interpolation="src/scheme/interpolation"
solver="src/solver"
eigen="src/third_party/eigen-3.4.0"
variables="src/variables"


# Source files
main="main.cpp"

debugger_debug_cpp="$debugger/debug.cpp"

grid_grid_cpp="$grid/grid.cpp"
grid_metrics_cpp="$grid/metrics.cpp"

io_read_cpp="$io/read.cpp"
io_write_cpp="$io/write.cpp"

malloc_allocate_cpp="$malloc/allocate.cpp"

scheme_roe_cpp="$scheme/roe.cpp"
scheme_interpolation_MUSCL_cpp="$scheme/interpolation/MUSCL.cpp"
scheme_interpolation_fluxlimiter_cpp="$scheme/interpolation/fluxlimiter.cpp"

solver_solver_cpp="$solver/solver.cpp"

eigen_cpp="$eigen"

variables_consVar_cpp="$variables/consVar.cpp"
variables_primitiveVar_cpp="$variables/primitiveVar.cpp"
variables_fluxVar_cpp="$variables/fluxVar.cpp"
variables_utils_cpp="$variables/utils.cpp"


# Executable name
exec_name="cfd_test"


# Optional compiler flags from command line
compile_line="${1:-}"

echo "Compiling .."

# Compile command
g++ -I $solver -I $eigen -I $interpolation -I $variables -I $scheme -I $malloc -I $io -I $grid -I $debugger $compile_line \
    -o $exec_name                           \
    $main                                   \
                                            \
    $debugger_debug_cpp                     \
                                            \
    $grid_grid_cpp                          \
    $grid_metrics_cpp                       \
                                            \
    $io_read_cpp                            \
    $io_write_cpp                           \
                                            \
    $malloc_allocate_cpp                    \
                                            \
    $scheme_interpolation_MUSCL_cpp         \
    $scheme_interpolation_fluxlimiter_cpp   \
    $scheme_roe_cpp                         \
                                            \
    $solver_solver_cpp                      \
                                            \
    $variables_consVar_cpp                  \
    $variables_primitiveVar_cpp             \
    $variables_fluxVar_cpp                  \
    $variables_utils_cpp                    \

echo "Compiled successfully!"
