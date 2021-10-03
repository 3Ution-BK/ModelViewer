#ifndef MODELVIEWER_MODEL_VERTEXMAP_HPP_
#define MODELVIEWER_MODEL_VERTEXMAP_HPP_

#include "Hash/Hash.hpp"

#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Model
{

template <typename VertexType, typename IndexType = unsigned int>
class VertexMap
{
    static_assert(std::is_integral<IndexType>::value,
                  "IndexType is not integral type.");

public:
    explicit VertexMap();

    void insert(const VertexType &vertex);

    void getIndices(std::vector<IndexType> &x);
    void getVertices(std::vector<VertexType> &x);

private:
    std::vector<IndexType> indices;
    std::vector<VertexType> vertices;
    std::unordered_map<VertexType, IndexType, Hash::Hash<VertexType>> map;
};

} // namespace Model

#include "VertexMap-inl.hpp"

#endif // MODELVIEWER_MODEL_VERTEXMAP_HPP_
