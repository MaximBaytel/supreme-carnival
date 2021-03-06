import math

filename = 'naive_sphere.h'

c_array_name = 'const float sphere_model[]'

longitude_steps = 10
latitude_steps  = 10

float_signification_count = 6

include_normals = True
include_uv_coordinates = True

def toCfloat(x):
    return format(x,'.%df' % float_signification_count) + 'f,'

file = open('./' + filename,'w')

file.write('//this file is autogenerated header that contains sphere model as C-array\r\n\r\n')


file.write(c_array_name + '={\r\n')


southtpole = toCfloat(0.0) + toCfloat(0.0) + toCfloat(-1.0)

if (include_normals):
    southtpole += toCfloat(0.0) + toCfloat(0.0) + toCfloat(-1.0)

    if (include_uv_coordinates):
        southtpole += toCfloat(0.0) + toCfloat(0.0)

    southtpole += '\n'

file.write(southtpole)

count = 1
i = 1
#for i in range(latitude_steps):
while i < latitude_steps:
    u1 = i/latitude_steps
    latitude1 = -math.pi/2  + math.pi * u1

    z1 = math.sin(latitude1)
    r1 = abs(math.cos(latitude1))

    i = i + 1

    u2 = i/latitude_steps
    latitude2 = -math.pi/2  + math.pi * u2

    z2 = math.sin(latitude2)
    r2 = abs(math.cos(latitude2))

    i = i + 1

    for j in range(longitude_steps):
        v = j/longitude_steps

        longitude = v * 2 * math.pi

        x = math.cos(longitude) * r1
        y = math.sin(longitude) * r1

        str = toCfloat(x) + toCfloat(y) + toCfloat(z1)

        if (include_normals):
            str += toCfloat(x) + toCfloat(y) + toCfloat(z1)

        if (include_uv_coordinates):
            str += toCfloat(u1) + toCfloat(v)

        str += '\n'

        file.write(str)

        x = math.cos(longitude) * r2
        y = math.sin(longitude) * r2

        str = toCfloat(x) + toCfloat(y) + toCfloat(z2)

        if (include_normals):
            str += toCfloat(x) + toCfloat(y) + toCfloat(z2)

        if (include_uv_coordinates):
            str += toCfloat(u2) + toCfloat(v)

        str += '\n'

        file.write(str)


        count += 2


northtpole = toCfloat(0.0) + toCfloat(0.0) + toCfloat(1.0)

if (include_normals):
    northtpole += toCfloat(0.0) + toCfloat(0.0) + toCfloat(1.0)

    if (include_uv_coordinates):
        northtpole += toCfloat(1.0) + toCfloat(0.0)

    northtpole += '\n'

file.write(southtpole)



file.write('};\n\n')

file.write('const unsigned int sphere_model_count = %d;\n' % (count+1))


file.write('const unsigned int latitude_steps = %d;\n' % latitude_steps)
file.write('const unsigned int longitude_steps = %d;\n' % latitude_steps)

file.close()

