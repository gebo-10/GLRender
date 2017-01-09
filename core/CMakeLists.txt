include_directories(${PROJECT_SOURCE_DIR}/core/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/core/src CORE_SRC)
add_library(core  ${CORE_SRC}) #SHARED
set_target_properties(${GLRender} PROPERTIES FOLDER "test") 
