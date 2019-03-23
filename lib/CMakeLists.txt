add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(util)

set_target_properties(glfw PROPERTIES FOLDER lib)
set_target_properties(glad PROPERTIES FOLDER lib)
set_target_properties(util PROPERTIES FOLDER lib)
