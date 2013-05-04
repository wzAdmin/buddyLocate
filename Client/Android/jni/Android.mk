LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(call my-dir)

###########################################################
## Find all of files under the named directories.
###########################################################

define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "$(2)" -and -not -name ".*") \
 )
endef

define all-cpp-files-under
$(call all-files-under,$(1),*.cpp)
endef

define all-c-files-under
$(call all-files-under,$(1),*.c)
endef

define all-S-files-under
$(call all-files-under,$(1),*.S)
endef
CUR_PATH := $(LOCAL_PATH)
include $(CUR_PATH)/Client.mk

