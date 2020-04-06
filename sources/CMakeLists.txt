add_library(drivers STATIC
    valve.c
    valve_console.c
)
set_target_properties(drivers PROPERTIES
    C_STANDARD 11
)
target_compile_options(drivers PRIVATE
    -pedantic
    -Wall
    -Wextra
    -ansi
)
