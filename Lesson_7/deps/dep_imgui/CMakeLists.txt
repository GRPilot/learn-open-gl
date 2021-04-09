
set(incs
    ./imconfig.h
    ./imgui_internal.h
    ./imgui.h
    ./imgui_impl_glfw.h
    ./imgui_impl_opengl3.h
    ./imstb_rectpack.h
    ./imstb_textedit.h
    ./imstb_truetype.h
)
set(srcs
    ./imgui_demo.cpp
    ./imgui_draw.cpp
    ./imgui_tables.cpp
    ./imgui_widgets.cpp
    ./imgui.cpp
    ./imgui_impl_glfw.cpp
    ./imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${incs} ${srcs})
