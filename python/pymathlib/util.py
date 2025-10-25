width = 0.0
height = 0.0


def cartesian_to_native(x, y, w=width, h=height):
    """
    Returns coordinates from native, origin at TOP LEFT, to cartesian, origin at center

    Args:
        x (float): x coordinate, native.
        y (float): y coordinate, native.
        w (float): width of the frame, default to `width`
        h (float): height of the frame, default to `height`

    Returns:
        tuple (float, float): The native coordinates in the form of (x, y)
    """
    return cartesian_to_native_x(x, w), cartesian_to_native_y(y, h)

def cartesian_to_native_x(x, w=width):
    return x + (w / 2)

def cartesian_to_native_y(y, h=height):
    return -y + (h / 2)

def native_to_cartesian(x, y, w=width, h=height):
    return native_to_cartesian_x(x, w), native_to_cartesian_y(y, h)

def native_to_cartesian_x(x, w):
    return x - (w / 2)

def native_to_cartesian_y(y, h):
    return -y + (h / 2)