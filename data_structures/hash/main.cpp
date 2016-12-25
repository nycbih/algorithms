#include <iostream>
#include <type_traits>


#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

template <size_t TSize,typename TKey>
struct Simple
{
    size_t calc(TKey key)
    {
        size_t index = hash(key);
        return index % TSize;
    }
};
///
/// string hash function
///
template <size_t TSize>
struct Simple<TSize,std::string>
{
    size_t calc(const std::string &key)
    {
        size_t index = hash(key);
        return index % TSize;
    }

    std::hash<std::string> hash;
};
///
/// hashing with open addressing and liner probing
///
template<size_t TSize, typename TKey, typename TValue, template <size_t,typename> class TFunc=Simple>
class hash
{
    struct slot
    {
        TKey key;
        TValue value;
        bool used=false;
        bool available=true;
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

        void show()
        {
            std::cout << "key=" << key << " value=" << value << " used=" <<  used << " available=" << available << std::endl;
        }
    };
public:
    struct status
    {
        void update(size_t last)
        {
            if( worst_search_len < last ) worst_search_len = last;
            last_search_len = last;
        }

        size_t last_search_len=0;
        size_t worst_search_len=0;
        size_t find=0;
        size_t remove=0;
        size_t insert=0;
    };
    bool insert(const TKey &key, const TValue &val)
    {
        size_t index = m_func.calc(val);

        size_t last_search_len=0;

        for( size_t i=index; i < TSize; ++i )
        {
            last_search_len++;

            if( m_buckets[i].available || m_buckets[i].key == key )
            {
                m_buckets[i].set(key,val);
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

        for( size_t i=index; i < TSize; ++i )
        {
            if( m_buckets[i].key == key )
            {
                m_buckets[i].reset();
                return true;
            }
        }

        return false;
    }

    bool find(const TKey &key, const TValue val)
    {
        size_t index = m_func.calc(val);

        size_t last_search_len=0;

        for( size_t i=index; i < TSize; ++i )
        {
            last_search_len++;

            if( m_buckets[i].key == key )
            {
                m_status.update(last_search_len);
                return true;
            }
        }

        m_status.update(last_search_len);
        return false;
    }

    status status1()
    {
        return m_status;
    }

    void show()
    {
        for( auto &bucket : m_buckets )
        {
            bucket.show();
        }
    }
private:
    status m_status;

    size_t index(TKey key)
    {
        return m_func.calc(key);
    }
    Simple<TSize,TKey> m_func;
    slot m_buckets[TSize+1];
};
///
/// hashing with chaining
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    hash<5,std::string,std::string> hash1;

    std::string a("a");
    std::string b("b");
    std::string c("c");

    std::cout << hash1.insert(a, b) << std::endl;
    hash1.show();

    std::cout << hash1.find(a,b) << std::endl;

//    std::cout << hash1.find(a,c) << std::endl;

    std::cout << "done...\n";

    return 0;
}
