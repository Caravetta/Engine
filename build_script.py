import subprocess
import os
import sys
import shutil
import stat

if sys.platform != 'win32' and sys.platform != 'linux':
    sys.exit("%s is not supported" % sys.platform)

os.chdir("src/core/")

if (os.path.exists("generated_code")):
	shutil.rmtree("generated_code")

os.mkdir("generated_code")
os.mkdir("generated_code/include")

os.chdir("../../")

os.chdir("src/tools/")
subprocess.call(["9k", "build"])

os.chdir("build/")
if sys.platform == 'win32':
	subprocess.call(["ninja"])

os.chdir("../../../")

lib_headers = []

lib_headers.append("src/tools/build/Component_ID_Generator")
lib_headers.append("src/core/generated_code/")
lib_headers.append("base_generated_component_info")

for root, dirs, files in os.walk("src/core/"):
    for file in files:
    	if sys.platform == 'win32':
    		if (file.find('linux') == -1):
        		if (file.endswith(".h")):
            	 	 lib_headers.append(os.path.join(root, file))


subprocess.call(lib_headers)

lib_headers.pop(1)
lib_headers.pop(2)
lib_headers.pop(3)

os.chdir("src/core/")

subprocess.call(["9k", "build"])

os.chdir("build/")
if sys.platform == 'win32':
	subprocess.call(["ninja"])

os.chdir("../../../")

if (os.path.exists("build")):
	shutil.rmtree("build")

os.mkdir("build")
os.mkdir("build/Engine_Tools")
os.mkdir("build/Engine_Core")
os.mkdir("build/Engine_Core/include")

lib_header = []

for root, dirs, files in os.walk("src/core/"):
    for file in files:
    	if sys.platform == 'win32':
    		if (file.find('linux') == -1):
        		if (file.endswith(".h")):
            	 	 lib_header.append(os.path.join(root, file))

for file in lib_header:
	if sys.platform == 'win32':
		os.system("copy %s build\Engine_Core\include\. >nul 2>&1" % (file.replace('/', '\\')))

lib_files = []

if sys.platform == 'win32':
	for root, dirs, files in os.walk("src/core/build"):
		for file in files:
			if (file.endswith(".dll") or file.endswith(".exp") or file.endswith(".lib")):
				lib_files.append(os.path.join(root, file))

	for file in lib_files:
		os.system("copy %s build\Engine_Core\. >nul 2>&1" % (file.replace('/', '\\')))


tools = []

if sys.platform == 'win32':
	for root, dirs, files in os.walk("src/tools/build"):
		for file in files:
			if (file.endswith(".exe")):
				tools.append(os.path.join(root, file))

	for file in tools:
		os.system("copy %s build\Engine_Tools\. >nul 2>&1" % (file.replace('/', '\\')))
