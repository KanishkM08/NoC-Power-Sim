#ifndef __GARNET_HAMMING_DISTANCE_SORTER_HH__
#define __GARNET_HAMMING_DISTANCE_SORTER_HH__

#include <vector>
#include "mem/ruby/network/garnet/flit.hh"

namespace gem5
{

namespace ruby
{

namespace garnet
{

class HammingDistanceSorter
{
  public:
    static void sortFlits(std::vector<flit*>& flits);
  private:
    static unsigned int hammingDistance(flit* a, flit* b);
};

} // namespace garnet
} // namespace ruby
} // namespace gem5

#endif // __GARNET_HAMMING_DISTANCE_SORTER_HH__

