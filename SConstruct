project_name = 'cpplib'
env = Environment()
env.VariantDir('build', 'src', duplicate=0)
env.VariantDir('build/test', 'test', duplicate=0)

src = {'common': ['cpplib/common/char.cpp',
                  'cpplib/common/exception.cpp',
                  'cpplib/common/file.cpp',
                  'cpplib/common/object.cpp',
                  'cpplib/common/string.cpp',
                  'cpplib/common/stringInput.cpp'],
        'draw': ['cpplib/draw/camera.cpp',
                 'cpplib/draw/gl/drawDevice.cpp',
                 'cpplib/draw/gl/framebuffer.cpp',
                 'cpplib/draw/gl/model.cpp',
                 'cpplib/draw/gl/program.cpp',
                 'cpplib/draw/gl/texture.cpp',
                 'cpplib/draw/image.cpp',
                 #'cpplib/draw/scene.cpp',
                 'cpplib/draw/sdlWindow.cpp',
                 'cpplib/draw/tga.cpp',
                 'cpplib/draw/entity.cpp'],
        'math': ['cpplib/geom/vec.cpp',
                 'cpplib/geom/ball.cpp',
                 'cpplib/geom/mesh.cpp',
                 'cpplib/math/random.cpp',
                 'cpplib/geom/mat.cpp']}

xxd_src = ['cpplib/draw/gl/glsl/simple.vs',
           'cpplib/draw/gl/glsl/simple.fs',
           'cpplib/draw/gl/glsl/deferred.vs',
           'cpplib/draw/gl/glsl/deferred.fs',
           'cpplib/draw/gl/res/plane.msh',]

test_src = ['test/ball_test.cpp',
            'test/vec_test.cpp',
            'test/tga_test.cpp',
            'test/mat_test.cpp',
            'test/string_test.cpp',
            'test/mesh_test.cpp']


libs=['-lGLEW', '-lGL', '-lSDL']
cxxflags=['-Isrc', '-I.', '-g', '-O0', '-fPIC']

obj = {}

xxd = []
for f in xxd_src:
    xxd.append(env.Command('build/' + f, ['src/' + f], 'xxd -i $SOURCE > $TARGET'))

for k in src:
        obj[k] = env.Object(['build/' + s for s in src[k]], CCFLAGS=cxxflags, LIBS=libs)
        env.Depends(obj[k], xxd)
        lib = env.Library('bin/libcpp_' + k, obj[k], CCFLAGS=cxxflags, LIBS=libs)

libcpp = env.Library('bin/libcpp', obj.values(), CCFLAGS=cxxflags, LIBS=libs)

env.Program('bin/test', obj.values() + ['test/main_test.cpp'], CCFLAGS=cxxflags, LIBS=libs)

test_cxxflags =['-frtti'] + cxxflags
test_libs = ['-lgtest_main', '-lgtest']
test_ldflags = ['-pthread']
env.Program('bin/gtest', ['build/' + s for s in test_src] + obj.values(), CCFLAGS=test_cxxflags, LINKFLAGS=test_ldflags, LIBS=libs+test_libs)
