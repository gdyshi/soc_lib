PROJECT(middle)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


 
 SET(MIDDLE_HDRS  
     ZQ_ECG_errno.h           
     ZQ_ECG_prj.h                      
     ZQ_ECG_types.h
     ZQ_ECG_middle_message.h
     ZQ_ECG_debug.h  
     ZQ_ECG_print.h
     ZQ_ECG_includes.h
)  
  


SET(SRC_LIST_SMP ZQ_ECG_sample.c ZQ_ECG_smp_board.c MD5.c console_test.c)
SET(SRC_LIST_BAT ZQ_ECG_battery.c)
SET(SRC_LIST_PRINT ZQ_ECG_print.c)
SET(SRC_LIST_MSG device_state_server.c)

SET(SRC_LIST_PWM pwm.c)






include_directories ("/opt/include")
#include_directories ("/opt/include/libxml2")
include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/../filter")
include_directories ("${PROJECT_SOURCE_DIR}/../common")
include_directories ("${PROJECT_SOURCE_DIR}/../anasys")
include_directories ("${PROJECT_SOURCE_DIR}/../postserver")
include_directories ("${PROJECT_SOURCE_DIR}/../buffer")

#include_directories ("${PROJECT_SOURCE_DIR}/../parser")

LINK_DIRECTORIES ("/opt/lib")
LINK_DIRECTORIES ("${PROJECT_SOURCE_DIR}/../common")

#INCLUDE_DIRECTORIES(Include)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
#ADD_LIBRARY(${library_name} SHARED ${DIR_SRCS})
ADD_EXECUTABLE(middle_smp ${SRC_LIST_SMP})
ADD_EXECUTABLE(middle_battery ${SRC_LIST_BAT})
ADD_EXECUTABLE(middle_print ${SRC_LIST_PRINT})
ADD_EXECUTABLE(middle_msg ${SRC_LIST_MSG})

ADD_EXECUTABLE(pwm ${SRC_LIST_PWM})




target_link_libraries (middle_smp zq_ecg_common zq_ecg_anasys zq_ecg_filter zq_ecg_buffer pthread)
target_link_libraries (middle_print pthread)
target_link_libraries (middle_msg nanomsg  post qlibc)

# add the install targets
install (TARGETS middle_smp DESTINATION ${PROJECT_SOURCE_DIR}/../build/bin)
install (TARGETS middle_battery DESTINATION ${PROJECT_SOURCE_DIR}/../build/bin)
install (TARGETS middle_print DESTINATION ${PROJECT_SOURCE_DIR}/../build/bin)
install (TARGETS middle_msg DESTINATION ${PROJECT_SOURCE_DIR}/../build/bin)
install (TARGETS pwm DESTINATION ${PROJECT_SOURCE_DIR}/../build/bin)
install (FILES ${MIDDLE_HDRS} DESTINATION ${PROJECT_SOURCE_DIR}/../build/include)