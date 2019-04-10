#! /usr/bin/python
import subprocess
import os
import sys
import shutil
import stat

if (os.path.exists("src/core/build")):
	shutil.rmtree("src/core/build")

if (os.path.exists("src/core/generated_code")):
	shutil.rmtree("src/core/generated_code")

if (os.path.exists("src/tools/build")):
	shutil.rmtree("src/tools/build")

if (os.path.exists("build")):
	shutil.rmtree("build")
