##设置库名称
set(LIBRARY_TARGET_NAME muduo)

##查找所有头文件
file(GLOB_RECURSE  base_HEADER_FILES
    LIST_DIRECTORIES False 
    "${PROJECT_SOURCE_DIR}/base/*.h"
)
file(GLOB_RECURSE  net_HEADER_FILES
    LIST_DIRECTORIES False 
	"${PROJECT_SOURCE_DIR}/net/*.h"
)
#file(GLOB_RECURSE  test_HEADER_FILES
#    LIST_DIRECTORIES False 
#	"${PROJECT_SOURCE_DIR}/test/*.h"
#)
file(GLOB_RECURSE  alds_HEADER_FILES
    LIST_DIRECTORIES False 
	"${PROJECT_SOURCE_DIR}/alds/*.h"
)

##设置VS筛选器，头文件分文件夹
source_group(
    TREE "${PROJECT_SOURCE_DIR}/base"
    PREFIX "Header Files"
    FILES ${base_HEADER_FILES}
)
source_group(
    TREE "${PROJECT_SOURCE_DIR}/net"
    PREFIX "Header Files"
    FILES ${net_HEADER_FILES}
)
source_group(
    TREE "${PROJECT_SOURCE_DIR}/test"
    PREFIX "Header Files"
    FILES ${test_HEADER_FILES}
)
source_group(
    TREE "${PROJECT_SOURCE_DIR}/alds"
    PREFIX "Header Files"
    FILES ${alds_HEADER_FILES}
)

##查找所有源文件
file(GLOB_RECURSE  base_SRC_FILES
    LIST_DIRECTORIES False 
    "${PROJECT_SOURCE_DIR}/base/*.cc"
	"${PROJECT_SOURCE_DIR}/base/*.cpp"
)
file(GLOB_RECURSE  net_SRC_FILES
    LIST_DIRECTORIES False 
	"${PROJECT_SOURCE_DIR}/net/*.cc"
)
file(GLOB_RECURSE  test_SRC_FILES
    LIST_DIRECTORIES False 
	#"${PROJECT_SOURCE_DIR}/test/*.cc"
    #"${PROJECT_SOURCE_DIR}/test/acceptor_test.cc"
)

##设置VS筛选器，源码分文件夹
source_group(
    TREE "${PROJECT_SOURCE_DIR}/base"
    PREFIX "Source Files"
    FILES ${base_SRC_FILES}
)
source_group(
    TREE "${PROJECT_SOURCE_DIR}/net"
    PREFIX "Source Files"
    FILES ${net_SRC_FILES}
)
source_group(
    TREE "${PROJECT_SOURCE_DIR}/test"
    PREFIX "Source Files"
    FILES ${test_SRC_FILES}
)

##设置生成目标
add_executable(${LIBRARY_TARGET_NAME}
	${base_HEADER_FILES}
	${net_HEADER_FILES}
	#${test_HEADER_FILES}
	${alds_HEADER_FILES}
	
    ${base_SRC_FILES}
	${net_SRC_FILES}
	${test_SRC_FILES}
)

##指定工程文件分组
set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES FOLDER "FolderName")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE") # WINDOWS

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES WIN32_EXECUTABLE ON)

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES LINK_FLAGS "/SAFESEH:NO /LARGEADDRESSAWARE")


##指定工程生成文件组织结构
#set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

##打开qt特性配置
#set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES AUTOMOC ON)

##设置预处理器定义
target_compile_definitions(${LIBRARY_TARGET_NAME} PRIVATE UNICODE WIN32 QT_DLL QT_CORE_LIB QT_GUI_LIB QT_WIDGETS_LIB) # QT_NO_DEBUG NDEBUG

##配置构建/使用时的头文件路径
target_include_directories(
    ${LIBRARY_TARGET_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/base/>"
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/net/>"
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/>"
	
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/alds/>"
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/3rdParty/include/>"
)

##配置库依赖
#find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
target_link_libraries(${LIBRARY_TARGET_NAME}
    #PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets
	${PROJECT_SOURCE_DIR}/3rdParty/lib/$<CONFIG>/libprotobuf.lib 
	${PROJECT_SOURCE_DIR}/3rdParty/lib/$<CONFIG>/libprotobuf-lite.lib 
	${PROJECT_SOURCE_DIR}/3rdParty/lib/$<CONFIG>/libprotoc.lib
)
