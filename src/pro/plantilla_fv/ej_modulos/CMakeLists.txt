#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EstadoMenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MotorGrafico.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Personaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EstadoTienda.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EstadoControles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Personaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EstadoJugando.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/HUD.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bala.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Colisiones.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Portal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EstadoWinLose.cpp"
)

#Y donde se encuentran los .h 
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
"${CMAKE_CURRENT_SOURCE_DIR}/State.h"
)  

 