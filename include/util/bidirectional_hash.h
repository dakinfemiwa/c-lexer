#ifndef BIDIRECTIONAL_HASH_H
#define BIDIRECTIONAL_HASH_H

#include <vector>
#include <unordered_map>
#include <optional>

template<typename K, typename V>
class BidirectionalHash {
    public:
        
        void insert(const K& key, const V& value) {
            forward[key] = value;
            reverse[value] = key;
        }

        std::optional<V> getValue(const K& key) const {
            auto it = forward.find(key);
            if (it != forward.end()) {
                return it->second;
            }
            return std::nullopt;
        }

        std::optional<K> getReverse(const V& value) const {
            auto it = reverse.find(value);
            if (it != reverse.end()) {
                return it->second;
            }
            return std::nullopt;
        }
    

    private:
        std::unordered_map<K, V> forward;
        std::unordered_map<V, K> reverse;
};

#endif