add_library(fls_reader
        OBJECT
        column_view.cpp
        fls_rowgroup.cpp
        reader.cpp
        segment.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_reader>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_reader PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()