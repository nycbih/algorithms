#pragma once
#include <vector>


namespace hft
{
///
/// default hash function via std::hash
///
    template<size_t TSize, typename TKey>
    struct DefaultHashFunc
    {
        size_t calc(TKey key)
        {
            size_t index = std::hash<TKey>{}(key);
            return index % TSize;
        }
    };

///
/// hashing with open addressing and liner probing
///
    template<size_t TSize, typename TKey, typename TValue, template<size_t, typename> class THashFunc=DefaultHashFunc>
    class hash
    {
        ///
        /// internal representation of bucket
        ///
        struct slot
        {
            TKey key;
            TValue value;
            bool used = false;
            bool available = true;

            void set(const TKey &key_, const TValue &val_)
            {
                key = key_;
                value = val_;
                used = true;
                available = false;
            }

            void reset()
            {
                available = true;
            }
        };

    public:
        using TVector = std::vector<std::pair<TKey, TValue>>;

        struct status
        {
            void update(size_t last)
            {
                if (worst_search_len < last) worst_search_len = last;
                last_search_len = last;
            }

            size_t last_search_len = 0;
            size_t worst_search_len = 0;
            size_t find = 0;
            size_t remove = 0;
            size_t insert = 0;
        };

        bool insert(const TKey &key, const TValue &val)
        {
            size_t index = m_func.calc(val);

            size_t last_search_len = 0;

            for (size_t i = index; i < TSize; ++i)
            {
                last_search_len++;

                if (m_buckets[i].available || m_buckets[i].key == key)
                {
                    m_buckets[i].set(key, val);
                    m_status.update(last_search_len);
                    return true;
                }
            }

            m_status.update(last_search_len);

            return false;
        }

        bool remove(const TKey &key, const TValue &val)
        {
            size_t index = m_func.calc(val);

            size_t last_search_len = 0;

            for (size_t i = index; i < TSize; ++i)
            {
                if (m_buckets[i].key == key)
                {
                    m_buckets[i].reset();
                    m_status.update(last_search_len);
                    return true;
                }
            }

            m_status.update(last_search_len);
            return false;
        }

        bool find(const TKey &key, const TValue val)
        {
            size_t index = m_func.calc(val);

            size_t last_search_len = 0;

            for (size_t i = index; i < TSize; ++i)
            {
                last_search_len++;

                if (m_buckets[i].key == key)
                {
                    m_status.update(last_search_len);
                    return true;
                }
            }

            m_status.update(last_search_len);
            return false;
        }

        ///
        /// track hash performance status
        ///
        const status& hash_perf_stats() const
        {
            return m_status;
        }

        ///
        /// return list of key/value pairs
        ///
        void list(const TVector &vec) const
        {
            for (auto &bucket : m_buckets)
            {
                vec.push_back(std::make_pair(bucket.key, bucket.value));
            }
        }

    private:
        status m_status;

        size_t index(TKey key)
        {
            return m_func.calc(key);
        }

        THashFunc<TSize, TKey> m_func;
        slot m_buckets[TSize + 1];
    };
}