set(srcs
    "font12x16.c"
    "font14x30.c"
    "font16x32.c"
    "font25x57.c"
    "font5x8.c"
    "font9x16.c"
    "fonts.c")

set(includes 
    ".")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS ${includes})

