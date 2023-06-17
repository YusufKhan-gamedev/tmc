# ========
# compiler
# ========

ifndef TOOLCHAIN_PATH
ifneq (,$(shell which gcc))
TOOLCHAIN_PATH :=
else ifdef DEVKITARM
TOOLCHAIN_PATH := $(DEVKITARM)/bin/
else
$(error gcc not found, please install)
endif
endif

# ensure trailing slash
ifneq ($(TOOLCHAIN_PATH),)
override TOOLCHAIN_PATH:=$(TOOLCHAIN_PATH)/
endif

CC := $(TOOLCHAIN_PATH)gcc
CPP := $(CC) -E
CXX := $(TOOLCHAIN_PATH)g++
AS := $(TOOLCHAIN_PATH)as
LD := $(TOOLCHAIN_PATH)ld
OBJCOPY := $(TOOLCHAIN_PATH)objcopy

# ============
# custom tools
# ============

CC1 := $(TOOLCHAIN_PATH)gcc
SHA1 := $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c

SCANINC := tools/bin/scaninc
PREPROC := tools/bin/preproc
ASSET_PROCESSOR := tools/bin/asset_processor
ENUM_PROCESSOR := tools/extract_include_enum.py
FIX := tools/bin/gbafix

