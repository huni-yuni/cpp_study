#include "PathFinder_TwoWaves.h"

#include <unordered_set>
#include <assert.h>
#include <algorithm>
#include <memory>

//
// Service constants
//

static const int MAX_NEIGHBOURS_COUNT = 4;
static const int NULL_IDX             = -1;

//
// Service types
//

namespace // unnamed
{
  class CPassMap final
  {
  public: // Types

    using Idx = int;

  public: // Construction

    CPassMap(
        const std::pair<int, int> _MapDimensions,
        const std::vector<bool> & _Map
      ):
        m_TraversableMap (_Map),
        m_Width          (_MapDimensions.first),
        m_Height         (_MapDimensions.second)
    {
      assert(m_Width > 0 && m_Height > 0);

      int NeededTraversableMapSize = m_Height * m_Width;
      assert(m_TraversableMap.size() == NeededTraversableMapSize);
    }

  public: // Interface

    Idx GetMapIdx(
        std::pair<int, int> _Location
      ) const
    {
      int X_coordinate = _Location.first;
      int Y_coordinate = _Location.second;

      assert(X_coordinate >= 0 && Y_coordinate >= 0);
      assert(X_coordinate < m_Width && Y_coordinate < m_Height);

      Idx MapIdx = Y_coordinate * m_Width + X_coordinate;

      return MapIdx;
    }

    std::vector<Idx> GetTraversableNeighborhood(
        const Idx _LocationMapIdx
      ) const
    {
      std::vector<Idx> Neighbours;
      Neighbours.reserve(MAX_NEIGHBOURS_COUNT);

      const Idx TopNeighbor = _LocationMapIdx + m_Width;
      if (IsTraversable(TopNeighbor))
        Neighbours.push_back(TopNeighbor);

      const Idx BottomNeighbor = _LocationMapIdx - m_Width;
      if (IsTraversable(BottomNeighbor))
        Neighbours.push_back(BottomNeighbor);

      if (_LocationMapIdx % m_Width)
      {
        const Idx LeftNeighbor = _LocationMapIdx - 1;
        if (IsTraversable(LeftNeighbor))
          Neighbours.push_back(LeftNeighbor);
      }

      if ((_LocationMapIdx % m_Width) != (m_Width - 1))
      {
        const Idx RightNeighbor = _LocationMapIdx + 1;
        if (IsTraversable(RightNeighbor))
          Neighbours.push_back(RightNeighbor);
      }

      return Neighbours;
    }

    bool IsTraversable(
        const Idx _LocationMapIdx
      ) const
    {
      return (_LocationMapIdx >= 0                      &&
              _LocationMapIdx < m_TraversableMap.size() &&
              m_TraversableMap[_LocationMapIdx]);
    }

  private: // Attributes

    const std::vector<bool> & m_TraversableMap;

    const int m_Width;
    const int m_Height;
  };

  class CWave final
  {
  public: // Consruction 

    CWave():
        m_PassMap         {},
        m_Source          (NULL_IDX),
        m_Border          (NULL_IDX),
        m_IsBorderReached (false),
        m_TaggedLocations {},
        m_RadialMap       {}
    {
      // Empty
    }

  public: // Interface

    void Reset()
    {
      m_PassMap.reset();
      m_Source  = NULL_IDX;
      m_Border  = NULL_IDX;

      m_IsBorderReached = false;
      m_TaggedLocations.clear();
      m_RadialMap.clear();
    }

    bool IsEmpty() const
    {
      return (!m_PassMap                &&
              m_Source == NULL_IDX      &&
              m_Border == NULL_IDX      &&
              !m_IsBorderReached        &&
              m_TaggedLocations.empty() &&
              m_RadialMap.empty());
    }

    const std::vector<std::unordered_set<CPassMap::Idx>> & GetResult() const
    {
      return m_RadialMap;
    }

    bool IsBorderReached() const
    {
      return m_IsBorderReached;
    }

    void Init(
        const std::shared_ptr<CPassMap> & _PassMap,
        const CPassMap::Idx               _Source,
        const CPassMap::Idx               _Border
      )
    {
      assert(_Source != _Border);

      if (!IsEmpty())
        Reset();

      m_Source  = _Source;
      m_Border  = _Border;
      m_PassMap = _PassMap;

      m_TaggedLocations.insert(m_Source);
      m_RadialMap.push_back({ m_Source });
    }

    bool MakeWaveStep()
    {
      assert(!IsEmpty());

      int WaveRadius = m_RadialMap.size();
      m_RadialMap.push_back({});

      for (const auto Location : m_RadialMap[WaveRadius - 1])
      {
        for (const auto TraversableNeighbor : m_PassMap->GetTraversableNeighborhood(Location))
        {
          TagLocation(WaveRadius, TraversableNeighbor);

          if (m_IsBorderReached)
            break;
        }

        if (m_IsBorderReached)
          break;
      }

      if (!m_RadialMap.back().empty())
        return true;

      m_RadialMap.pop_back();
      return false;
    }

    void GetRadiusPath(
        const CPassMap::Idx          _Location,
        std::vector<CPassMap::Idx> & _OutPath
      ) const
    {
      assert(!IsEmpty());
      assert(m_RadialMap.back().find(_Location) != m_RadialMap.back().end());

      _OutPath.clear();

      if (_Location == m_Source)
        return;

      _OutPath.push_back(_Location);

      CPassMap::Idx PathLocation = _Location;
      auto WaveRadius            = --m_RadialMap.end();

      while (WaveRadius > ++m_RadialMap.begin())
      {
        WaveRadius--;

        std::vector<CPassMap::Idx> TraversableNeighborhood = m_PassMap->GetTraversableNeighborhood(PathLocation);

        auto SuitableNeighbor = std::find_first_of(
          (*WaveRadius).begin(),
          (*WaveRadius).end(),
          TraversableNeighborhood.begin(),
          TraversableNeighborhood.end()
        );

        PathLocation = *SuitableNeighbor;
        _OutPath.push_back(PathLocation);
      }
    }

  private: // Service

    void TagLocation(
        const int           _WaveRadius,
        const CPassMap::Idx _Location
      )
    {
      if (_Location == m_Border)
      {
        m_IsBorderReached = true;
        m_RadialMap[_WaveRadius].clear();
        return;
      }

      const auto Result = m_TaggedLocations.insert(_Location);

      if (!Result.second)
        return;

      m_RadialMap[_WaveRadius].insert(_Location);
    }

  private: // Attributes

    std::shared_ptr<CPassMap>       m_PassMap;
    CPassMap::Idx                   m_Source;
    CPassMap::Idx                   m_Border;

    bool                                           m_IsBorderReached;
    std::unordered_set<CPassMap::Idx>              m_TaggedLocations;
    std::vector<std::unordered_set<CPassMap::Idx>> m_RadialMap;
  };

} // unnamed namespace

//
// Implementation
//

bool FindPath(
    std::pair<int, int>       _Start,
    std::pair<int, int>       _Target,
    const std::vector<bool> & _Map,
    std::pair<int, int>       _MapDimensions,
    std::vector<int> &        _OutPath
  )
{
  _OutPath.clear();

  const auto PassMap = std::make_shared<CPassMap>(_MapDimensions, _Map);

  const CPassMap::Idx StartLocation  = PassMap->GetMapIdx(_Start);
  const CPassMap::Idx TargetLocation = PassMap->GetMapIdx(_Target);

  assert(PassMap->IsTraversable(StartLocation) && PassMap->IsTraversable(TargetLocation));

  if (StartLocation == TargetLocation)
    return true;

  const auto StartWave = std::make_unique<CWave>();
  StartWave->Init(PassMap, StartLocation, TargetLocation);

  const auto TargetWave = std::make_unique<CWave>();
  TargetWave->Init(PassMap, TargetLocation, StartLocation);

  CPassMap::Idx Intersection = NULL_IDX;

  auto FindIntersection = [&](
      const auto & _FirstContainer,
      const auto & _SecondContainer
    )
  {
    const auto IntersectionIt = std::find_first_of(
                                    _FirstContainer.begin(),
                                    _FirstContainer.end(),
                                    _SecondContainer.begin(),
                                    _SecondContainer.end()
                                  );

    if (IntersectionIt != _FirstContainer.end())
      Intersection = (*IntersectionIt);
  };

  const int MinStepsBeforeIntersection = abs(_Target.first - _Start.first) + abs(_Target.second - _Start.second);
  int       StepsCount                 = 0;

  while (true)
  {
    if (!StartWave->MakeWaveStep())
      break;
    
    if (++StepsCount >= MinStepsBeforeIntersection)
      FindIntersection(StartWave->GetResult().back(), TargetWave->GetResult().back());

    if (Intersection != NULL_IDX)
      break;

    if (!TargetWave->MakeWaveStep())
      break;

    if (++StepsCount >= MinStepsBeforeIntersection)
      FindIntersection(StartWave->GetResult().back(), TargetWave->GetResult().back());

    if (Intersection != NULL_IDX)
      break;
  }

  if (StartWave->IsBorderReached())
  {
    _OutPath.push_back(TargetLocation);
    return true;
  }

  if (Intersection == NULL_IDX)
    return false;

  std::vector<CPassMap::Idx> IntersectionToStartPath;
  std::vector<CPassMap::Idx> IntersectionToTargetPath;

  StartWave-> GetRadiusPath(Intersection, IntersectionToStartPath);
  TargetWave->GetRadiusPath(Intersection, IntersectionToTargetPath);

  StartWave-> Reset();
  TargetWave->Reset();

  IntersectionToTargetPath.push_back(TargetLocation);

  _OutPath.insert(_OutPath.begin(), IntersectionToStartPath.rbegin(), IntersectionToStartPath.rend());
  _OutPath.pop_back();
  _OutPath.insert(_OutPath.end(), IntersectionToTargetPath.begin(), IntersectionToTargetPath.end());

  return true;
}