cmake_minimum_required(VERSION 3.10)

project(    
        meine_DB_Anwendung
        LANGUAGES CXX 
        DESCRIPTION "Objektorientierte Programmierung in C++"
        HOMEPAGE_URL "http://vorlesung.nabla-b.engineering"
)

add_executable( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc" )