if (CONFIG_OUR_DRIVER)
    target_sources(app PRIVATE my_driver.c)
    zephyr_include_directories(.)
endif()