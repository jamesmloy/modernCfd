
macro(add_blaze TARGET_NAME)
    target_include_directories(${TARGET_NAME} PRIVATE ${CFD_HOME}/../blaze)
endmacro()