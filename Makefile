# Helper Makefile to automate specific helper tasks

REPO_NAME ?= cpp-repo-template

SHELL := /bin/bash


.PHONY: help
help:
	@LC_ALL=C $(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'


venv/bin/activate: requirements.txt
	python3 -m venv venv --system-site-packages --symlinks --upgrade-deps
	source ./venv/bin/activate \
		&& pip install --upgrade pip setuptools wheel \
		&& pip install  --no-build-isolation -r requirements.txt

.PHONY: build-venv
build-env: venv/bin/activate

dev-container: venv/bin/activate
	source ./venv/bin/activate && ./repo-cli.py prompt build_env


BUILD_TYPES = Debug Release

# Function populating the build rules per release type
define BUILD_template=

# Gennerate compile_commands.json file, pass -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: configure-$(1)
configure-$(1): cmake/config.cmake
	mkdir -p build-$(1) install-$(1)
	cp cmake/config.cmake build-$(1)
	conan install . --output-folder=build-$(1) --profile .conan/profiles/default
	cd build-$(1) && cmake .. -DCMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake -G Ninja -DCMAKE_INSTALL_PREFIX=`realpath ../install-$(1)` -DCMAKE_BUILD_TYPE=$(1) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: build-$(1)
build-$(1): configure-$(1)
	cd build-$(1) && ninja all

endef

$(foreach build,$(BUILD_TYPES),$(eval $(call BUILD_template,$(build))))

.PHONY: clean
clean:
	rm -rf build-* install-*
