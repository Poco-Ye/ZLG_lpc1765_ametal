# SDK 名字
SDK_NAME    ?= easy_arm_1114m0_sdk

# SDK 版本号
SDK_VERSION ?= 1.00

# 已发布的版本不可以再使用
SDK_VERSION_FORBID = 0.0

# 发布的 工程模板和示例程序 默认的调试工具： jlink ck100 ak100 ak100pro
DEBUGER ?= ck100

# 函数调用语法，很像变量的使用，也是以$来标识的，其语法为：$()或${}
# $(subst FROM,TO,TEXT) 即将字符串TEXT中的子串FROM变为TO
AW_HOME := $(subst \,/,$(AW_HOME))

export CODE_HOME  	   = $(AW_HOME)/apollo
export BUILD_HOME 	   = $(AW_HOME)/build
export TOOLS_HOME 	   = $(AW_HOME)/tools
export TARGET_HOME     = $(AW_HOME)/output
export LIB_HOME        = $(AW_HOME)/apollo/lib
export COMMON_DOC_HOME = $(BUILD_HOME)/sdks/$(SDK_NAME)/documents

export SDK_HOME   	   = $(BUILD_HOME)/sdks/$(SDK_NAME)
export SDK_SRC	  	   = $(SDK_HOME)
export SDK_TARGET 	   = $(TARGET_HOME)/sdks/$(SDK_NAME)_$(SDK_VERSION)

export SOURCES_TARGET    = $(SDK_TARGET)/apollo
export PROJECTS_TARGET   = $(SDK_TARGET)/projects
export EXAMPLES_TARGET   = $(SDK_TARGET)/examples
export DOCUMENTS_TARGET  = $(SDK_TARGET)/documents


# doxygen
DOXYGEN = $(TOOLS_HOME)/doxygen/bin/doxygen.exe



SUB_DIRS = 	apollo

DIRS = \
	$(SDK_TARGET)

ifeq "$(findstring $(SDK_VERSION), $(SDK_VERSION_FORBID))" ""
else
$(error the SDK_VERION can't be used, check if the verison is already released!)
endif

ifndef AW_HOME
$(error AW_HOME is not spedified!)
endif
