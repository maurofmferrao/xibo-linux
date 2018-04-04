#pragma once

#include "constants.hpp"
#include <memory>

class Region;

class RegionBuilder
{
public:
    RegionBuilder() = delete;
    static std::unique_ptr<Region> create(int region_id);

};
