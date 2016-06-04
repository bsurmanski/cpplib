#include <gtest/gtest.h>
#include "cpplib/geom/mesh.hpp"
#include "cpplib/common/file.hpp"

TEST(Mdl, Load) {
    File file("cube.msh");
    Mesh *m = Mesh::load(&file);
    ASSERT_EQ(m->header.nverts, 8);
    ASSERT_EQ(m->header.nuvs, 8);
    ASSERT_EQ(m->header.nfaces, 12);
    ASSERT_EQ(m->header.nedges, 18);
    delete m;
}
