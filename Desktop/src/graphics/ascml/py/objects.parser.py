import glob
import os
import re
from functools import reduce


def relative(path=""):
    return os.path.join(os.path.dirname(__file__), path)


class Field:
    def __init__(self, f_type, name, initializer):
        self.f_type, self.name, self.initializer = f_type, name, initializer

    def __print__(self):
        print("type: " + self.f_type)
        print("name: " + self.name)
        print("initializer: " + self.initializer)

    def __str__(self):
        return types.get(self.f_type, self.f_type) + " " + self.name + " { " + self.initializer + " };"


class Object:
    def __init__(self, name, *fields):
        self.name, self.fields = name, fields
        self.define = "ASCENSION_OBJECTS_" + name.upper() + "_H"
        attribs = reduce(lambda attr1, attr2: str(attr1) + "\n\t" + str(attr2), self.fields)
        self.body = "struct " + self.name + " : public ObjectBase {\n\t" + attribs + "\n" \
                    "\n\tvoid set(const std::string& base_name = \"\") const override;\n};\n"
        deps = list(set(map(lambda x: x.f_type, fields)))
        self.includes = ["#include \"../..//ObjectBase.h\""]
        for dep in deps:
            global includes
            self.includes.append(includes.get(dep, "#include \"%s/%s.h\"" % (dep, dep)))

    def __repr__(self):
        return self.body

    def header(self):
        return "#ifndef " + self.define + "\n" \
                                          "#define " + self.define + "\n\n" \
               + "\n".join(self.includes) + "\n\n" \
               + self.body + \
               "\n#endif //ASCENSION_OBJECTBASE_H\n"

    def source(self):
        return ""
        pass


rxd = {
    'name': re.compile(r'^(.*?)[{ \t\n]{(.*)}'),
}
types = {
    'i': "int",
    'u': "unsigned",
    'b': "bool",
    'f': "float",
    'v2': "glm::vec2",
    'v3': "glm::vec3",
    'v4': "glm::vec4",
    'm2': "glm::mat2",
    'm3': "glm::mat3",
    'm4': "glm::mat4",
}
includes = {
    'i': "",
    'u': "",
    'b': "",
    'f': "",
    'v2': "#include <glm/vec2.hpp>",
    'v3': "#include <glm/vec3.hpp>",
    'v4': "#include <glm/vec4.hpp>",
    'm2': "#include <glm/detail/type_mat3x3.hpp>",
    'm3': "#include <glm/detail/type_mat2x2.hpp>",
    'm4': "#include <glm/detail/type_mat4x4.hpp>",
}
u_location = '(*api.program, (base_name + ".%s").c_str())'
u_type = dict.fromkeys(['i', 'u', 'f'],
                       'glUniform%s(glGetUniformLocation' + u_location + ', this->%s);')
u_type.update(dict.fromkeys(['v2', 'v3', 'v4'],
                            'glUniform%s(glGetUniformLocation' + u_location + ', 1, &this->%s[0]);'))
u_type.update(dict.fromkeys(['m2', 'm3', 'm4'],
                            'glUniform%s(glGetUniformLocation' + u_location + ', 1, GL_FALSE, &this->%s[0][0]);'))
uniforms = {
    'i': "1i",
    'u': "1ui",
    'b': "1i",
    'f': "1f",
    'v2': "2fv",
    'v3': "3fv",
    'v4': "4fv",
    'm2': "Matrix2fv",
    'm3': "Matrix3fv",
    'm4': "Matrix4fv",
}
objects_count = 1
access_rights = 0o755


def parse_attribute(attribute):
    attribute = attribute.strip()
    spl = attribute.split("{")
    _initializer = spl[1].strip()
    spl = spl[0].split(" ")
    _type = spl[0].strip()
    _name = spl[1].strip()
    return Field(_type, _name, _initializer)


def generate(file):
    global objects_count
    with open(file) as f:
        # Read all text
        text = "".join(f.read().splitlines())

        # Object name
        res = rxd["name"].search(text)
        name = res.group(1).strip()
        body = res.group(2).strip()
        attributes = list(filter(lambda x: x != '', body.split("}")))
        attributes = list(map(parse_attribute, attributes))

        obj = Object(name, *attributes)

        print("\n" + str(objects_count) + ": " + str(obj))

        objects_count += 1
        f.close()
        create_files(obj)


def create_uniforms(fields):
    f = ""
    for ff in fields:
        if ff.f_type in u_type:
            f += "\t" + (u_type[ff.f_type] % (uniforms[ff.f_type], ff.name, ff.name)) + "\n"
        else:
            f += "\t" + ff.name + ".set(base_name + \".%s\");\n" % ff.name
    return f


def create_files(obj):
    print(obj.header())
    os.mkdir("generated/" + obj.name, access_rights)

    fname = "generated/" + obj.name + "/" + obj.name
    file = open(fname + ".h", "w+")
    file.write(obj.header())
    file.close()

    file = open(fname + ".cpp", "w+")
    fields_uniforms = create_uniforms(obj.fields)
    file.write('#include <graphics/ascml/AscmlApi.h>\n'
               '#include <GL/glew.h>\n'
               '#include "' + obj.name + '.h"\n\n'
               'void ' + obj.name + '::set(const std::string& base_name = \"\") const {\n'
               + fields_uniforms +
               '}\n')
    file.close()


# Generate sources for all .ascmlo files
print("Generating source files from .ascmlo")
os.chdir(relative("../objects"))
for input_file in glob.glob("*.ascmlo"):
    generate(input_file)
