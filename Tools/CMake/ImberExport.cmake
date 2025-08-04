#------------------------------------------------
# Export API definitions
#------------------------------------------------

function(GenerateApiExport TARGET_NAME API_EXPORT_MACRO OUTPUT_DIR)
    string(TOUPPER ${TARGET_NAME} UPPER_TARGET_NAME)
    string(TOUPPER ${API_EXPORT_MACRO} UPPER_API_EXPORT_MACRO)

    if (NOT ${IMBER_STATIC})
        set_property(TARGET ${TARGET_NAME}
            PROPERTY DEFINE_SYMBOL "${UPPER_TARGET_NAME}_API_EXPORT"
        )
    endif()
    
    set(API_EXPORT_FILE ${OUTPUT_DIR}/${TARGET_NAME}Export.gen.h)
    include(GenerateExportHeader)
    generate_export_header(${TARGET_NAME}
        BASE_NAME ${TARGET_NAME}
        EXPORT_FILE_NAME ${API_EXPORT_FILE}
        EXPORT_MACRO_NAME ${UPPER_API_EXPORT_MACRO}
        NO_EXPORT_MACRO_NAME ${UPPER_TARGET_NAME}_NO_EXPORT
        DEPRECATED_MACRO_NAME ${UPPER_TARGET_NAME}_DEPRECATED
        NO_DEPRECATED_MACRO_NAME ${UPPER_TARGET_NAME}_NO_DEPRECATED
        STATIC_DEFINE ${UPPER_TARGET_NAME}_STATIC
    )

    message(STATUS "${TARGET_NAME} generated ${API_EXPORT_FILE}")

    if (MSVC)
        target_compile_options(${TARGET_NAME}
            PUBLIC
            "/FI${API_EXPORT_FILE}"
        )
    endif()
endfunction()
