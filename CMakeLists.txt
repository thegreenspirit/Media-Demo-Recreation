# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(MediaDemoRecreation)
set(MOD_NAME MediaDemoRecreation CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "MediaDemoRecreation" CACHE STRING "The name of the built library")

add_library(MediaDemoRecreation SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Objects/Global/ActClear.c
    ${MOD_NAME}/Objects/Global/GameOver.c
    ${MOD_NAME}/Objects/Global/ItemBox.c
    ${MOD_NAME}/Objects/Global/PauseMenu.c
    ${MOD_NAME}/Objects/Global/Player.c
    ${MOD_NAME}/Objects/Global/StarPost.c
    ${MOD_NAME}/Objects/Menu/UIButton.c
    ${MOD_NAME}/Objects/Menu/UIPicture.c
    ${MOD_NAME}/Objects/Title/TitleSetup.c
)

target_include_directories(MediaDemoRecreation PRIVATE
    ${MOD_NAME}/
    ${MOD_NAME}/Objects/
    GameAPI/C/
)

set_target_properties(MediaDemoRecreation PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
target_compile_definitions(MediaDemoRecreation PRIVATE RETRO_REVISION=${RETRO_REVISION})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)