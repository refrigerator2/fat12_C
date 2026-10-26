#
# DANTE :: System Automatycznych Testów Jednostkowych oraz Akceptacyjnych
# Tomasz Jaworski, 2018-2020
#
# Plik wygenerowany automatycznie
# Znacznik czasowy: 2026-10-26 11:06:45.391718
#

cmake_minimum_required(VERSION 3.17)
project(project1 C)

# Przyjmij standard C11
set(CMAKE_C_STANDARD 11)

# Ustaw opcje kompilatora (z raportu Dante)
add_compile_options(
      "-Werror=vla"
      "-fdiagnostics-color"
      "-Wall"
      "-std=c11"
      "-DINSIDE_DANTE"
      "-D_ANSI_OUTPUT"
      "-Wextra"
      "-ggdb3"
      "-xc"
      "-fmax-errors=5"
      "-Wno-error=unused-parameter"
      "-Wno-error=implicit-fallthrough"
      "-Wno-error=parentheses"
      "-Wno-parentheses"
      "-D_GNU_SOURCE"
      "-pedantic"
      "-Werror"

)

# Ustaw opcje konsolidatora (z raportu Dante)
add_link_options(
        "-Wl,-wrap,main"
        "-Wl,-cref"
        "-Wl,-Map=main.map"
        "-ggdb3"
)

# Utwórz target 'project1' i dodaj do niego pliki źródlowe:
add_executable(project1
        "file_reader.c"
        "main.c"
        "unit_helper_v2.c"
        "unit_test_v2.c"
        "rdebug.c"
)

# Dołącz niezbędne biblioteki
target_link_libraries(project1
        "m"
)