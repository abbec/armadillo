#!/bin/sh

find_clang() {

if [ -f "/usr/bin/clang" ]
then
	clang_path="/usr/bin/clang"
elif [ -f "/usr/local/bin/clang" ]
then
	clang_path="/usr/local/bin/clang"
fi

if [ ! -z "$clang_path" ]
then
	echo "found clang at $clang_path"
	export CC=$clang_path
	return 0
else
	echo "could not find clang"
	return 1
fi

}

find_asm() {

if [ -f "/usr/bin/arm-none-eabi-as" ]
then
	asm_path="/usr/bin/arm-none-eabi-as"
elif [ -f "/usr/local/bin/arm-none-eabi-as" ]
then
	asm_path="/usr/local/bin/arm-none-eabi-as"
fi

if [ ! -z "$asm_path" ]
then
	echo "found gnu assembler for arm at $asm_path"
	export ASM=$asm_path
	return 0
else
	echo "could not find gnu assembler for arm."
	return 1
fi
}

find_clang
find_asm

