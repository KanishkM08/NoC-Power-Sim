#include "mem/ruby/network/garnet/HammingDistanceSorter.hh"
#include <algorithm>

namespace gem5
{
namespace ruby
{
namespace garnet
{

unsigned int
HammingDistanceSorter::hammingDistance(flit* a, flit* b)
{
    // Simple placeholder: XOR IDs for now
    return __builtin_popcount(a->get_id() ^ b->get_id());

}

void
HammingDistanceSorter::sortFlits(std::vector<flit*>& F)
{
    int N = F.size();
    if (N <= 2) return;

    for (int i = 0; i < N - 1; ++i) {
        int min_idx = i + 1;
        unsigned int min_dist = hammingDistance(F[i], F[min_idx]);
        for (int j = i + 2; j < N; ++j) {
            unsigned int dist = hammingDistance(F[i], F[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = j;
            }
        }
        if (min_idx != i + 1)
            std::swap(F[i + 1], F[min_idx]);
    }
}

} // namespace garnet
} // namespace ruby
} // namespace gem5

