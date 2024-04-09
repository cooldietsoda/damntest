project("DamnTestVerify")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions -fno-unwind-tables -fno-rtti)
target_link_libraries(${PROJECT_NAME} PRIVATE DamnTest)