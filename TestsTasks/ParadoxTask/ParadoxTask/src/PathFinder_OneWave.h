#pragma once

#include <utility>
#include <vector>

bool FindPath(
    std::pair<int, int>       _Start,
    std::pair<int, int>       _Target,
    const std::vector<bool> & _Map,
    std::pair<int, int>       _MapDimensions,
    std::vector<int> &        _OutPath
  );