project(turn_geoapi)

set(SOURCE_FILES
        ns_geo_api.cpp
	shared/geoip.cpp
	shared/lgr.cpp
    )

set(HEADER_FILES
	ns_geo_api.h
	shared/geoip.hpp
	shared/lgr.hpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

# Install head files
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PUBLIC_HEADER "${HEADER_FILES}"  # Install head files
    VERSION ${VERSION}
    )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

INSTALL(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Development
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/turn/geoapi
		COMPONENT Development
    INCLUDES DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/turn
        ${CMAKE_INSTALL_INCLUDEDIR}/turn/client
                ${CMAKE_INSTALL_INCLUDEDIR}/turn/geoapi
        COMPONENT Development
    )

export(TARGETS ${PROJECT_NAME}
    NAMESPACE coturn::
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    )

# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
    NAMESPACE coturn::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/coturn"
        COMPONENT Development
    )

# Install cmake version configure file
if(DEFINED VERSION)
    write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${VERSION}
        COMPATIBILITY AnyNewerVersion)
    install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/coturn"
		    COMPONENT Development)
endif()
