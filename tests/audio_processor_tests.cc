#include <catch2/catch.hpp>
#include <visualizer/3d_visualizer.h>

namespace audio {
    Visualizer3D visualizer = Visualizer3D();
    TEST_CASE("Mapping Reduction") {
        float mapped = visualizer.Rescale(5, 0, 10, 0, 1);
        REQUIRE(mapped == .5f);
    }

    TEST_CASE("Mapping Increase") {
        float mapped = visualizer.Rescale(1, 0, 1, 0, 10);
        REQUIRE(mapped == 10);
    }

    TEST_CASE("Mapping Decimals") {
        float mapped = visualizer.Rescale(0.1, 0.1, 0.9, 1, 9);
        REQUIRE(mapped == 1);
    }

}