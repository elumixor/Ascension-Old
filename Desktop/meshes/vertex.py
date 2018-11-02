class Location:
    x, y, z = None, None, None

    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

    def __eq__(self, other):
        return isinstance(other, Location) and self.x == other.x and self.y == other.y and self.z == other.z


class Texture:
    def __init__(self, u, v):
        self.u, self.v = u, v

    def __eq__(self, other):
        return isinstance(other, Texture) and self.u == other.u and self.v == other.v


class Normal:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

    def __eq__(self, other):
        return isinstance(other, Normal) and self.x == other.x and self.y == other.y and self.z == other.z


class Vertex:
    location, texture, normal = None, None, None

    def __init__(self, location, texture, normal):
        self.location = location
        self.texture = texture
        self.normal = normal

    def __eq__(self, other):
        return isinstance(other, Vertex) \
               and self.location == other.location \
               and self.texture == other.texture \
               and self.normal == other.normal
