namespace Model
{

template <typename VertexType, typename IndexType>
VertexMap<VertexType, IndexType>::VertexMap() = default;

template <typename VertexType, typename IndexType>
void VertexMap<VertexType, IndexType>::getIndices(std::vector<IndexType> &x)
{
    x = indices;
}

template <typename VertexType, typename IndexType>
void VertexMap<VertexType, IndexType>::getVertices(std::vector<VertexType> &x)
{
    x = vertices;
}

template <typename VertexType, typename IndexType>
void VertexMap<VertexType, typename IndexType>::insert(const VertexType &vertex)
{
    auto search{map.find(vertex)};
    if (search != map.end())
    {
        indices.push_back(search->second);
        return;
    }

    auto newIndex{static_cast<IndexType>(map.size())};
    map[vertex] = newIndex;

    vertices.push_back(vertex);
    indices.push_back(newIndex);
}

} // namespace Model
