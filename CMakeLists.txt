cmake_minimum_required(VERSION 3.9)

# list the header files
set(HEADER_FILES
	include/Viewer.h
	
	include/Renderer3D/SceneNavigation.h
	include/Renderer3D/EditorCamera.h
	include/Renderer3D/Input.h
	include/Renderer3D/Scene.h
	include/Renderer3D/Selection.h
	include/Renderer3D/States.h
	include/Renderer3D/Transform.h
	include/Renderer3D/WidgetGL3D.h
	include/Renderer3D/Sky.h
	
	include/Renderer3D/Geomtry/Cube.h
	include/Renderer3D/Geomtry/GeomtryGeneration.h
	include/Renderer3D/Geomtry/Grid.h
	include/Renderer3D/Geomtry/Plane.h
	include/Renderer3D/Geomtry/Shape.h
	include/Renderer3D/Geomtry/Sphere.h
	include/Renderer3D/Geomtry/ModelOBJ.h
	
	
	include/Renderer3D/Manipulator/Manipulater.h
	include/Renderer3D/Manipulator/TranslationGizmo.h
	include/Renderer3D/Manipulator/ScalingGizmo.h
	
	include/Renderer3D/Material/Material.h
	include/Renderer3D/Material/Shader.h
	include/Renderer3D/Material/Texture2D.h
	
)

# list the source files
set(SOURCE_FILES
	src/main.cpp
	src/Viewer.cpp

	src/Renderer3D/SceneNavigation.cpp
	src/Renderer3D/EditorCamera.cpp
	src/Renderer3D/Input.cpp
	src/Renderer3D/Scene.cpp
	src/Renderer3D/Selection.cpp
	src/Renderer3D/States.cpp
	src/Renderer3D/WidgetGL3D.cpp
	src/Renderer3D/Sky.cpp
	
	src/Renderer3D/Geomtry/Cube.cpp
	src/Renderer3D/Geomtry/GeomtryGeneration.cpp
	src/Renderer3D/Geomtry/Grid.cpp
	src/Renderer3D/Geomtry/Plane.cpp
	src/Renderer3D/Geomtry/Sphere.cpp
	src/Renderer3D/Geomtry/ModelOBJ.cpp
	

	src/Renderer3D/Manipulator/Manipulater.cpp
	src/Renderer3D/Manipulator/TranslationGizmo.cpp
	src/Renderer3D/Manipulator/ScalingGizmo.cpp
	
	src/Renderer3D/Material/Material.cpp
	src/Renderer3D/Material/Shader.cpp
	src/Renderer3D/Material/Texture2D.cpp
)

# link with qt5
find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)
qt5_wrap_cpp(HEADER_MOC ${HEADER_FILES})

# add library target
add_executable(Editor
	${HEADER_FILES}
	${SOURCE_FILES}
	${HEADER_MOC}
	${RCC_SOURCES}
)

# clang format
add_custom_target(Editor-format)
foreach(CODE_FILE ${HEADER_FILES} ${SOURCE_FILES})
	add_custom_command(TARGET Editor-format
		PRE_BUILD
		COMMAND ${CLANG_FORMAT} -style=file -i ${CODE_FILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Formatting ${CODE_FILE} with ${CLANG_FORMAT}..."
	)
endforeach(CODE_FILE)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UI_FILES})

set(QT_LIBS
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
	Qt5::Widgets
)

target_link_libraries(Editor
	PUBLIC
		${QT_LIBS}
		opengl32
		glew32
)


add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
		$<TARGET_FILE:Qt5::Core>
		$<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:Editor>
		
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/glew32.dll
	 $<TARGET_FILE_DIR:Editor>
	 
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/SceneNAV.png
	 ${CMAKE_CURRENT_BINARY_DIR}
	 
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/SceneNAV.png
	$<TARGET_FILE_DIR:Editor>
	
)

# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(Editor
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(Editor
		PRIVATE
			/WX
	)
elseif(UNIX)
	target_compile_definitions(Editor
		PRIVATE
			OS_LINUX=1
	)
	target_compile_options(Editor
		PRIVATE
			-Werror
	)
endif()


# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(Editor PUBLIC cxx_std_17)
set_target_properties(Editor PROPERTIES
	CXX_EXTENSIONS OFF
)

# define debug macro
target_compile_definitions(Editor PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")

# list include directories
target_include_directories(Editor
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer3D
	${CMAKE_CURRENT_SOURCE_DIR}/external/
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew
	${CMAKE_CURRENT_SOURCE_DIR}/external/tinyobj/
	${CMAKE_CURRENT_SOURCE_DIR}/resources
)

# list Libs directories
target_link_directories (Editor
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer3D
	${CMAKE_CURRENT_SOURCE_DIR}/external/
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew
)

