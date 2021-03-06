cmake_minimum_required(VERSION 3.1)
project(carto_mobile_sdk)

# General options
option(INCLUDE_GDAL "Link with GDAL" OFF)
option(INCLUDE_OBJC "Include ObjC code on iOS" OFF)

option(SINGLE_LIBRARY "Compile as single library" OFF)

if(IOS)
option(SHARED_LIBRARY "Build as shared library" OFF)
option(ENABLE_BITCODE "Enable bitcode support" ON)
endif(IOS)

# General platform-specific flags
if(WIN32)
set(CMAKE_VS_WINRT_EXTENSIONS ON)
set(VS_WINRT_EXTENSIONS ON)
endif(WIN32)

if(WIN32 OR ANDROID)
set(SDK_LIBRARY_TYPE SHARED)
elseif(SHARED_LIBRARY)
set(SDK_LIBRARY_TYPE SHARED)
elseif(NOT SHARED_LIBRARY)
set(SDK_LIBRARY_TYPE STATIC)
endif()

# C++ compiler flags
add_definitions("${SDK_CPP_DEFINES} -DHAVE_OT -DHAVE_UCDN -DHB_NO_MT -DFT2_BUILD_LIBRARY -DUSE_STD_REGEX -DBOOST_ALL_NO_LIB -DCRYPTOPP_DISABLE_ASM -DCRYPTOPP_DISABLE_SSE2 -DNDEBUG")

if(WIN32)
add_definitions("-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -DSQLITE_OS_WINRT -DSQLITE_OMIT_WAL -DGL_GLEXT_PROTOTYPES")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /EHs /GR")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Os")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /WINMD /NODEFAULTLIB:vccorlib /NODEFAULTLIB:msvcrt vccorlib.lib msvcrt.lib")
endif(WIN32)

if(IOS)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-arc -fmodules -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -fmodules -stdlib=libc++ -std=c++11 -ftemplate-depth=1024 -fexceptions -frtti -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -ObjC")

set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES)

if(ENABLE_BITCODE)
set(CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE YES)
else()
set(CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE NO)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release|RELEASE")
set(CMAKE_XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING YES)
set(CMAKE_XCODE_ATTRIBUTE_DEAD_CODE_STRIPPING YES)
set(CMAKE_XCODE_ATTRIBUTE_SEPARATE_STRIP YES)
set(CMAKE_XCODE_ATTRIBUTE_STRIP_STYLE "non-global")
set(CMAKE_XCODE_ATTRIBUTE_GENERATE_MASTER_OBJECT_FILE YES)
endif()

endif(IOS)

if(ANDROID)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ftemplate-depth=1024 -fexceptions -frtti -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os -flto=full -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -flto=full -fomit-frame-pointer")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -Wl,-plugin-opt=O2 -s -Wl,--gc-sections -Wl,--as-needed -fuse-ld=lld -Wl,--version-script=${PROJECT_SOURCE_DIR}/../android/version-script")

if(CMAKE_BUILD_TYPE MATCHES "Release|RELEASE")
string(REPLACE "-Wa,--noexecstack" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string(REPLACE "-Wa,--noexecstack" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

endif(ANDROID)

# Directories
set(SDK_BASE_DIR "${PROJECT_SOURCE_DIR}/../..")
set(SDK_SRC_DIR "${SDK_BASE_DIR}/all/native")
set(SDK_EXT_SRC_DIR "${SDK_BASE_DIR}/extensions/all/native")
set(SDK_CARTO_LIBS_DIR "${SDK_BASE_DIR}/libs-carto" )
set(SDK_EXTERNAL_LIBS_DIR "${SDK_BASE_DIR}/libs-external")

include_directories(
    "${SDK_EXT_SRC_DIR}"
    "${SDK_SRC_DIR}"
    "${SDK_CARTO_LIBS_DIR}/vt/src"
    "${SDK_CARTO_LIBS_DIR}/mapnikvt/src"
    "${SDK_CARTO_LIBS_DIR}/cartocss/src"
    "${SDK_CARTO_LIBS_DIR}/nml/src"
    "${SDK_CARTO_LIBS_DIR}/osrm/src"
    "${SDK_CARTO_LIBS_DIR}/sgre/src"
    "${SDK_CARTO_LIBS_DIR}/mbvtbuilder/src"
    "${SDK_CARTO_LIBS_DIR}/geocoding/src"
    "${SDK_EXTERNAL_LIBS_DIR}/boost"
    "${SDK_EXTERNAL_LIBS_DIR}/boostext"
    "${SDK_EXTERNAL_LIBS_DIR}/asio"
    "${SDK_EXTERNAL_LIBS_DIR}/cglib"
    "${SDK_EXTERNAL_LIBS_DIR}/stdext"
    "${SDK_EXTERNAL_LIBS_DIR}/cryptopp"
    "${SDK_EXTERNAL_LIBS_DIR}/freetype/include"
    "${SDK_EXTERNAL_LIBS_DIR}/harfbuzz/src"
    "${SDK_EXTERNAL_LIBS_DIR}/msdfgen"
    "${SDK_EXTERNAL_LIBS_DIR}/bidi"
    "${SDK_EXTERNAL_LIBS_DIR}/jpeg"
    "${SDK_EXTERNAL_LIBS_DIR}/miniz"
    "${SDK_EXTERNAL_LIBS_DIR}/pion/include"
    "${SDK_EXTERNAL_LIBS_DIR}/png"
    "${SDK_EXTERNAL_LIBS_DIR}/pbf"
    "${SDK_EXTERNAL_LIBS_DIR}/nanosvg/src"
    "${SDK_EXTERNAL_LIBS_DIR}/pugixml/src"
    "${SDK_EXTERNAL_LIBS_DIR}/pvrt"
    "${SDK_EXTERNAL_LIBS_DIR}/rapidjson/include"
    "${SDK_EXTERNAL_LIBS_DIR}/picojson"
    "${SDK_EXTERNAL_LIBS_DIR}/rg_etc1"
    "${SDK_EXTERNAL_LIBS_DIR}/sqlite"
    "${SDK_EXTERNAL_LIBS_DIR}/sqlite3pp"
    "${SDK_EXTERNAL_LIBS_DIR}/tinyformat"
    "${SDK_EXTERNAL_LIBS_DIR}/tess2/include"
    "${SDK_EXTERNAL_LIBS_DIR}/utf8/source"
    "${SDK_EXTERNAL_LIBS_DIR}/webp/src"
    "${SDK_EXTERNAL_LIBS_DIR}/png"
)

if(INCLUDE_VALHALLA)
include_directories(
    "${SDK_EXTERNAL_LIBS_DIR}/valhalla/include"
    "${SDK_EXTERNAL_LIBS_DIR}/valhalla/include/valhalla" 
    "${SDK_EXTERNAL_LIBS_DIR}/protobuf/src"
    "${SDK_EXTERNAL_LIBS_DIR}/date/include"
)
endif(INCLUDE_VALHALLA)

if(INCLUDE_GDAL)
include_directories(
    "${SDK_EXTERNAL_LIBS_DIR}/gdal/include"
)
endif(INCLUDE_GDAL)

if(INCLUDE_OBJC)
include_directories(
    "${SDK_SRC_DIR}/../../ios/objc"
)
endif(INCLUDE_OBJC)

if(ANDROID)
include_directories(
    "${SDK_SRC_DIR}/../../android/native"
)
elseif(IOS)
if(SDK_CPP_DEFINES MATCHES ".*_CARTO_USE_METALANGLE.*")
include_directories("${SDK_SRC_DIR}/../../libs-external/angle-metal/include")
else()
include_directories("${SDK_SRC_DIR}/../../ios/glwrapper")
endif()
include_directories(
    "${SDK_SRC_DIR}/../../ios/native"
    "${SDK_SRC_DIR}/../../generated/ios-objc/proxies"
    "${SDK_SRC_DIR}/../../generated/ios-objc/wrappers"
)
elseif(WIN32)
include_directories(
    "${SDK_SRC_DIR}/../../libs-external/angle-uwp/include"
    "${SDK_SRC_DIR}/../../winphone/native"
    "${SDK_EXTERNAL_LIBS_DIR}/zlib"
)
link_directories("${SDK_BASE_DIR}/libs-external/angle-uwp/${WINPHONE_ARCH}")
endif()

# Subprojects
add_subdirectory("${SDK_CARTO_LIBS_DIR}/vt" vt)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/mapnikvt" mapnikvt)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/cartocss" cartocss)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/nml" nml)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/osrm" osrm)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/sgre" sgre)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/mbvtbuilder" mbvtbuilder)
add_subdirectory("${SDK_CARTO_LIBS_DIR}/geocoding" geocoding)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/bidi" bidi)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/cryptopp" cryptopp)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/freetype" freetype)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/harfbuzz" harfbuzz)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/msdfgen" msdfgen)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/jpeg" jpeg)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/miniz" miniz)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/png" png)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/pugixml" pugixml)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/pvrt" pvrt)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/rg_etc1" rg_etc1)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/sqlite" sqlite)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/sqlite3pp" sqlite3pp)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/tess2" tess2)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/webp" webp)

if(INCLUDE_VALHALLA)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/date" date)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/protobuf" protobuf)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/valhalla" valhalla)
endif(INCLUDE_VALHALLA)

if(WIN32)
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/zlib" zlib)
endif(WIN32)

if(NOT (WIN32 OR IOS OR ANDROID))
add_subdirectory("${SDK_EXTERNAL_LIBS_DIR}/pion" pion)
endif()

# SDK files
file(GLOB SDK_SRC_FILES
    "${SDK_SRC_DIR}/*/*.cpp"
    "${SDK_SRC_DIR}/*/*/*.cpp"
    "${SDK_SRC_DIR}/*/*.h"
    "${SDK_SRC_DIR}/*/*/*.h"
    "${SDK_EXT_SRC_DIR}/*/*.cpp"
    "${SDK_EXT_SRC_DIR}/*/*/*.cpp"
    "${SDK_EXT_SRC_DIR}/*/*.h"
    "${SDK_EXT_SRC_DIR}/*/*/*.h"
)
set_source_files_properties("${SDK_SRC_DIR}/../../all/native/utils/PlatformUtils.cpp" PROPERTIES COMPILE_FLAGS "-D_CARTO_MOBILE_SDK_PLATFORM=\"\\\"${SDK_PLATFORM}\\\"\" -D_CARTO_MOBILE_SDK_VERSION=\"\\\"${SDK_VERSION}\\\"\"")

if(WIN32 OR IOS OR ANDROID)
list(REMOVE_ITEM SDK_SRC_FILES "${SDK_SRC_DIR}/network/HTTPClientPionImpl.cpp")
endif()

if(ANDROID)
file(GLOB SDK_ANDROID_SRC_FILES
    "${WRAPPER_DIR}/*.cpp"
    "${WRAPPER_DIR}/*.h"
    "${SDK_SRC_DIR}/../../android/native/*/*.cpp"
    "${SDK_SRC_DIR}/../../android/native/*/*.h"
    "${SDK_SRC_DIR}/../../android/native/*/*/*.cpp"
    "${SDK_SRC_DIR}/../../android/native/*/*/*.h"
)
set(SDK_SRC_FILES "${SDK_SRC_FILES}" "${SDK_ANDROID_SRC_FILES}")
elseif(IOS)
if(INCLUDE_OBJC)
file(GLOB SDK_OBJC_SRC_FILES
    "${SDK_SRC_DIR}/../../ios/objc/*/*.cpp"
    "${SDK_SRC_DIR}/../../ios/objc/*/*.mm"
    "${SDK_SRC_DIR}/../../ios/objc/*/*.h"
    "${SDK_SRC_DIR}/../../ios/objc/*.h"
)
set(SDK_SRC_FILES "${SDK_SRC_FILES}" "${SDK_OBJC_SRC_FILES}")
endif(INCLUDE_OBJC)
file(GLOB SDK_IOS_SRC_FILES
    "${WRAPPER_DIR}/*.cpp"
    "${WRAPPER_DIR}/*.mm"
    "${WRAPPER_DIR}/*.h"
    "${SDK_SRC_DIR}/../../ios/native/*/*.cpp"
    "${SDK_SRC_DIR}/../../ios/native/*/*.mm"
    "${SDK_SRC_DIR}/../../ios/native/*/*.h"
)
set(SDK_SRC_FILES "${SDK_SRC_FILES}" "${SDK_IOS_SRC_FILES}")
elseif(WIN32)
file(GLOB SDK_WINRT_SRC_FILES
    "${WRAPPER_DIR}/*.cpp"
    "${WRAPPER_DIR}/*.h"
    "${SDK_SRC_DIR}/../../winphone/native/*/*.cpp"
    "${SDK_SRC_DIR}/../../winphone/native/*/*.h"
    "${SDK_SRC_DIR}/../../winphone/native/*/*/*.cpp"
    "${SDK_SRC_DIR}/../../winphone/native/*/*/*.h"
)
set(SDK_SRC_FILES "${SDK_SRC_FILES}" "${SDK_WINRT_SRC_FILES}")

set_source_files_properties("${SDK_SRC_DIR}/../../winphone/native/utils/AssetUtils.cpp" PROPERTIES COMPILE_FLAGS "/ZW")
set_source_files_properties("${SDK_SRC_DIR}/../../winphone/native/utils/PlatformUtils.cpp" PROPERTIES COMPILE_FLAGS "/ZW")
set_source_files_properties("${SDK_SRC_DIR}/../../winphone/native/utils/EGLContextWrapper.cpp" PROPERTIES COMPILE_FLAGS "/ZW")
set_source_files_properties("${SDK_SRC_DIR}/../../winphone/native/components/Task.cpp" PROPERTIES COMPILE_FLAGS "/ZW")
endif()

# Group wrapper files into different groups, to reduce clutter
source_group("Wrapper Sources"
    REGULAR_EXPRESSION ".*_wrap.cpp"
)
source_group("Wrapper Headers"
    REGULAR_EXPRESSION ".*_wrap.h"
)

# Linking
if(SINGLE_LIBRARY)

set(SDK_SRC_FILES
    "${SDK_SRC_FILES}"
    "${vt_SRC_FILES}"
    "${mapnikvt_SRC_FILES}"
    "${cartocss_SRC_FILES}"
    "${nml_SRC_FILES}"
    "${osrm_SRC_FILES}"
    "${sgre_SRC_FILES}"
    "${mbvtbuilder_SRC_FILES}"
    "${geocoding_SRC_FILES}"
    "${bidi_SRC_FILES}"
    "${cryptopp_SRC_FILES}"
    "${rg_etc1_SRC_FILES}"
    "${pvrt_SRC_FILES}"
    "${pugixml_SRC_FILES}"
    "${libtess2_SRC_FILES}"
    "${miniz_SRC_FILES}"
    "${png_SRC_FILES}"
    "${jpeg_SRC_FILES}"
    "${webp_SRC_FILES}"
    "${freetype_SRC_FILES}"
    "${harfbuzz_SRC_FILES}"
    "${msdfgen_SRC_FILES}"
    "${sqlite3pp_SRC_FILES}"
    "${sqlite_SRC_FILES}"
)

if(INCLUDE_VALHALLA)
set(SDK_SRC_FILES ${SDK_SRC_FILES}
    "${date_SRC_FILES}"
    "${protobuf_SRC_FILES}"
    "${valhalla_SRC_FILES}"
)
endif(INCLUDE_VALHALLA)

if(WIN32)
set(SDK_SRC_FILES ${SDK_SRC_FILES} "${zlib_SRC_FILES}")
endif(WIN32)

if(NOT (WIN32 OR IOS OR ANDROID))
set(SDK_SRC_FILES ${SDK_SRC_FILES} "${pion_SRC_FILES}")
endif()

set(SDK_OBJECTS "")

else(SINGLE_LIBRARY)

set(SDK_OBJECTS
    $<TARGET_OBJECTS:vt>
    $<TARGET_OBJECTS:mapnikvt>
    $<TARGET_OBJECTS:cartocss>
    $<TARGET_OBJECTS:nml>
    $<TARGET_OBJECTS:osrm>
    $<TARGET_OBJECTS:sgre>
    $<TARGET_OBJECTS:mbvtbuilder>
    $<TARGET_OBJECTS:geocoding>
    $<TARGET_OBJECTS:bidi>
    $<TARGET_OBJECTS:cryptopp>
    $<TARGET_OBJECTS:rg_etc1>
    $<TARGET_OBJECTS:pvrt>
    $<TARGET_OBJECTS:pugixml>
    $<TARGET_OBJECTS:libtess2>
    $<TARGET_OBJECTS:miniz>
    $<TARGET_OBJECTS:png>
    $<TARGET_OBJECTS:jpeg>
    $<TARGET_OBJECTS:webp>
    $<TARGET_OBJECTS:freetype>
    $<TARGET_OBJECTS:harfbuzz>
    $<TARGET_OBJECTS:msdfgen>
    $<TARGET_OBJECTS:sqlite3pp>
    $<TARGET_OBJECTS:sqlite>
)

if(INCLUDE_VALHALLA)
set(SDK_OBJECTS ${SDK_OBJECTS}
    $<TARGET_OBJECTS:date>
    $<TARGET_OBJECTS:protobuf>
    $<TARGET_OBJECTS:valhalla>
)
endif(INCLUDE_VALHALLA)

if(WIN32)
set(SDK_OBJECTS ${SDK_OBJECTS} $<TARGET_OBJECTS:zlib>)
endif(WIN32)

if(NOT (WIN32 OR IOS OR ANDROID))
set(SDK_OBJECTS ${SDK_OBJECTS} $<TARGET_OBJECTS:pion>)
endif()

endif(SINGLE_LIBRARY)

add_library(carto_mobile_sdk ${SDK_LIBRARY_TYPE}
    ${SDK_SRC_FILES}
    ${SDK_OBJECTS}
)

if(INCLUDE_GDAL)
add_library(gdal SHARED IMPORTED)
if(ANDROID)
set_property(TARGET gdal PROPERTY IMPORTED_LOCATION "${SDK_BASE_DIR}/prebuilt/gdal/libs/${ANDROID_ABI}/libgdal.so")
endif(ANDROID)
target_link_libraries(carto_mobile_sdk gdal)
endif(INCLUDE_GDAL)

if(ANDROID)
target_link_libraries(carto_mobile_sdk EGL GLESv2 z log android jnigraphics)
elseif(IOS)
if(SDK_CPP_DEFINES MATCHES ".*_CARTO_USE_METALANGLE.*")
target_link_libraries(carto_mobile_sdk "-framework Foundation" "-framework CoreGraphics" "-framework CoreText" "-framework IOSurface" "-framework UIKit" "-framework CFNetwork")
else()
target_link_libraries(carto_mobile_sdk "-framework Foundation" "-framework CoreGraphics" "-framework CoreText" "-framework OpenGLES" "-framework GLKit" "-framework UIKit" "-framework CFNetwork")
endif()
elseif(WIN32)
target_link_libraries(carto_mobile_sdk msxml6.lib d3d11.lib dwrite.lib d2d1.lib libEGL.dll.lib libGLESv2.dll.lib)
endif()
