import os


def relative(path=""):
    return os.path.join(os.path.dirname(__file__), path)


def source_name(path):
    split = path.split("/")
    return str(split[split.__len__() - 2]) + "/" + str(split[split.__len__() - 1])


# Get source files
rootDir = relative("objects/generated")
all_files = " ../ObjectBase.h\n" \
            "\t../../AscmlApi.h../../AscmlApi.cpp\n" \
            "\t../../scenes/Base/Base.h ../../scenes/Base/Base.cpp\n"
for subdir, dirs, files in os.walk(rootDir):
    for file in files:
        if file.endswith(".cpp") or file.endswith(".h"):
            fl = os.path.join(subdir, file)
            all_files += " " + source_name(fl)


# Create CMakeList.txt
output = relative("../objects/generated/CMakeLists.txt")
f = open(output, "w+")

f.write('project(Objects)\n')
f.write('include_directories(.)\n')
f.write('add_library(${PROJECT_NAME} STATIC' + all_files + ')\n')
f.write('target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})\n')
f.close()

print("CMake file created")
