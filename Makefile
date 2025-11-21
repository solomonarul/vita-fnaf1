# This Makefile is meant to be used only in development environments.

.DEFAULT_GOAL := _bruh

TARGET = app

_bruh:
	@echo "You didn't read the README, did you?"

c:
	@cmake -E remove vgcore.*
	@cmake -E remove_directory build && echo "[INFO]: Removed build directory."
	@cmake -E remove_directory .cache && echo "[INFO]: Removed .cache directory."
	@cmake -E remove_directory out && echo "[INFO]: Removed out directory."

bud:
	@cmake -B build -S . --preset unix-debug
	@cmake --build build -j${nproc}
	@cmake --install build --prefix out

bur:
	@cmake -B build -S . --preset unix-release
	@cmake --build build -j${nproc}
	@cmake --install build --prefix out

but:
	@cmake -B build -S . --preset unix-test
	@cmake --build build -j${nproc}
	@cmake --install build --prefix out

bwd:
	@cmake -B build -S . --preset windows-debug
	@cmake --build build
	@cmake --install build --prefix out
bwr:
	@cmake -B build -S . --preset windows-release
	@cmake --build build
	@cmake --install build --prefix out

bwt:
	@cmake -B build -S . --preset windows-test
	@cmake --build build
	@cmake --install build --prefix out

bvd:
	@cmake -B build -S . --preset vita-debug
	@cmake --build build -j${nproc}
	@cmake -E copy ./build/app.vpk ./out/vpk/app.vpk

bvr:
	@cmake -B build -S . --preset vita-release
	@cmake --build build -j${nproc}
	@cmake -E copy ./build/app.vpk ./out/vpk/app.vpk

r:
	@./out/bin/${TARGET}

rv:
	@vita3k ./out/vpk/${TARGET}.vpk

sv:
	@curl -T ./out/vpk/${TARGET}.vpk ftp://$(VITA_ADDR)/ux0:/VPK/${TARGET}.vpk