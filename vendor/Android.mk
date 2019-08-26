#
# Copyright (C) 2014 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
ifneq ($(shell test $(PLATFORM_SDK_VERSION) -gt 25; echo $$?),0)
include $(LOCAL_PATH)/android7/Android.mk
else ifneq ($(shell test $(PLATFORM_SDK_VERSION) -gt 27; echo $$?),0)
include $(LOCAL_PATH)/android8/Android.mk
else
include $(LOCAL_PATH)/android9/Android.mk
endif
