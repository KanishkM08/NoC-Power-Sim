// src/mem/ruby/network/garnet/HammingDistanceSorter.cc - (Corrections)

#include "mem/ruby/network/garnet/HammingDistanceSorter.hh"
#include <algorithm>
#include <vector>

namespace gem5
{
namespace ruby
{
namespace garnet
{
// C++ Fix: Use the fully qualified name in the function signatures 
// to avoid the 'flit not declared in this scope' error.

unsigned int
HammingDistanceSorter::hammingDistance(
    gem5::ruby::garnet::flit* a, // <-- FIX
    gem5::ruby::garnet::flit* b  // <-- FIX
)
{
    // LOGIC FIX: Calculate distance based on the actual data payload.
    // The paper's intent is to minimize bit toggling between adjacent flits.
    return __builtin_popcount(a->get_data_payload() ^ b->get_data_payload());
}

// Ensure 'void' is present and use the fully qualified name for flit
void
HammingDistanceSorter::sortFlits(std::vector<gem5::ruby::garnet::flit*>& F) // <-- FIX
{
    int N = F.size();
    if (N <= 2) return; // Cannot sort 0, 1, or 2 flits (Head + optional 1 body)

    // Greedy selection sort (matches your initial implementation)
    for (int i = 0; i < N - 1; ++i) {
        int min_idx = i + 1;
        // Calculate distance between F[i] (current flit) and F[i+1] (next flit)
        unsigned int min_dist = hammingDistance(F[i], F[min_idx]); 
        
        // Search the rest of the list for a flit with a smaller HD to F[i]
        for (int j = i + 2; j < N; ++j) {
            unsigned int dist = hammingDistance(F[i], F[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = j;
            }
        }
        
        // Swap the best-fit flit (min_idx) into the next position (i + 1)
        if (min_idx != i + 1)
            std::swap(F[i + 1], F[min_idx]);
    }
}

} // namespace garnet
} // namespace ruby
} // namespace gem5
