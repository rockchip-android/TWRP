LOCAL_PATH:= $(call my-dir)

#######################################
include $(CLEAR_VARS)

LOCAL_MODULE := twrp.emmc.fstab
LOCAL_SRC_FILES := twrp.emmc.fstab
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/etc/

include $(BUILD_PREBUILT)

#######################################
include $(CLEAR_VARS)

LOCAL_MODULE := twrp.sd.fstab
LOCAL_SRC_FILES := twrp.sd.fstab
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/etc/

include $(BUILD_PREBUILT)

#######################################
include $(CLEAR_VARS)

LOCAL_MODULE := twrp.nvme.fstab
LOCAL_SRC_FILES := twrp.nvme.fstab
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/etc/

include $(BUILD_PREBUILT)
 