file(GLOB subdirs CONFIGURE_DEPENDS *)

foreach(subdir ${subdirs})
    if(IS_DIRECTORY ${subdir})
        get_filename_component(module "${subdir}" NAME) #Get module name
        add_subdirectory(${module})
    endif()
endforeach()

# add_subdirectory(Graphics)