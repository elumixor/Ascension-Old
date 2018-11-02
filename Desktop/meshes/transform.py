import glob
import os
import struct

from vertex import *

dirname = os.path.dirname(__file__)


def relative(path=""):
    return os.path.join(dirname, path)


locations, textures, normals, vertices, indices = [], [], [], [], []


def operation(l):
    values = l.split(" ")

    if values[0] == "v":
        locations.append(Location(values[1], values[2], values[3]))
    if values[0] == "vt":
        textures.append(Texture(values[1], values[2]))
    if values[0] == "vn":
        normals.append(Normal(values[1], values[2], values[3]))
    if values[0] == "f":
        for face_vertex in range(1, 4):
            ind = values[face_vertex].split("/")
            vertex = Vertex(locations[int(ind[0]) - 1], textures[int(ind[1]) - 1], normals[int(ind[2]) - 1])

            found = False
            index = 0
            for vv in vertices:
                if vv == vertex:
                    found = True
                    break
                index += 1

            if not found:
                vertices.append(vertex)

            indices.append(index)


print("\nTransforming .obj to .ascobj")
counter = 1

os.chdir(relative(""))
for input_file in glob.glob("*.obj"):
    fname = os.path.splitext(input_file)[0]
    output = relative("generated/" + fname + ".ascobj")

    print(str(counter) + ":\t" + fname + ".obj -> " + fname + ".ascobj")
    counter += 1

    with open(input_file) as f:
        lines = f.read().splitlines()
        for line in lines:
            operation(line)
        f.close()

    # Write data
    f = open(output, "wb")

    # count and ind_count
    s = struct.pack("II", vertices.__len__(), indices.__len__())
    f.write(s)

    for v in vertices:
        # locations
        s = struct.pack("fff", float(v.location.x), float(v.location.y), float(v.location.z))
        f.write(s)

    for v in vertices:
        s = struct.pack("ff", float(v.texture.u), float(v.texture.v))
        f.write(s)

    for v in vertices:
        s = struct.pack("fff", float(v.normal.x), float(v.normal.y), float(v.normal.z))
        f.write(s)

    for v in indices:
        s = struct.pack("I", v)
        f.write(s)

    f.close()

print("Transformation successfully completed. Files written to " + relative("generated") + "\n")
