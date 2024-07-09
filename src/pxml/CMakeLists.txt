add_custom_target(update_pxml
    pargen ${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../lib
)