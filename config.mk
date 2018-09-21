# SDK ����
SDK_NAME    ?= easy_arm_1114m0_sdk

# SDK �汾��
SDK_VERSION ?= 1.00

# �ѷ����İ汾��������ʹ��
SDK_VERSION_FORBID = 0.0

# ������ ����ģ���ʾ������ Ĭ�ϵĵ��Թ��ߣ� jlink ck100 ak100 ak100pro
DEBUGER ?= ck100

# ���������﷨�����������ʹ�ã�Ҳ����$����ʶ�ģ����﷨Ϊ��$()��${}
# $(subst FROM,TO,TEXT) �����ַ���TEXT�е��Ӵ�FROM��ΪTO
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
